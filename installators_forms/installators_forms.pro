#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T09:24:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = installators_forms
TEMPLATE = app

QMAKE_LFLAGS_RELEASE += -static -static-libgcc

win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../build/release/
else:win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../build/debug/

SOURCES += main.cpp\
    firstwindow.cpp \
    installator.cpp \
    mainwindow.cpp \
    pathwindow.cpp \
    uninstallator.cpp

HEADERS  += \
    firstwindow.h \
    installator.h \
    mainwindow.h \
    pathwindow.h \
    proto.h \
    uninstallator.h

FORMS    += \
    pathwindow.ui

RESOURCES += \
    resource.qrc



