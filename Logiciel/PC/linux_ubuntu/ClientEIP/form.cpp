#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Form)
{
    m_ui->setupUi(this);
    QPalette p;
    p = palette();
    p.setBrush(QPalette::Window, QBrush(QPixmap(getCurrentDir()+"/data/blueBackground.png")));
    setPalette(p);
    this->show();
}

Form::~Form()
{
    delete m_ui;
}

void Form::changeEvent(QEvent *e)
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

void Form::setSender(Sender *s1)
{
    s = s1;
}

QString Form::getCurrentDir(){
    QString CurrentDir = QDir::currentPath();
    return CurrentDir;
}

void Form::setId(int mapid)
{
    id = mapid;
}

void Form::on_Btnload_clicked()
{
    /*int j=0;

    QString ligne2 ="Longitude \t - \t Latitude \t - \t Hauteur\n";

    QString fileName = getCurrentDir()+"/data/posi.txt";
    QFile fichier(fileName);

    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ligne2 += "peut pas ouvrir";
    }
    else
    {
    QTextStream flux(&fichier);

    QString ligne;

    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        ligne2 += ligne + "\t";


        if (j == 1)
        {
            ligne2+= "\n";
            j=0;

         }
        else
        j++;
    }
  //  m_ui->tablePos->setModel(&model);

    
}
    m_ui->textBrowser->setText(ligne2);*/
    xmlRead r;
    r.lire();
    coord.clear();
    coord += r.getList();
    dragTable();
}

void Form::dragTable()
{
//    QString ligne ="Longitude \t - \t Latitude \t - \t Hauteur\n";
     QTableWidgetItem *monItem;
      m_ui->tableWidget->setRowCount(coord.size()/3);
      m_ui->tableWidget->horizontalHeader()->sizeIncrement();
    int i = 0,ligne = 0;
    while (i < coord.length()) {
        QString v1,v2,v3;
        v1 = coord[i];
        qDebug()<<"position"+QString::number(ligne)+"latitude" + v1;

        v2 = coord[i+1];
        qDebug()<<"longitude"+v2;

        v3 = coord[i+2];
        qDebug()<<"hauteur"+v3;

       // ligne+= v1+" \t - \t "+v2+" \t - \t "+v3+"\n";
        monItem = new QTableWidgetItem(v1);
        m_ui->tableWidget->setItem(ligne,0,monItem);
        monItem = new QTableWidgetItem(v2);
        m_ui->tableWidget->setItem(ligne,1,monItem);
        monItem = new QTableWidgetItem(v3);
        m_ui->tableWidget->setItem(ligne,2,monItem);

        ligne++;
        i+= 3;

    }
     //m_ui->textBrowser->setText(ligne);
}


void Form::on_pushButton_clicked()
{
    QString andwser, yorn;
    s->ecrit("VAL;"+QString::number(id)+";");

    while(andwser != "VAL;fin;")
    {
        s->setTaille(55);
        andwser = s->getMsg();
        qDebug()<<andwser;
        andwser =andwser.mid(andwser.indexOf("VAL;"),andwser.indexOf("EOF;"));
        qDebug()<<andwser;
        if (andwser.mid(0,4)== "VAL;")
            yorn = "y";
        else
            yorn = "n";
        s->ecrit("VAL;"+yorn+";");


    }
}

void Form::on_pushButton_2_clicked()
{
/*    frm *xml = new frm();
    xml->show();*/
    //creer une list de position ...
    coord << "05" << "10" << "15";
    coord << "25" << "30" << "35";
    coord << "45" << "50" << "55";
    coord << "65" << "70" << "75";
    frm *h = new frm();
    // boucle de lecture de la list
            //utiliser la fonction ajout
    int i = 0;
    while (i < coord.length()) {
        QString v1,v2,v3;
        v1 = coord[i];
        v2 = coord[i+1];
        v3 = coord[i+2];
        h->ajout(v1, v2, v3);
        i+= 3;
    }
    h->show();

}

void Form::on_btnEnvoyer_clicked()
{

}
