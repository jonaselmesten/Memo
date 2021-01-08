#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deckaddwindow.h"
#include "deckrow.h"
#include <iostream>
#include <string>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_deckAddButton_clicked() {

    ui_add_deck = new DeckAddWindow(this);

    connect(ui_add_deck, SIGNAL(sendName(QString)), this, SLOT(add_new_deck_line(QString)));

    ui_add_deck->setModal(true);
    ui_add_deck->show();
}


void MainWindow::add_new_deck_line(const QString &name) {

    if(deck_holder.addNewDeck(name.toStdString())) {

        DeckRow *row = new DeckRow(this);

        connect(row->findChild<QPushButton*>("removeButton"), &QPushButton::clicked,
                [=]() {
            this->deleteDeck(row->findChild<QLabel*>("deckName")->text());
        }
        );

        row->init(name.simplified(), &deck_holder.getDeck(name.toStdString()));

        ui->deckHolder->addWidget(row);
        ui_add_deck->changeMessageText("Enter name of new deck.");

    }else {
        ui_add_deck->changeMessageText("A deck with that name already exists.");
    }
}

void MainWindow::deleteDeck(const QString &name) {
    deck_holder.deleteDeck(name.toStdString());
}






