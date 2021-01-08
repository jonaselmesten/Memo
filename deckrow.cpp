#include "deckrow.h"
#include "ui_deckrow.h"
#include "cardwindow.h"
#include <iostream>

DeckRow::DeckRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeckRow)
{
    ui->setupUi(this);
}

DeckRow::~DeckRow() {
    delete ui;
}

void DeckRow::init(QString name, std::vector<Card*> *cards) {
    ui->deckName->setText(name);
    this->cards = cards;
}

void DeckRow::on_studyButton_clicked() {
    std::cout << "STUDY " << ui->deckName->text().toStdString() << std::endl;

    CardWindow *window = new CardWindow(this);
    window->init(ui->deckName->text(), cards);
    window->show();
}

void DeckRow::on_removeButton_clicked() {
    deleteLater();
}
