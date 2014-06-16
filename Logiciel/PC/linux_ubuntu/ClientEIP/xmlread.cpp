#include "xmlread.h"
#include "ui_xmlread.h"

xmlRead::xmlRead(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::xmlRead)
{
    m_ui->setupUi(this);
}

xmlRead::~xmlRead()
{
    delete m_ui;
}

void xmlRead::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void xmlRead::lire()
{
 /*   QXmlStreamReader xml;
    QString fichier = QFileDialog::getOpenFileName(this, tr("open File"),"",tr("XML files (*.xml)"));
    QFile file(fichier);
    file.open(QFile::ReadOnly | QFile::Text); // Ouverture du fichier XML en lecture seule et en mode texte
    xml.setDevice(&file); // Initialise l'instance reader avec le flux XML venant de file
    readNext();//prochain token
    while (!xml.atEnd())
    {
        if (xml.isStartElement())
        {
            if (xml.name() == "root")
            {
            }*/
}
