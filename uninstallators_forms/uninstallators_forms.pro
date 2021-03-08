#-------------------------------------------------
#
# Project created by QtCreator 2017-01-23T10:01:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uninstallators_forms
TEMPLATE = app
QMAKE_LFLAGS_RELEASE += -static -static-libgcc

win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../build/release/
else:win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../build/debug/

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    proto.h
QMAKE_LFLAGS_RELEASE += -static -static-libgcc
