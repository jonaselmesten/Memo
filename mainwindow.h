//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <filesystem>
#include "deckaddwindow.h"
#include "deckrow.h"
#include "smartvector.h"

namespace fs = std::filesystem;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * The class that holds all the logic for the main window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void closeEvent (QCloseEvent *event);

    void saveDecks();

    void loadDecks();

private slots:
    void on_deckAddButton_clicked();
    void addNewDeckLine(QString name);
    void deleteDeck(QString name);

private:
    Ui::MainWindow *ui;
    DeckAddWindow *uiAddDeck;

    std::map<std::string, SmartVector<Card>*> deckMap;

    std::string folderPath;

};
#endif // MAINWINDOW_H
