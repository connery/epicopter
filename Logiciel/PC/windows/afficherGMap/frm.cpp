#include "frm.h"
#include "ui_frm.h"

frm::frm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frm)
{
    ui->setupUi(this);
}

frm::~frm()
{
    delete ui;
}

void frm::on_btnsave_clicked()
{
 QString fichier =   QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("XML files (*.xml)"));

 if(fichier.isEmpty())
     return;

QFile file(fichier);
file.setFileName("Trajet.xml");

if(!file.open(QIODevice::WriteOnly | QIODevice::Text )) //ouverture du fichier de sauvegarde en ecriture
    return;


QXmlStreamWriter xmlWriter(&file);

xmlWriter.setAutoFormatting(true);
xmlWriter.writeStartDocument();

xmlWriter.writeStartElement("Trajet");

    xmlWriter.writeStartElement("Position");

     /* xmlWriter.writeStartElement("Latitude",ui->txtlatitude->text());
      //xmlWriter.writeAttribute("Latitude",ui->txtlatitude->text());
      xmlWriter.writeEndElement();*/

     xmlWriter.writeStartElement("latitude",ui->txtlatitude->text());
     xmlWriter.writeEndElement();

      xmlWriter.writeStartElement("Longitude",ui->txtlongitude->text());
      //xmlWriter.writeAttribute("Longitude",ui->txtlongitude->text());
      xmlWriter.writeEndElement();

      xmlWriter.writeStartElement("Altitude",ui->txtaltitude->text());
    //  xmlWriter.writeAttribute("Altitude",ui->txtaltitude->text());
      xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
xmlWriter.writeEndElement();

xmlWriter.writeEndDocument();

file.close();



}
