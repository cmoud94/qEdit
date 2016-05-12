#-------------------------------------------------
#
# Project created by QtCreator 2016-04-02T23:16:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qEdit
TEMPLATE = app

CONFIG += c++11


SOURCES += src/main.cpp \
	src/mainwindow.cpp \
    src/editor.cpp \
    src/preferences.cpp \
    src/help.cpp

HEADERS  += \
	src/mainwindow.h \
    editor.h \
    src/editor.h \
    src/preferences.h \
    help.h \
    src/help.h

RESOURCES += \
	resources.qrc

DISTFILES +=
