QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = S
TEMPLATE = app

DESTDIR = $$PWD/../bin

INCLUDEPATH += $$PWD/..

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        smainwindow.cpp

HEADERS  += smainwindow.h

FORMS    += smainwindow.ui
