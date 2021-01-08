#ifndef DECKADDWINDOW_H
#define DECKADDWINDOW_H

#include <QDialog>

namespace Ui {
class DeckAddWindow;
}

class DeckAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DeckAddWindow(QWidget *parent = nullptr);
    ~DeckAddWindow();

    void changeMessageText(QString text);

signals:
    void sendName(QString);

private slots:
    void on_addButton_clicked();

private:
    Ui::DeckAddWindow *ui;
};

#endif // DECKADDWINDOW_H
