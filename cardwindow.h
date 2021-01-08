#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include "card.h"
#include <QMainWindow>
#include <vector>

namespace Ui {
class CardWindow;
}

enum Type {TEXT = 0, IMAGE = 1, IMAGE_TEXT = 2};
enum Tab {STUDY, EDIT, NEW};
enum Side {QUESTION, ANSWER};

class CardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CardWindow(QWidget *parent = nullptr);

    ~CardWindow();

    void init(QString name, std::vector<Card*> *cards);



private slots:
    void on_newQuestionType_currentIndexChanged(int index);

    void on_newAnswerType_currentIndexChanged(int index);

    void on_newQuestionImageButton_clicked();

    void on_newAnswerImageButton_clicked();

    void on_newClearButton_clicked();

    void on_newAddButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_sortOption_currentIndexChanged(int index);

private:

    void changeVisible(Tab tab, Type type, Side side);

    void setTabs();

    Type question;
    Type answer;
    Tab current_tab;

    Ui::CardWindow *ui;

    QString name;
    std::vector<Card*> *cards;
};

#endif // CARDWINDOW_H
