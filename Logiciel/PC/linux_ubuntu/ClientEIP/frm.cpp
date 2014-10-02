#include "frm.h"
#include "ui_frm.h"

frm::frm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frm)
{
    ui->setupUi(this);
    avancement = 0;

    /*QPalette p;
    p = palette();
    p.setBrush(QPalette::Window, QBrush(QPixmap("/data/blueBackground.png")));
    setPalette(p);*/
}

frm::~frm()
{
    delete ui;
}

void frm::closeEvent(QCloseEvent *event)
{
   //  s->ecrit("END;");
   //  event->accept();
}


QString frm::getCurrentDir(){
    QString CurrentDir = QDir::currentPath();
    return CurrentDir;
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
          xmlWriter.writeTextElement("Longitude",s);
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

void frm::on_pushButton_clicked()
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
              xmlWriter.writeStartElement("p"+QString::number((avancement/3)));

              xmlWriter.writeTextElement("Latitude",s);
          }
          else if (avancement % 3 == 1)
          {
            xmlWriter.writeTextElement("Longitude",s);
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
      this->close();
}
