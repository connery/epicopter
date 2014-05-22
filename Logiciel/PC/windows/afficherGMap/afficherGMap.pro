# -------------------------------------------------
# Project created by QtCreator 2013-10-14T14:05:34
# -------------------------------------------------
QT += network \
    webkit \
    xml \
    xmlpatterns \
    sql
TARGET = afficherGMap
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    form.cpp \
    login.cpp \
    protoclient.cpp \
    tcpclientproto.cpp \
    sender.cpp
HEADERS += mainwindow.h \
    form.h \
    login.h \
    protoclient.h \
    packet.h \
    tcpclientproto.h \
    sender.h \
    User.h
FORMS += mainwindow.ui \
    form.ui \
    login.ui
OTHER_FILES += map.html \
    my_php.php \
    posi.txt \
    config.inc.php \
    updateUser.php \
    login.php \
    login.html
