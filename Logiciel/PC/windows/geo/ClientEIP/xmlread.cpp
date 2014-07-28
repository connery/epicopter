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

QList<QString> xmlRead::getList()
{
    return list;
}

void xmlRead::lire()
{
   QXmlStreamReader xml;
    QString fichier = QFileDialog::getOpenFileName(this, tr("open File"),"",tr("XML files (*.xml)"));
    QFile file(fichier);
    file.open(QFile::ReadOnly | QFile::Text); // Ouverture du fichier XML en lecture seule et en mode texte
    xml.setDevice(&file); // Initialise l'instance reader avec le flux XML venant de file
   // readNext();//prochain token
    int i = 0;
    while (!xml.atEnd())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
       /* if(token == QXmlStreamReader::StartDocument) {
                    continue;
                }*/
         if(token == QXmlStreamReader::StartElement) {
            /*if (xml.name() == QString::number(i))
            {*/

                QString name = xml.name().toString();
                 //qDebug()<<name;
                if (name == "Latitude" || name == "Longitude" ||
                                      name == "Altitude")
                {
                    list<<xml.readElementText();
                  //  qDebug()<<name+ "euh " + xml.readElementText();
                }
               /*if(xml.tokenType() == QXmlStreamReader::StartElement) {

                            if(xml.name() == "Latitude")
                            {
                            }
                            else if(xml.name() == "Longitude")
                            {
                            list<<xml.readElementText();
                            qDebug()<<xml.readElementText();

                            }
                            else if(xml.name() == "Altitude")
                            {
                            list<<xml.readElementText();
                            qDebug()<<xml.readElementText();

                            }*/
            //}
            }
         //}
    }
    xml.clear();
    file.close();
}
