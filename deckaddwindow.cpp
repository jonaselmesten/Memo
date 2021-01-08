#include "deckaddwindow.h"
#include "ui_deckaddwindow.h"

DeckAddWindow::DeckAddWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeckAddWindow)
{
    ui->setupUi(this);
}

DeckAddWindow::~DeckAddWindow() {
    delete ui;
}

void DeckAddWindow::on_addButton_clicked() {
    emit sendName(ui->nameInput->text());
    ui->nameInput->clear();
}

void DeckAddWindow::changeMessageText(QString text) {
    ui->msgText->setText(text);
}
