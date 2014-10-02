/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionValider;
    QAction *actionAnnuler;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWebView *maWeb;
    QMenuBar *menuBar;
    QMenu *menuValidation;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1369, 910);
        QPalette palette;
        MainWindow->setPalette(palette);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionValider = new QAction(MainWindow);
        actionValider->setObjectName(QStringLiteral("actionValider"));
        actionValider->setCheckable(false);
        actionValider->setShortcutContext(Qt::WidgetShortcut);
        actionValider->setIconVisibleInMenu(false);
        actionAnnuler = new QAction(MainWindow);
        actionAnnuler->setObjectName(QStringLiteral("actionAnnuler"));
        actionAnnuler->setIconVisibleInMenu(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QPalette palette1;
        QBrush brush(QColor(0, 175, 240, 255));
        brush.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        centralWidget->setPalette(palette1);
        centralWidget->setStyleSheet(QStringLiteral("background-color: rgb(0, 175, 240);"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        maWeb = new QWebView(centralWidget);
        maWeb->setObjectName(QStringLiteral("maWeb"));
        maWeb->setStyleSheet(QStringLiteral(""));
        maWeb->setUrl(QUrl(QStringLiteral("about:blank")));

        verticalLayout->addWidget(maWeb);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1369, 21));
        QPalette palette2;
        menuBar->setPalette(palette2);
        menuValidation = new QMenu(menuBar);
        menuValidation->setObjectName(QStringLiteral("menuValidation"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QPalette palette3;
        mainToolBar->setPalette(palette3);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuValidation->menuAction());
        menuValidation->addAction(actionValider);
        menuValidation->addAction(actionAnnuler);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionValider->setText(QApplication::translate("MainWindow", "valider", 0));
        actionAnnuler->setText(QApplication::translate("MainWindow", "annuler", 0));
        menuValidation->setTitle(QApplication::translate("MainWindow", "validation", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
