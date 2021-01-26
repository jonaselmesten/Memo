//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef DECKADDWINDOW_H
#define DECKADDWINDOW_H

#include <QDialog>

namespace Ui {
class DeckAddWindow;
}
/**
 * @brief The DeckAddWindow class
 * Class the handles the window for adding new decks.
 */
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
