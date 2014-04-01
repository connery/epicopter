/********************************************************************************
** Form generated from reading ui file 'form.ui'
**
** Created: Tue 1. Apr 20:18:00 2014
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout;
    QPushButton *Btnload;
    QPushButton *btnEnvoyer;
    QPushButton *btnCancel;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(Form);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setEnabled(true);

        verticalLayout->addWidget(textBrowser);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Btnload = new QPushButton(Form);
        Btnload->setObjectName(QString::fromUtf8("Btnload"));

        horizontalLayout->addWidget(Btnload);

        btnEnvoyer = new QPushButton(Form);
        btnEnvoyer->setObjectName(QString::fromUtf8("btnEnvoyer"));

        horizontalLayout->addWidget(btnEnvoyer);

        btnCancel = new QPushButton(Form);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Form);
        QObject::connect(btnCancel, SIGNAL(clicked()), Form, SLOT(close()));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        Btnload->setText(QApplication::translate("Form", "Load parcourt", 0, QApplication::UnicodeUTF8));
        btnEnvoyer->setText(QApplication::translate("Form", "Envoyer", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("Form", "Annuler", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
