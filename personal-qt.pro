#-------------------------------------------------
#
# Project created by QtCreator 2012-06-16T21:57:03
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = personal-qt
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    httpdaemon.cpp

HEADERS  += maindialog.h \
    httpdaemon.h

FORMS    += maindialog.ui

RESOURCES += \
    personal-qt.qrc
