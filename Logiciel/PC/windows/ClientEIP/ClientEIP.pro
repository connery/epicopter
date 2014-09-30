#-------------------------------------------------
#
# Project created by QtCreator 2014-06-05T10:45:56
#
#-------------------------------------------------

QT       += core gui \
            network \
            webkit \
            xml \
            xmlpatterns \
            sql \
            webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientEIP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    frm.cpp \
    login.cpp \
    protoclient.cpp \
    sender.cpp \
    tcpclientproto.cpp \
    xmlread.cpp \
    mygraphicsview.cpp

HEADERS  += mainwindow.h \
    form.h \
    frm.h \
    login.h \
    protoclient.h \
    sender.h \
    tcpclientproto.h \
    xmlread.h \
    User.h \
    mygraphicsview.h

FORMS    += mainwindow.ui \
    form.ui \
    frm.ui \
    login.ui \
    xmlread.ui
