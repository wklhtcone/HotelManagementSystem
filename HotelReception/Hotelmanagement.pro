#-------------------------------------------------
#
# Project created by QtCreator 2018-07-15T14:32:37
#
#-------------------------------------------------

QT       += core gui
LIBS += -lpthread libwsock32 libws2_32
RC_ICONS =app.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hotelmanagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    chooseroom.cpp \
    reservepage.cpp \
    roomtype.cpp \
    singleitem.cpp \
    ClientConnector.cpp \
    Client.cpp \
    choosethread.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    chooseroom.h \
    reservepage.h \
    roomtype.h \
    singleitem.h \
    DataStruct.h \
    ClientConnector.h \
    Client.h \
    head.h \
    choosethread.h \
    logindialog.h

FORMS    += mainwindow.ui \
    chooseroom.ui \
    reservepage.ui \
    roomtype.ui \
    singleitem.ui \
    logindialog.ui

RESOURCES += \
    images.qrc
