//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deckaddwindow.h"
#include "deckreader.h"
#include "errorwindow.h"
#include "deckformatexception.h"
#include "deckrow.h"
#include "deckwriter.h"
#include <iostream>
#include <string>
#include <QPushButton>
#include <QCloseEvent>
#include <fstream>
#include <filesystem>
#include <sstream>


namespace fs = std::filesystem;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , folderPath("C:\\deckapp")
{
    ui->setupUi(this);
    loadDecks();
}

MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief MainWindow::on_deckAddButton_clicked
 * Opens a new window where the name can be specified.
 */
void MainWindow::on_deckAddButton_clicked() {

    uiAddDeck = new DeckAddWindow(this);

    connect(uiAddDeck, SIGNAL(sendName(QString)), this, SLOT(addNewDeckLine(QString)));

    uiAddDeck->setModal(true);
    uiAddDeck->show();
}

/**
 * @brief MainWindow::addNewDeckLine
 * @param name Name of new deck.
 * This will be called through DeckAddWindow when a new deck is added.
 */
void MainWindow::addNewDeckLine(QString name) {

    //Add if not already in map.
    if(deckMap.end() == deckMap.find(name.simplified().toStdString())) {

        DeckRow *row = new DeckRow(this);
        std::string deck_name = name.simplified().toStdString();

        //Bind remove button to this name.
        connect(row->findChild<QPushButton*>("removeButton"), &QPushButton::clicked,
                [=]() {this->deleteDeck(row->findChild<QLabel*>("deckName")->text());}
        );

        SmartVector<Card> *deck = new SmartVector<Card>(deck_name);

        deckMap.insert({deck_name, deck});

        row->init(name, *deck);

        //Add new row to GUI.
        ui->deckHolder->addWidget(row);
        uiAddDeck->changeMessageText("Enter name of new deck.");

    }else {
        uiAddDeck->changeMessageText("A deck with that name already exists.");
    }
}

/**
 * @brief MainWindow::deleteDeck
 * @param name Name of the deck to be deleted.
 * Will also delete the directory of this deck.
 */
void MainWindow::deleteDeck(QString name) {

    try {

        fs::remove_all(folderPath + "\\" + name.toStdString());
        deckMap.erase(name.toStdString());

    }  catch (...) {
        ErrorWindow *window = new ErrorWindow(this);
        window->setMessage(name + " could not be deleted from disk.");
    }
}

/**
 * @brief MainWindow::saveDecks
 * Save all decks to PC with DeckWriter.
 */
void MainWindow::saveDecks() {

    //Create folder to store all data.
    try {
        if(!fs::exists(folderPath))
            fs::create_directory(folderPath);
    }  catch (...) {

        ErrorWindow *window = new ErrorWindow(this);
        window->setMessage("Base folder could not be created.");

        return;
    }

    DeckWriter writer = DeckWriter(folderPath);

    //Go through all decks.
    for(auto const& obj : deckMap) {

        //Move on to next deck in case of exception - to store sa much data as possible.
        try {
            writer.writeDeckToFile(*obj.second);
        } catch (...) {

            ErrorWindow *window = new ErrorWindow(this);
            std::string errorMessage = obj.first + " could not be written to disk.";
            window->setMessage(errorMessage.c_str());

        }
    }
}

/**
 * @brief MainWindow::loadDecks
 * Loads all the decks from PC.
 */
void MainWindow::loadDecks() {

    DeckReader reader;

    //Go through all directoris (deck data).
    for(auto& path: fs::directory_iterator(folderPath)) {

        try {

            SmartVector<Card>* deck = reader.readDeck(path);
            deckMap.insert({deck->getName(), deck});

            DeckRow *row = new DeckRow(this);

            //Bind remove button to this name.
            connect(row->findChild<QPushButton*>("removeButton"), &QPushButton::clicked,
                    [=]() {
                this->deleteDeck(row->findChild<QLabel*>("deckName")->text());
            }
            );

            row->init(QString(deck->getName().c_str()), *deck);

            //Add new row to GUI.
            ui->deckHolder->addWidget(row);

        }  catch (DeckFormatException e) {

            ErrorWindow *window = new ErrorWindow(this);
            window->setMessage("Error in card format.");
            window->show();

        } catch (...) {
            ErrorWindow *window = new ErrorWindow(this);
            window->setMessage("Could not load from disk.");
            window->show();
        }
    }
}

void MainWindow::closeEvent (QCloseEvent *event) {
    saveDecks();
}


