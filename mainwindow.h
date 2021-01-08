#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include "deckaddwindow.h"
#include "deckholder.h"
#include "deckrow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_deckAddButton_clicked();
    void add_new_deck_line(const QString &name);
    void deleteDeck(const QString &name);

private:
    Ui::MainWindow *ui;
    DeckAddWindow *ui_add_deck;

    DeckHolder deck_holder;
};
#endif // MAINWINDOW_H
