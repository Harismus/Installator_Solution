#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T13:14:22
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_inst
TEMPLATE = app

win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../build/release/
else:win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../build/debug/

SOURCES += main.cpp\
        filesystem.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    data_struct.h \
    filesystem.h

FORMS += create_installator.ui
