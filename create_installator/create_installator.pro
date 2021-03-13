#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T13:14:22
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++1z

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = create_installator

TEMPLATE = app

win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../build/release
else:win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../build/debug/

include($$PWD/../parser/parser.pri)

SOURCES += main.cpp\
        filesystem.cpp \
        mainwindow.cpp \
        message.cpp \     
        readinstallator.cpp \
        readuninstallator.cpp

HEADERS  += mainwindow.h \
    data_struct.h \
    filesystem.h \
    message.h \   
    readinstallator.h \
    readuninstallator.h

FORMS += create_installator.ui
