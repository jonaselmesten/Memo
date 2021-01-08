#include "cardwindow.h"
#include "ui_cardwindow.h"
#include "textpart.h"
#include <QFileDialog>
#include <iostream>

CardWindow::CardWindow(QWidget *parent) :
    QMainWindow(parent),
    current_tab(STUDY),
    ui(new Ui::CardWindow)
{
    ui->setupUi(this);
}

CardWindow::~CardWindow() {
    delete ui;
}

void CardWindow::init(QString name, std::vector<Card*> *cards) {

    ui->newAnswerImageButton->hide();
    ui->newQuestionImageButton->hide();
    ui->newAnswerImage->hide();
    ui->newQuestionImage->hide();

    this->name = name;
    this->cards = cards;

    this->setWindowTitle(name);

    this->setTabs();
}

void CardWindow::setTabs() {

    if(cards->size() == 0) {
        this->ui->windowMessage->setText("Deck is empty - Add cards to be able to study/edit.");
        this->ui->tabWidget->setCurrentIndex(2);
        this->ui->studyTab->setEnabled(false);
        this->ui->editTab->setEnabled(false);
    }else {
        this->ui->studyTab->setEnabled(true);
        this->ui->editTab->setEnabled(true);
    }
}

void CardWindow::on_newQuestionType_currentIndexChanged(int index) {

    switch (index) {
    case 0: changeVisible(current_tab, TEXT, QUESTION);
        question = TEXT;
        break;
    case 1: changeVisible(current_tab, IMAGE, QUESTION);
        question = IMAGE;
        break;
    case 2: changeVisible(current_tab, IMAGE_TEXT, QUESTION);
        question = IMAGE_TEXT;
        break;
    }
}

void CardWindow::on_newAnswerType_currentIndexChanged(int index) {
    switch (index) {
    case 0: changeVisible(current_tab, TEXT, ANSWER);
        answer = TEXT;
        break;
    case 1: changeVisible(current_tab, IMAGE, ANSWER);
        answer = IMAGE;
        break;
    case 2: changeVisible(current_tab, IMAGE_TEXT, ANSWER);
        answer = IMAGE_TEXT;
        break;
    }
}

void CardWindow::changeVisible(Tab tab, Type type, Side side) {

    switch (tab) {
    case EDIT:
        switch (side) {
        case QUESTION:
            switch (type) {
            case TEXT:

                break;
            case IMAGE:

                break;
            case IMAGE_TEXT:

                break;
            }
            break;
        case ANSWER:
            switch (type) {
            case TEXT:

                break;
            case IMAGE:

                break;
            case IMAGE_TEXT:

                break;
            }
            break;
        }
        break;
    case NEW:
        switch (side) {
        case QUESTION:
            switch (type) {
            case TEXT:
                ui->newQuestionImageButton->hide();
                ui->newQuestionText->show();
                ui->newQuestionImage->hide();
                break;
            case IMAGE:
                ui->newQuestionText->hide();
                ui->newQuestionImageButton->show();
                ui->newQuestionImage->show();
                break;
            case IMAGE_TEXT:
                ui->newQuestionText->show();
                ui->newQuestionImageButton->show();
                ui->newQuestionImage->show();
                break;
            }
            break;
        case ANSWER:
            switch (type) {
            case TEXT:
                ui->newAnswerImageButton->hide();
                ui->newAnswerText->show();
                ui->newAnswerImage->hide();
                break;
            case IMAGE:
                ui->newAnswerText->hide();
                ui->newAnswerImageButton->show();
                ui->newAnswerImage->show();
                break;
            case IMAGE_TEXT:
                ui->newAnswerText->show();
                ui->newAnswerImageButton->show();
                ui->newAnswerImage->show();
                break;
            }
            break;
        }
        break;
    }
}

void CardWindow::on_newQuestionImageButton_clicked() {

    //TODO MAKE TO ONE FUNCTION
    QString questionImage = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "C:/",
                                                        tr("Images (*.png *.xpm *.jpg)"));
    ui->newQuestionImage->setPixmap(questionImage);
    ui->newQuestionImage->show();

    std::cout << questionImage.toStdString() << std::endl;
}

void CardWindow::on_newAnswerImageButton_clicked() {

    QString answerImage = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "C:/",
                                                        tr("Images (*.png *.xpm *.jpg)"));
    ui->newAnswerImage->setPixmap(answerImage);
    ui->newAnswerImage->show();

    std::cout << answerImage.toStdString() << std::endl;
}

void CardWindow::on_newClearButton_clicked() {

    ui->newAnswerImage->clear();
    ui->newAnswerText->clear();
    ui->newAnswerImage->hide();
    ui->newQuestionImage->clear();
    ui->newQuestionImage->hide();
    ui->newQuestionText->clear();
}

void CardWindow::on_newAddButton_clicked() {

    CardPart *new_question;
    CardPart *new_answer;

    //Create question
    switch (question) {
    case TEXT:
        new_question = new TextPart(ui->newQuestionText->toPlainText());
        break;
    case IMAGE:

        break;
    case IMAGE_TEXT:

        break;
    }

    //Create answer
    switch (answer) {
    case TEXT:
        new_answer = new TextPart(ui->newAnswerText->toPlainText());
        break;
    case IMAGE:

        break;
    case IMAGE_TEXT:

        break;
    }

    //OM MAN INTE SKRIVER IN NÅGOT I RUTORNA BLIR DET KNEIS
    Card *card =  new Card(new_question, new_answer);
    cards->push_back(card);

    std::cout << "------------ SIZE:" << cards->size() << std::endl;

    for(Card* c : *cards) {
        std::cout << "Saveable:" << c->to_saveable_string() << std::endl;
    }

}

void CardWindow::on_tabWidget_currentChanged(int index) {

    switch (index) {
        case 0: current_tab = STUDY;
            break;
        case 1: current_tab = EDIT;
            break;
        case 2: current_tab = NEW;
    }
}

void CardWindow::on_sortOption_currentIndexChanged(int index) {



}
