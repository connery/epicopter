#-------------------------------------------------
#
# Project created by QtCreator 2014-03-28T09:35:18
#
#-------------------------------------------------

QT       += core gui\
            network \
            webkitwidgets\
            xml \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = affmap
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    main.cpp \
    login.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    login.h \
    form.h

FORMS    += mainwindow.ui \
    login.ui \
    form.ui

OTHER_FILES +=\
    updateUser.php \
    traitement.php \
    test.txt \
    posi.txt \
    my_php.php \
    map.html \
    Makefile.Release \
    Makefile.Debug \
    Makefile \
    login.php \
    login.html \
    index.html \
    GMaps.js \
    config.inc.php \
    batelco.txt \
    bakuphtml.txt \
    bakup.html \
    back2.txt \
    à_pk.txt \
    affmap.pro.user \
    2015_logo_epicopter - Copie.png \
    2015_logo_epicopter2.png \
    2015_logo_epicopter.png
