/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *Btnload;
    QPushButton *btnEnvoyer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *btnCancel;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(531, 330);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(Form);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setStyleSheet(QLatin1String("border-style: outset;\n"
"border-width: 3px;\n"
"border-radius: 10px;\n"
"border-color: white;"));
        tableWidget->setRowCount(0);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Btnload = new QPushButton(Form);
        Btnload->setObjectName(QStringLiteral("Btnload"));
        Btnload->setStyleSheet(QLatin1String(" QPushButton#Btnload:pressed{\n"
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
" QPushButton#Btnload{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: beige;\n"
"     font: bold 12px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }"));

        horizontalLayout->addWidget(Btnload);

        btnEnvoyer = new QPushButton(Form);
        btnEnvoyer->setObjectName(QStringLiteral("btnEnvoyer"));
        btnEnvoyer->setStyleSheet(QLatin1String(" QPushButton#btnEnvoyer:pressed{\n"
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
"\n"
" QPushButton#btnEnvoyer{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: beige;\n"
"     font: bold 12px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }"));

        horizontalLayout->addWidget(btnEnvoyer);

        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
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
"\n"
" QPushButton#pushButton_2{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: beige;\n"
"     font: bold 12px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));
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
"\n"
" QPushButton#pushButton{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: beige;\n"
"     font: bold 12px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }"));

        horizontalLayout->addWidget(pushButton);

        btnCancel = new QPushButton(Form);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setStyleSheet(QLatin1String(" QPushButton#btnCancel:pressed{\n"
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
"\n"
" QPushButton#btnCancel{\n"
"    color: rgb(255, 255, 255);\n"
"	 background-color: rgb(64, 84, 197);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: beige;\n"
"     font: bold 12px;\n"
"     min-width: 5em;\n"
"     padding: 6px;\n"
" }"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Form);
        QObject::connect(btnCancel, SIGNAL(clicked()), Form, SLOT(close()));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Form", "Latitude", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Form", "Longitude", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Form", "Hauteur", 0));
        Btnload->setText(QApplication::translate("Form", "Load parcourt", 0));
        btnEnvoyer->setText(QApplication::translate("Form", "Envoyer", 0));
        pushButton_2->setText(QApplication::translate("Form", "Exporter", 0));
        pushButton->setText(QApplication::translate("Form", "Validation plan", 0));
        btnCancel->setText(QApplication::translate("Form", "Annuler", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
