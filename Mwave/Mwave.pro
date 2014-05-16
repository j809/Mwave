#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T23:48:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mwave
TEMPLATE = app


SOURCES += main.cpp\
        dashboard.cpp \
    terminal.cpp \
    quitdialog.cpp \
    voicedialog.cpp \
    workerthread.cpp \
    intro.cpp \
    reminder.cpp \
    setreminder.cpp

HEADERS  += dashboard.h \
    terminal.h \
    quitdialog.h \
    voicedialog.h \
    workerthread.h \
    intro.h \
    reminder.h \
    setreminder.h

FORMS    += dashboard.ui \
    terminal.ui \
    quitdialog.ui \
    voicedialog.ui \
    intro.ui \
    reminder.ui \
    setreminder.ui

RESOURCES += \
    images.qrc

OTHER_FILES +=
