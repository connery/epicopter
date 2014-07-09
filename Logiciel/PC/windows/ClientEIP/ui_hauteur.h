/********************************************************************************
** Form generated from reading UI file 'hauteur.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HAUTEUR_H
#define UI_HAUTEUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mygraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_Hauteur
{
public:
    QVBoxLayout *verticalLayout;
    MyGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Hauteur)
    {
        if (Hauteur->objectName().isEmpty())
            Hauteur->setObjectName(QStringLiteral("Hauteur"));
        Hauteur->resize(1133, 545);
        verticalLayout = new QVBoxLayout(Hauteur);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new MyGraphicsView(Hauteur);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(Hauteur);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(Hauteur);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Hauteur);
        QObject::connect(pushButton_2, SIGNAL(clicked()), Hauteur, SLOT(close()));

        QMetaObject::connectSlotsByName(Hauteur);
    } // setupUi

    void retranslateUi(QWidget *Hauteur)
    {
        Hauteur->setWindowTitle(QApplication::translate("Hauteur", "Form", 0));
        pushButton->setText(QApplication::translate("Hauteur", "valider", 0));
        pushButton_2->setText(QApplication::translate("Hauteur", "quitter", 0));
    } // retranslateUi

};

namespace Ui {
    class Hauteur: public Ui_Hauteur {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HAUTEUR_H
