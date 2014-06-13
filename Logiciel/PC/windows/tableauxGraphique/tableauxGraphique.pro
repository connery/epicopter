#-------------------------------------------------
#
# Project created by QtCreator 2014-06-05T13:15:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tableauxGraphique
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    mygraphicsview.cpp

HEADERS  += mainwindow.h \
    form.h \
    mygraphicsview.h

FORMS    += mainwindow.ui \
    form.ui
