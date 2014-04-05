/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lblLogin;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lblPassword;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *BtnLogin;
    QPushButton *BtnQuit;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(176, 127);
        verticalLayout = new QVBoxLayout(Login);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(Login);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lblLogin = new QLineEdit(Login);
        lblLogin->setObjectName(QStringLiteral("lblLogin"));

        horizontalLayout->addWidget(lblLogin);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(Login);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lblPassword = new QLineEdit(Login);
        lblPassword->setObjectName(QStringLiteral("lblPassword"));

        horizontalLayout_2->addWidget(lblPassword);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        BtnLogin = new QPushButton(Login);
        BtnLogin->setObjectName(QStringLiteral("BtnLogin"));

        horizontalLayout_3->addWidget(BtnLogin);

        BtnQuit = new QPushButton(Login);
        BtnQuit->setObjectName(QStringLiteral("BtnQuit"));

        horizontalLayout_3->addWidget(BtnQuit);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", 0));
        label_2->setText(QApplication::translate("Login", "Login       ", 0));
        label->setText(QApplication::translate("Login", "Password", 0));
        BtnLogin->setText(QApplication::translate("Login", "Login", 0));
        BtnQuit->setText(QApplication::translate("Login", "Quit", 0));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
