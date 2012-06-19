#-------------------------------------------------
#
# Project created by QtCreator 2012-06-16T21:57:03
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = personal-qt
TEMPLATE = app


SOURCES += src/main.cpp\
        src/maindialog.cpp \
    src/httpdaemon.cpp \
    src/databasemanager.cpp

HEADERS  += src/maindialog.h \
    src/httpdaemon.h \
    src/databasemanager.h \
    src/constants.h

FORMS    += src/maindialog.ui

RESOURCES += \
    personal-qt.qrc
