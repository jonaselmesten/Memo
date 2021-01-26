//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "deckrow.h"
#include "ui_deckrow.h"
#include "cardwindow.h"
#include "smartvector.h"
#include <iostream>
#include <memory>

DeckRow::DeckRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeckRow),
    time(0)
{
    ui->setupUi(this);
}

DeckRow::~DeckRow() {
    delete ui;
}

void DeckRow::init(QString name, SmartVector<Card> &deck) {
    ui->deckName->setText(name);
    this->deck = &deck;
}

/**
 * @brief DeckRow::changeStudyTime
 * @param seconds How long this deck has been studied.
 * Will convert the amount of seconds to hours, minutes and seconds.
 */
void DeckRow::changeStudyTime(int seconds) {

    time += seconds;
    int total = time;

    int hour = total / 3600;
    total %= 3600;
    int min = time / 60 ;
    total %= 60;
    int sec = total;

    std::string time =  "H:" + std::to_string(hour) +
                        " M:" + std::to_string(min) +
                        " S:" + std::to_string(sec);

    ui->timeStudied->setText(time.c_str());
}

void DeckRow::on_removeButton_clicked() {
    deleteLater();
}

/**
 * @brief DeckRow::on_studyButton_clicked
 * Open a CardWindow for this deck.
 */
void DeckRow::on_studyButton_clicked() {

    CardWindow *window = new CardWindow(this);

    connect(window, SIGNAL(updateStudyTime(int)), this, SLOT(changeStudyTime(int)));

    window->init(ui->deckName->text(), deck);
    window->show();
}
