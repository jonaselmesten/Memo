//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include "card.h"
#include "smartvector.h"
#include <QMainWindow>
#include <vector>
#include <filesystem>
#include <deque>
#include "timer.h"

namespace fs = std::filesystem;

namespace Ui {
class CardWindow;
}

enum Type {TEXT = 0, IMAGE = 1, LINK = 2};
enum Tab {STUDY, NEW};
enum Side {QUESTION, ANSWER};

/**
 * @brief The CardWindow class
 * This class handles the GUI and all the logic for when a certain deck is being studied/updated with new cards.
 */
class CardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CardWindow(QWidget *parent = nullptr);

    ~CardWindow();

    void init(QString name, SmartVector<Card> *deck);

signals:
    void updateStudyTime(int);

private slots:
    void on_newQuestionType_currentIndexChanged(int index);

    void on_newAnswerType_currentIndexChanged(int index);

    void on_newQuestionImageButton_clicked();

    void on_newAnswerImageButton_clicked();

    void on_newClearButton_clicked();

    void on_newAddButton_clicked();

    void on_sortOption_currentIndexChanged(int index);

    void on_showAnswerButton_clicked();

    void on_vhButton_clicked();

    void on_hButton_clicked();

    void on_mButton_clicked();

    void on_eButton_clicked();

    void on_veButton_clicked();

    void on_deleteCardButton_clicked();

    void on_startStudyButton_clicked();

private:

    void closeEvent (QCloseEvent *event);

    void clearStudyWindow();

    bool textEditIsEmpty(Side side);

    void changeVisible(Type type, Side side);

    void setTabs();

    void saveImagePath(Side side);

    void nextCard(Level level);

    void activateButtonRow(bool active);

    void deleteChildWidgets(QLayoutItem *item);

    Type question;
    Type answer;
    Tab currentTab;

    Ui::CardWindow *ui;

    SmartVector<Card> *deck;
    std::deque<Card*> cardDeque;

    QString name;

    fs::path questionImagePath;
    fs::path answerImagePath;

    Timer timer;
};

#endif // CARDWINDOW_H
