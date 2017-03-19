#-------------------------------------------------
#
# Project created by QtCreator 2016-08-14T09:01:27
#Tan version
# ello
#1
#2
#-------------------------------------------------

QT       += core gui \
            multimedia serialport sql \
            widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JrdGui
TEMPLATE = app


SOURCES += main.cpp\
    APP/Gui/src/jrdgui.cpp \
    APP/Game/Submarine/src/dialog.cpp \
    APP/Game/Submarine/src/enemy.cpp \
    APP/Game/Submarine/src/friend.cpp \
    APP/Game/Submarine/src/game.cpp \
    APP/Game/Submarine/src/health.cpp \
    APP/Game/Submarine/src/player.cpp \
    APP/Game/Submarine/src/score.cpp \
    BSW/Database/src/datalog.cpp \
    BSW/Serial/src/Serial.cpp \


HEADERS  += \
    APP/Gui/api/jrdgui.h \
    APP/Game/Submarine/api/dialog.h \
    APP/Game/Submarine/api/enemy.h \
    APP/Game/Submarine/api/friend.h \
    APP/Game/Submarine/api/game.h \
    APP/Game/Submarine/api/health.h \
    APP/Game/Submarine/api/player.h \
    APP/Game/Submarine/api/score.h \
    BSW/Database/api/datalog.h \
    BSW/Serial/api/Serial.h \


FORMS    += jrdgui.ui

INCLUDEPATH += \
        $$PWD/APP/Gui/api \
        $$PWD/APP/Game/Submarine/api \
        $$PWD/BSW/Database/api \
        $$PWD/BSW/Serial/api \
        $$PWD/APP/Passive/api

RESOURCES += \
        APP/Game/Submarine/cfg/res.qrc
