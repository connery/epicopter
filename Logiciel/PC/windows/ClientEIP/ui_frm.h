/********************************************************************************
** Form generated from reading UI file 'frm.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_H
#define UI_FRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frm
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *frm)
    {
        if (frm->objectName().isEmpty())
            frm->setObjectName(QStringLiteral("frm"));
        frm->resize(282, 128);
        label = new QLabel(frm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 261, 21));
        QFont font;
        font.setFamily(QStringLiteral("KacstQurn"));
        font.setPointSize(12);
        label->setFont(font);
        pushButton = new QPushButton(frm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 70, 101, 27));
        pushButton->setStyleSheet(QLatin1String(" QPushButton#pushButton:pressed{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: red;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }\n"
" \n"
"QPushButton#pushButton{\n"
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
        pushButton_2 = new QPushButton(frm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 70, 101, 27));
        pushButton_2->setStyleSheet(QLatin1String(" QPushButton#pushButton_2:pressed{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: red;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }\n"
" \n"
"QPushButton#pushButton_2{\n"
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

        retranslateUi(frm);
        QObject::connect(pushButton_2, SIGNAL(clicked()), frm, SLOT(close()));

        QMetaObject::connectSlotsByName(frm);
    } // setupUi

    void retranslateUi(QWidget *frm)
    {
        frm->setWindowTitle(QApplication::translate("frm", "frm", 0));
        label->setText(QApplication::translate("frm", "Voulez vous exporter le fichier ?", 0));
        pushButton->setText(QApplication::translate("frm", "Oui", 0));
        pushButton_2->setText(QApplication::translate("frm", "Non", 0));
    } // retranslateUi

};

namespace Ui {
    class frm: public Ui_frm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_H
