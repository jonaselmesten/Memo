//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include "cardwindow.h"
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //TEMP
    QString as = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QDateTime date = QDateTime::fromString(as, "yyyy-MM-dd");
    date = date.addDays(-5);
    std::cout << as.toStdString() << std::endl;
    std::cout << date.toString("yyyy-MM-dd").toStdString() << std::endl;

    return a.exec();
}
