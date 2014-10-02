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
    m_ui->tableWidget->horizontalHeader()->resizeSections(QHeaderView::Stretch);
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

void Form::closeEvent(QCloseEvent *event)
{
     s->ecrit("END;");
     event->accept();
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
      m_ui->tableWidget->horizontalHeader()->resizeSections(QHeaderView::Stretch);
//    QString ligne ="Longitude \t - \t Latitude \t - \t Hauteur\n";
     QTableWidgetItem *monItem;
      m_ui->tableWidget->setRowCount(coord.size()/3);
      m_ui->tableWidget->horizontalHeader()->sizeIncrement();
    int i = 0,ligne = 0;
    while (i < coord.length()) {
        QString v1,v2,v3;
        v1 = coord[i];
        //qDebug()<<"position"+QString::number(ligne)+"latitude" + v1;

        v2 = coord[i+1];
        //qDebug()<<"longitude"+v2;

        v3 = coord[i+2];
        //qDebug()<<"hauteur"+v3;

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
    QString andwser, yorn, lat, lon, hau;
    coord.clear();
    s->ecrit("VAL;"+QString::number(id)+";");

    while(andwser != ";fin;")
    {
       // qDebug()<<"boucle";
        s->setTaille(55);
        andwser = s->getMsg();
        //qDebug()<<andwser;
        andwser =andwser.mid(andwser.indexOf("VAL;"),andwser.indexOf("EOF;"));
        //qDebug()<<andwser;
        if (andwser.mid(0,4)== "VAL;")
            yorn = "y";
        else
            yorn = "n";

        if (andwser != "VAL;fin;")
        {
        andwser =andwser.mid(andwser.indexOf("VAL;"+4));

            QString tmp = "";
            /* parsing à tester */
                tmp = andwser.mid(andwser.indexOf(";")+1);
                qDebug()<<"andwser : "+andwser;

                lat = tmp.mid(0, lat.indexOf(";"));
                qDebug()<<"lat : "+lat;
                tmp.remove(0,lat.size()+1);

                qDebug()<<"tmp : "+tmp;

                lon = tmp.mid(0,tmp.indexOf(";"));
                lon = lon.mid(0, lon.indexOf(";"));
                // qDebug()<<"lon : "+lon;

                tmp.remove(0,lon.size()+1);
                qDebug()<<"tmp : "+tmp;
                //qDebug()<<"hau : "+hau;

                hau = tmp.mid(0,tmp.indexOf(";"));
                hau = hau.mid(0, hau.indexOf(";"));tmp = "";
                /* parsing à tester */
                tmp = andwser.mid(andwser.indexOf(";")+1);
                qDebug()<<"andwser : "+andwser;

                lat = tmp.mid(0, lat.indexOf(";"));
                qDebug()<<"lat : "+lat;
                tmp.remove(0,lat.size()+1);

                qDebug()<<"tmp : "+tmp;

                lon = tmp.mid(0,tmp.indexOf(";"));
                lon = lon.mid(0, lon.indexOf(";"));
                    // qDebug()<<"lon : "+lon;

                tmp.remove(0,lon.size()+1);
                 qDebug()<<"tmp : "+tmp;
                    //qDebug()<<"hau : "+hau;

                hau = tmp.mid(0,tmp.indexOf(";"));
                hau = hau.mid(0, hau.indexOf(";"));
            coord << lat << lon <<hau;
        }
        else
            break;


        s->ecrit("VAL;"+yorn+";");
         //qDebug()<< andwser;

    }
    qDebug()<<"avant dragtable";
    dragTable();
}

void Form::on_pushButton_2_clicked()
{
    frm *h = new frm();
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
    /*à tester*/
    QString andwser;
     s->ecrit("ENV;"+QString::number(id)+";");

     s->setTaille(55);
     andwser = s->getMsg();
     qDebug()<<andwser;
     andwser =andwser.mid(andwser.indexOf("OK;"),andwser.indexOf("EOF;"));

     int i = 0;

     while(andwser != "NO;" && i < coord.size())
     {
        s->ecrit("ENV;"+coord[i]+";"+coord[i+1]+";"+coord[i+2]+";");
        andwser = s->getMsg();
        andwser =andwser.mid(andwser.indexOf("NO;"),andwser.indexOf("EOF;"));
        i+=3;
     }
     s->ecrit("ENV;FIN;");
}

void Form::on_tableWidget_cellEntered(int row, int column)
{

}

void Form::on_tableWidget_cellChanged(int row, int column)
{
    QTableWidgetItem *monItem;
    monItem =  m_ui->tableWidget->item(row,column);
    QString text;
    text = monItem->text();
    coord[row*3+column] = text;
}

void Form::resizeEvent(QResizeEvent *event)
{
    m_ui->tableWidget->horizontalHeader()->resizeSections(QHeaderView::Stretch);
    m_ui->tableWidget->verticalHeader()->resizeSections(QHeaderView::Stretch);
}

