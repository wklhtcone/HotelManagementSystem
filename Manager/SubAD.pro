#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T20:08:55
#
#-------------------------------------------------



QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SubAD
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
    employee.cpp \
    userinfo.cpp \
    userlog.cpp \
    logtablea.cpp \
    logtableb.cpp \
    add.cpp \
    queryroom.cpp \
    employeeadd.cpp \
    employeequery.cpp \
    tableaquery.cpp \
    tablebquery.cpp \
    modify.cpp \
    employeemodify.cpp \
    sql_odbc.cpp \
    changeprice.cpp \
    managerfunc.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    employee.h \
    userinfo.h \
    userlog.h \
    logtablea.h \
    logtableb.h \
    add.h \
    queryroom.h \
    employeeadd.h \
    employeequery.h \
    tableaquery.h \
    tablebquery.h \
    modify.h \
    employeemodify.h \
    head.h \
    sql_odbc.h \
    changeprice.h \
    managerfunc.h \
    logindialog.h

FORMS    += mainwindow.ui \
    employee.ui \
    userinfo.ui \
    userlog.ui \
    logtablea.ui \
    logtableb.ui \
    add.ui \
    queryroom.ui \
    employeeadd.ui \
    employeequery.ui \
    tableaquery.ui \
    tablebquery.ui \
    modify.ui \
    employeemodify.ui \
    changeprice.ui \
    logindialog.ui

RESOURCES += \
    images.qrc

RC_ICONS = speed.ico
