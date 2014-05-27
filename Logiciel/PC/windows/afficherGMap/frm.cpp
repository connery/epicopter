#include "frm.h"
#include "ui_frm.h"

frm::frm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frm)
{
    ui->setupUi(this);
    avancement = 0;
    /* tessttttttttttttt  */
    ajout("6666.06666","111111","11111111");
    ajout("222222","2","2");
    ajout("3","3","3");
    ajout("4","4","4");
}

frm::~frm()
{
    delete ui;
}

void frm::on_btnsave_clicked()
{
    ecriture();
    /*
     QString fichier =   QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("XML files (*.xml)"));

     if(fichier.isEmpty())
     return;

    QFile file(fichier);
    //file.setFileName("Trajet.xml");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text )) //ouverture du fichier de sauvegarde en ecriture
        return;


    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Trajet");

    xmlWriter.writeStartElement("Position");


     xmlWriter.writeStartElement("latitude","noeud1");
     xmlWriter.writeTextElement("valeur",ui->txtlatitude->text());
     xmlWriter.writeEndElement();


      xmlWriter.writeStartElement("Longitude","noeud2");
      //xmlWriter.writeAttribute("Longitude",ui->txtlongitude->text());
      xmlWriter.writeTextElement("valeur",ui->txtlongitude->text());
      xmlWriter.writeEndElement();

      xmlWriter.writeStartElement("Altitude","noeud3");
    //  xmlWriter.writeAttribute("Altitude",ui->txtaltitude->text());
      xmlWriter.writeTextElement("valeur",ui->txtaltitude->text());
      xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();

    file.close();

    */

}

void frm::ajout(QString latitude, QString longitude, QString hauteur)
{
    list <<latitude << longitude<<hauteur;
/*    val[avancement][0] =latitude;
    val[avancement][1] =longitude;
    val[avancement][2] =hauteur;
    avancement++;*/
}

void frm::init()
{
}

void frm::ecriture()
{
  QString fichier =   QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("XML files (*.xml)"));

     if(fichier.isEmpty())
     return;

    QFile file(fichier);
    //file.setFileName("Trajet.xml");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text )) //ouverture du fichier de sauvegarde en ecriture
        return;


    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Trajet");

    xmlWriter.writeStartElement("Position");

    QString s;
    foreach(s, list)
    {
        if(avancement % 3 == 0)
        {
            xmlWriter.writeStartElement(QString::number((avancement/3)));

            xmlWriter.writeTextElement("Latitude",s);
        }
        else if (avancement % 3 == 1)
        {
          xmlWriter.writeTextElement("Logitude",s);
        }
        else
        {
          xmlWriter.writeTextElement("Altitude",s);
              xmlWriter.writeEndElement();

        }
        avancement++;
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();

    file.close();

}

void frm::fin()
{

}
