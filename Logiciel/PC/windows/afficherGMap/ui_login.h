/********************************************************************************
** Form generated from reading ui file 'login.ui'
**
** Created: Fri 28. Mar 15:29:41 2014
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

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
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(176, 127);
        verticalLayout = new QVBoxLayout(Login);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(Login);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lblLogin = new QLineEdit(Login);
        lblLogin->setObjectName(QString::fromUtf8("lblLogin"));

        horizontalLayout->addWidget(lblLogin);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lblPassword = new QLineEdit(Login);
        lblPassword->setObjectName(QString::fromUtf8("lblPassword"));

        horizontalLayout_2->addWidget(lblPassword);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        BtnLogin = new QPushButton(Login);
        BtnLogin->setObjectName(QString::fromUtf8("BtnLogin"));

        horizontalLayout_3->addWidget(BtnLogin);

        BtnQuit = new QPushButton(Login);
        BtnQuit->setObjectName(QString::fromUtf8("BtnQuit"));

        horizontalLayout_3->addWidget(BtnQuit);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Login", "Login       ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Login", "Password", 0, QApplication::UnicodeUTF8));
        BtnLogin->setText(QApplication::translate("Login", "Login", 0, QApplication::UnicodeUTF8));
        BtnQuit->setText(QApplication::translate("Login", "Quit", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Login);
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
