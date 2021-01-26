//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include "cardwindow.h"
#include <iostream>
#include <ctime>
#include <filesystem>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
