QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    cardwindow.cpp \
    deckaddwindow.cpp \
    deckholder.cpp \
    deckrow.cpp \
    main.cpp \
    mainwindow.cpp \
    textpart.cpp

HEADERS += \
    card.h \
    cardpart.h \
    cardwindow.h \
    deckaddwindow.h \
    deckholder.h \
    deckrow.h \
    mainwindow.h \
    textpart.h

FORMS += \
    cardwindow.ui \
    deckaddwindow.ui \
    deckrow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
