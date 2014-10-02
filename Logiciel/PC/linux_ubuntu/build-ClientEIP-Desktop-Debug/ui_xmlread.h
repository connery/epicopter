/********************************************************************************
** Form generated from reading UI file 'xmlread.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XMLREAD_H
#define UI_XMLREAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xmlRead
{
public:

    void setupUi(QWidget *xmlRead)
    {
        if (xmlRead->objectName().isEmpty())
            xmlRead->setObjectName(QStringLiteral("xmlRead"));
        xmlRead->resize(400, 300);

        retranslateUi(xmlRead);

        QMetaObject::connectSlotsByName(xmlRead);
    } // setupUi

    void retranslateUi(QWidget *xmlRead)
    {
        xmlRead->setWindowTitle(QApplication::translate("xmlRead", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class xmlRead: public Ui_xmlRead {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XMLREAD_H
