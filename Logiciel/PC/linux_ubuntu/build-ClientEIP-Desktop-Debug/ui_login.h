/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lblLogin;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lblPassword;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *BtnLogin;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(719, 492);
        Login->setMinimumSize(QSize(719, 492));
        Login->setMaximumSize(QSize(719, 492));
        Login->setStyleSheet(QStringLiteral("background-color: rgb(0, 175, 240);"));
        verticalLayout = new QVBoxLayout(Login);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 142, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lblLogin = new QLineEdit(Login);
        lblLogin->setObjectName(QStringLiteral("lblLogin"));
        lblLogin->setMinimumSize(QSize(312, 35));
        lblLogin->setMaximumSize(QSize(312, 35));
        lblLogin->setStyleSheet(QLatin1String("background-color: rgb(204, 239, 252);\n"
"padding-left: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font: 10pt;\n"
"border: 0px;"));

        horizontalLayout->addWidget(lblLogin);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        lblPassword = new QLineEdit(Login);
        lblPassword->setObjectName(QStringLiteral("lblPassword"));
        lblPassword->setMinimumSize(QSize(312, 35));
        lblPassword->setMaximumSize(QSize(312, 35));
        lblPassword->setStyleSheet(QLatin1String("QLineEdit#lblPassword:selected{\n"
"    \n"
"background-color: rgb(255, 255, 255);\n"
"padding-left: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font: 10pt;\n"
"border: 0px;\n"
"}\n"
"\n"
"QLineEdit#lblPassword{\n"
"    \n"
"background-color: rgb(204, 239, 252);\n"
"padding-left: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font: 10pt;\n"
"border: 0px;\n"
"}\n"
"\n"
""));

        horizontalLayout_2->addWidget(lblPassword);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        BtnLogin = new QPushButton(Login);
        BtnLogin->setObjectName(QStringLiteral("BtnLogin"));
        BtnLogin->setMinimumSize(QSize(312, 34));
        BtnLogin->setMaximumSize(QSize(312, 34));
        BtnLogin->setStyleSheet(QLatin1String("QPushButton#BtnLogin:pressed{\n"
"    \n"
"	background-color: rgb(12, 125, 175);\n"
"    font: 14px;\n"
"	color:  rgb(95, 169, 202);\n"
"	border:0;\n"
"}\n"
"\n"
" QPushButton#BtnLogin{\n"
"   \n"
"	background-color: rgb(12, 125, 175);\n"
"    font: 14px;\n"
"	color:  rgb(95, 169, 202);\n"
"	border:0;\n"
"\n"
" }"));

        horizontalLayout_3->addWidget(BtnLogin);

        horizontalSpacer_6 = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Logiciel de vol", 0));
        lblLogin->setPlaceholderText(QApplication::translate("Login", "Entrez votre identifiant", 0));
        lblPassword->setPlaceholderText(QApplication::translate("Login", "Mot de passe", 0));
        BtnLogin->setText(QApplication::translate("Login", "Se connecter", 0));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
