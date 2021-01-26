//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef DECKROW_H
#define DECKROW_H

#include "card.h"
#include "smartvector.h"
#include "timer.h"
#include <QWidget>
#include <vector>
#include <memory>

namespace Ui {
class DeckRow;
}

/**
 * @brief The DeckRow class
 * Class that represents a single row in the mainwindow when decks are read from file
 * or when added by the user.
 */
class DeckRow : public QWidget
{
    Q_OBJECT

public:
    explicit DeckRow(QWidget *parent = nullptr);

    void init(QString name, SmartVector<Card> &deck);

    ~DeckRow();

private slots:
    void on_removeButton_clicked();
    void changeStudyTime(int seconds);
    void on_studyButton_clicked();

private:
    Ui::DeckRow *ui;
    SmartVector<Card> *deck;
    int time;
};

#endif // DECKROW_H
