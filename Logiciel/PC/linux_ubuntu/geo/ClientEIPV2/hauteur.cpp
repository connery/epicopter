#include "hauteur.h"
#include "ui_hauteur.h"

Hauteur::Hauteur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hauteur)
{
    ui->setupUi(this);
}

Hauteur::~Hauteur()
{
    delete ui;
}

void Hauteur::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
