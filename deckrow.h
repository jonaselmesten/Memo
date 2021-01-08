#ifndef DECKROW_H
#define DECKROW_H

#include "card.h"
#include <QWidget>
#include <vector>

namespace Ui {
class DeckRow;
}

class DeckRow : public QWidget
{
    Q_OBJECT

public:
    explicit DeckRow(QWidget *parent = nullptr);

    void init(QString name, std::vector<Card*> *cards);

    ~DeckRow();

private slots:
    void on_studyButton_clicked();
    void on_removeButton_clicked();

private:
    Ui::DeckRow *ui;
    std::vector<Card*> *cards;
};

#endif // DECKROW_H
