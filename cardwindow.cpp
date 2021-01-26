//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "cardwindow.h"
#include "ui_cardwindow.h"
#include "textpart.h"
#include "imagepart.h"
#include "linkpart.h"
#include "smartvector.h"
#include <QFileDialog>
#include <iostream>
#include <memory>
#include <algorithm>
#include <random>
#include <regex>

/**
 * @brief The CompCardDate struct
 * Used when logic to sort cards by date is needed.
 */
struct CompCardDate {
    bool operator() (Card* lhs, Card* rhs) {
        if(lhs->getNextDate() != rhs->getNextDate())
            return lhs->getNextDate() < rhs->getNextDate();
        return (lhs->getDateModifier() < rhs->getDateModifier());
    }
};

/**
 * @brief The CompCardDifficulty struct
 * Used when logic to sort cards by the date modifier is needed.
 * The next-date-modifier value represents the difficulty in a card.
 */
struct CompCardDifficulty {
    bool operator() (Card* lhs, Card* rhs) {
        if(lhs->getDateModifier() != rhs->getDateModifier())
            return lhs->getDateModifier() < rhs->getDateModifier();
        return (lhs->getNextDate() < rhs->getNextDate());
    }
};

CardWindow::CardWindow(QWidget *parent) :
    QMainWindow(parent),
    question(TEXT),
    answer(TEXT),
    currentTab(STUDY),
    ui(new Ui::CardWindow)
{
    ui->setupUi(this);
}

CardWindow::~CardWindow() {
    delete ui;
}

/**
 * @brief CardWindow::init
 * @param name Name of the window.
 * @param deck Deck to be studied/add cards to.
 */
void CardWindow::init(QString name, SmartVector<Card> *deck) {

    //Init GUI.
    ui->newAnswerImageButton->hide();
    ui->newQuestionImageButton->hide();
    ui->newAnswerImage->hide();
    ui->newQuestionImage->hide();
    ui->frame->hide();
    activateButtonRow(false);

    this->name = name;
    this->deck = deck;
    this->setWindowTitle(name);
    this->setTabs();

    //Fill vector with cards of date before or on current date.
    if(deck->size() > 0) {
        std::for_each(deck->begin(), deck->end(), [&](std::shared_ptr<Card> const &card) {
            if(card.get()->getNextDate() <= QDateTime::currentDateTime())
                cardDeque.push_front(card.get());
        });
    }

    //Show empty message if empty.
    if(cardDeque.empty()) {
        this->ui->windowMessage->setText(QString("No cards to study today"));
        this->ui->studyTab->setEnabled(false);
        return;
    }

    //Sort after date automatically.
    on_sortOption_currentIndexChanged(0);

    std::string message = "Cards to study: " + std::to_string(cardDeque.size());
    this->ui->windowMessage->setText(QString(message.c_str()));
}

/**
 * @brief CardWindow::activateButtonRow
 * @param active
 * Show or hide the button row:
 * VERY HARD - HARD - MEDIUM - EASY - VERY EASY
 */
void CardWindow::activateButtonRow(bool active) {

    if(active) {
        ui->vhButton->show();
        ui->hButton->show();
        ui->mButton->show();
        ui->eButton->show();
        ui->veButton->show();
    }else {
        ui->vhButton->hide();
        ui->hButton->hide();
        ui->mButton->hide();
        ui->eButton->hide();
        ui->veButton->hide();
    }
}

/**
 * @brief CardWindow::setTabs
 * Will adjust the tabs according to whether the deck is empty or not.
 */
void CardWindow::setTabs() {

    if(deck->size() == 0) {
        this->ui->windowMessage->setText("Deck is empty - Add cards to be able to study/edit.");
        this->ui->tabWidget->setCurrentIndex(2);
        this->ui->studyTab->setEnabled(false);
    }else {
        this->ui->studyTab->setEnabled(true);
        this->ui->windowMessage->clear();
    }
}

/**
 * @brief CardWindow::on_newQuestionType_currentIndexChanged
 * @param index Index of question selector.
 * Adjust gui after what's selected in the question type.
 */
void CardWindow::on_newQuestionType_currentIndexChanged(int index) {

    switch (index) {
    case 0: changeVisible(TEXT, QUESTION);
        question = TEXT;
        break;
    case 1: changeVisible(IMAGE, QUESTION);
        question = IMAGE;
        break;
    }
}

/**
 * @brief CardWindow::on_newAnswerType_currentIndexChanged
 * @param index Index of question selector.
 * Adjust gui after what's selected in the answer type.
 */
void CardWindow::on_newAnswerType_currentIndexChanged(int index) {

    switch (index) {
    case 0: changeVisible(TEXT, ANSWER);
        answer = TEXT;
        break;
    case 1: changeVisible(IMAGE, ANSWER);
        answer = IMAGE;
        break;
    case 2: changeVisible(TEXT, ANSWER);
        answer = LINK;
        break;
    }
}

/**
 * @brief CardWindow::changeVisible
 * @param type Type of card part
 * @param side Question or answer
 */
void CardWindow::changeVisible(Type type, Side side) {

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
        case LINK:
            ui->newAnswerImageButton->hide();
            ui->newAnswerText->show();
            ui->newAnswerImage->hide();
            break;
        }
        break;
    }
}

void CardWindow::on_newQuestionImageButton_clicked() {
    saveImagePath(QUESTION);
}

void CardWindow::on_newAnswerImageButton_clicked() {
    saveImagePath(ANSWER);
}

/**
 * @brief CardWindow::saveImagePath
 * @param side Question or answer
 * Open a file selector for images.
 */
void CardWindow::saveImagePath(Side side) {

    QString image_path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "C:/",
                                                        tr("Images (*.png *.xpm *.jpg)"));
    switch (side) {
    case QUESTION:
        ui->newQuestionImage->setPixmap(image_path);
        ui->newQuestionImage->show();
        questionImagePath = image_path.toStdString();
        break;
    case ANSWER:
        ui->newAnswerImage->setPixmap(image_path);
        ui->newAnswerImage->show();
        answerImagePath = image_path.toStdString();
        break;
    }
}

/**
 * @brief CardWindow::on_newClearButton_clicked
 * Clear all the fields when a new card is added.
 */
void CardWindow::on_newClearButton_clicked() {

    ui->newAnswerImage->clear();
    ui->newAnswerText->clear();
    ui->newAnswerImage->hide();
    ui->newQuestionImage->clear();
    ui->newQuestionImage->hide();
    ui->newQuestionText->clear();
}

/**
 * @brief CardWindow::on_newAddButton_clicked
 * Creates a new card depeding on what types are selected as question ans answer.
 * The card is then added to the deck.
 */
void CardWindow::on_newAddButton_clicked() {

    CardPart *new_question = nullptr;
    CardPart *new_answer = nullptr;

    //Create question
    switch (question) {
    case TEXT:

        if(textEditIsEmpty(QUESTION)) {
            ui->windowMessage->setText("Text edit can't be empty.");
            return;
        }

        new_question = new TextPart(ui->newQuestionText->toPlainText());

        break;
    case IMAGE:
        new_question = new ImagePart(questionImagePath.string());
        break;
    }

    //Create answer
    switch (answer) {
    case TEXT:

        if(textEditIsEmpty(ANSWER)) {
            ui->windowMessage->setText("Text edit can't be empty.");
            delete new_question;
            return;
        }

        new_answer = new TextPart(ui->newAnswerText->toPlainText());

        break;
    case IMAGE:
        new_answer = new ImagePart(answerImagePath.string());
        break;
    case LINK:

        if(textEditIsEmpty(ANSWER)) {
            ui->windowMessage->setText("Text edit can't be empty.");
            delete new_question;
            return;
        }

        new_answer = new LinkPart(ui->newAnswerText->toPlainText());

        break;
    }

    deck->addObject(std::make_shared<Card>(new_question, new_answer, 0, QDateTime::currentDateTime()));

    //Clear the fiedls.
    ui->newQuestionText->clear();
    ui->newAnswerText->clear();
    ui->newAnswerImage->clear();
    ui->newQuestionImage->clear();
}

/**
 * @brief CardWindow::textEditIsEmpty
 * @param side Question or answer
 * @return Text field is empty or not.
 */
bool CardWindow::textEditIsEmpty(Side side) {

    switch(side) {
    case QUESTION:
        if(ui->newQuestionText->toPlainText().trimmed().isEmpty())
            return true;
        break;
    case ANSWER:
        if(ui->newAnswerText->toPlainText().trimmed().isEmpty())
            return true;
        break;
    }

    return false;
}

/**
 * @brief CardWindow::on_sortOption_currentIndexChanged
 * @param index Sort option
 * Sort the current deck according to what is selected.
 * 0 - Sort after date
 * 1 - Sort after difficulty
 * 2 - Random
 */
void CardWindow::on_sortOption_currentIndexChanged(int index) {

    //Sort the deque after different options.
    switch (index) {
        case 0://Date
            std::cout << "Sort date" << std::endl;
            std::sort(cardDeque.begin(), cardDeque.end(), CompCardDate());
            break;
        case 1://Difficulty
            std::cout << "Sort difficulty" << std::endl;
            std::sort(cardDeque.begin(), cardDeque.end(), CompCardDifficulty());
            break;
        case 2://Random
            std::cout << "Sort random" << std::endl;
            std::random_device random;
            std::mt19937 g(random());
            std::shuffle(cardDeque.begin(), cardDeque.end(), g);
        break;
    }

    /*
    std::for_each(card_queue.begin(),card_queue.end(),[](Card  *card) {
        std::cout << card->getNextDate().toString().toStdString() << " - " << card->getDateModifier() << " - " << card->getQuestion()->to_saveable() << std::endl;
    });
    */
}

/**
 * @brief CardWindow::closeEvent
 * @param event
 * This will be called when this deck-window closes.
 */
void CardWindow::closeEvent (QCloseEvent *event) {
    emit updateStudyTime(timer.getTime());
}

/**
 * @brief CardWindow::on_deleteCardButton_clicked
 * Logic to handle GUI and the deck when a card is deleted.
 */
void CardWindow::on_deleteCardButton_clicked() {

    clearStudyWindow();

    deck->deleteObject(cardDeque.front());
    cardDeque.pop_front();

    if(cardDeque.empty()) {
        ui->studyTab->setEnabled(false);
        ui->windowMessage->setText("No more cards to study.");
    }else {

        ui->questionAreaStudy->addLayout(cardDeque.front()->getQuestion()->toGui());
        activateButtonRow(false);
        ui->showAnswerButton->show();

        std::string line = "Cards left: " + std::to_string(cardDeque.size());
        ui->windowMessage->setText(line.c_str());
    }
}

/**
 * @brief CardWindow::deleteChildWidgets
 * @param item
 * Recursivly removes widgets from a certain QLayoutItem.
 */
void CardWindow::deleteChildWidgets(QLayoutItem *item) {

    QLayout *layout = item->layout();
    if (layout) {
        int itemCount = layout->count();
        for (int i = 0; i < itemCount; i++) {
            deleteChildWidgets(layout->itemAt(i));
        }
    }
    delete item->widget();
}

/**
 * @brief CardWindow::clearStudyWindow
 * Remove the question and answer parts from the GUI.
 */
void CardWindow::clearStudyWindow() {
    deleteChildWidgets(ui->answerAreaStudy);
    deleteChildWidgets(ui->questionAreaStudy);
}

/**
 * @brief CardWindow::on_showAnswerButton_clicked
 * Will show the answer on the GUI when clicked.
 */
void CardWindow::on_showAnswerButton_clicked() {
    ui->answerAreaStudy->addLayout(cardDeque.front()->getAnswer()->toGui());
    ui->showAnswerButton->hide();
    activateButtonRow(true);
}

/**
 * @brief CardWindow::nextCard
 * @param level Button pressed.
 * Handles the logic of all the difficulty buttons.
 * VERY HARD, HARD, MEDIUM, EASY and VERY EASY.
 */
void CardWindow::nextCard(Level level) {

    std::string date;

    switch (level) {
    case VERY_EASY:
        date = cardDeque.front()->updateNextReview(VERY_EASY);
        break;
    case EASY:
        date = cardDeque.front()->updateNextReview(EASY);
        break;
    case MEDIUM:
        date = cardDeque.front()->updateNextReview(MEDIUM);
        break;
    case HARD:
        date = cardDeque.front()->updateNextReview(HARD);
        break;
    case VERY_HARD:
        date = cardDeque.front()->updateNextReview(VERY_HARD);
        break;
    }

    clearStudyWindow();
    cardDeque.pop_front();


    if(cardDeque.empty()) {
        ui->studyTab->setEnabled(false);
        ui->windowMessage->setText("No more cards to study.");
        return;
    }

    activateButtonRow(false);
    ui->showAnswerButton->show();


    date = "Last card can be studied again on:" + date + "\n Cards left: " + std::to_string(cardDeque.size());

    ui->windowMessage->setText(date.c_str());
    ui->questionAreaStudy->addLayout(cardDeque.front()->getQuestion()->toGui());
}

/**
 * @brief CardWindow::on_startStudyButton_clicked
 * Change the GUI to study-mode.
 */
void CardWindow::on_startStudyButton_clicked() {
    ui->questionAreaStudy->addLayout(cardDeque.front()->getQuestion()->toGui());
    ui->frame->show();
    ui->sortOption->hide();
    ui->startStudyButton->hide();
}

void CardWindow::on_vhButton_clicked() {
    nextCard(VERY_HARD);
}

void CardWindow::on_hButton_clicked() {
    nextCard(HARD);
}

void CardWindow::on_mButton_clicked() {
    nextCard(MEDIUM);
}

void CardWindow::on_eButton_clicked() {
    nextCard(EASY);
}

void CardWindow::on_veButton_clicked() {
    nextCard(VERY_EASY);
}



