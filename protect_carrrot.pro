#-------------------------------------------------
#
# Project created by QtCreator 2020-05-15T22:59:12
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = protect_carrrot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainscene.cpp \
    mypushbutton.cpp \
    chooselevel.cpp \
    playscene.cpp \
    monster.cpp \
    tower.cpp \
    mypushbutton2.cpp \
    bullet.cpp \
    moveway.cpp \
    bottle.cpp \
    pin.cpp \
    star.cpp \
    bulletbottle.cpp \
    bulletpin.cpp \
    bulletstar.cpp \
    monster1.cpp \
    monster2.cpp \
    monster3.cpp \
    audioplayer.cpp

HEADERS += \
        mainscene.h \
    mypushbutton.h \
    chooselevel.h \
    playscene.h \
    monster.h \
    tower.h \
    mypushbutton2.h \
    bullet.h \
    moveway.h \
    collisioncheck.h \
    bottle.h \
    pin.h \
    star.h \
    bulletbottle.h \
    bulletpin.h \
    bulletstar.h \
    monster1.h \
    monster2.h \
    monster3.h \
    audioplayer.h

FORMS += \
        mainscene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
