/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWebView *maWeb;
    QWebView *webView;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnMap;
    QPushButton *Btnvalidation;
    QPushButton *cancel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1112, 704);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        maWeb = new QWebView(centralWidget);
        maWeb->setObjectName(QStringLiteral("maWeb"));
        maWeb->setStyleSheet(QStringLiteral(""));
        maWeb->setProperty("url", QVariant(QUrl(QStringLiteral("about:blank"))));

        verticalLayout->addWidget(maWeb);

        webView = new QWebView(centralWidget);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setMinimumSize(QSize(0, 34));
        webView->setStyleSheet(QStringLiteral(""));
        webView->setProperty("url", QVariant(QUrl(QStringLiteral("about:blank"))));

        verticalLayout->addWidget(webView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnMap = new QPushButton(centralWidget);
        btnMap->setObjectName(QStringLiteral("btnMap"));
        btnMap->setStyleSheet(QLatin1String(" QPushButton#btnMap:pressed{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: red;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" } \n"
"\n"
"QPushButton#btnMap{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }"));

        horizontalLayout->addWidget(btnMap);

        Btnvalidation = new QPushButton(centralWidget);
        Btnvalidation->setObjectName(QStringLiteral("Btnvalidation"));
        Btnvalidation->setStyleSheet(QLatin1String(" QPushButton#Btnvalidation:pressed{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: red;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" } \n"
"\n"
" QPushButton#Btnvalidation{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }"));

        horizontalLayout->addWidget(Btnvalidation);

        cancel = new QPushButton(centralWidget);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setStyleSheet(QLatin1String(" QPushButton#cancel:pressed{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: red;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" } \n"
" QPushButton#cancel{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }"));

        horizontalLayout->addWidget(cancel);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1112, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        btnMap->setText(QApplication::translate("MainWindow", "Affmap", 0));
        Btnvalidation->setText(QApplication::translate("MainWindow", "Validation", 0));
        cancel->setText(QApplication::translate("MainWindow", "Quitter", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
