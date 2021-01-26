QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /std:c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    cardwindow.cpp \
    deckaddwindow.cpp \
    deckformatexception.cpp \
    deckreader.cpp \
    deckrow.cpp \
    deckwriter.cpp \
    errorwindow.cpp \
    imagepart.cpp \
    linkpart.cpp \
    main.cpp \
    mainwindow.cpp \
    textpart.cpp \
    timer.cpp

HEADERS += \
    card.h \
    cardpart.h \
    cardwindow.h \
    deckaddwindow.h \
    deckformatexception.h \
    deckreader.h \
    deckrow.h \
    deckwriter.h \
    errorwindow.h \
    imagepart.h \
    linkpart.h \
    mainwindow.h \
    smartvector.h \
    textpart.h \
    timer.h

FORMS += \
    cardwindow.ui \
    deckaddwindow.ui \
    deckrow.ui \
    errorwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
