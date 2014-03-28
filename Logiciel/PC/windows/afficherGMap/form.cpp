#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Form)
{
    m_ui->setupUi(this);
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

void Form::on_Btnload_clicked()
{
    int j=0;

    QString ligne2 ="Longitude \t - \t Latitude \t - \t Hauteur\n";

    QString fileName = "C:/Users/washco/Documents/afficherGMap/posi.txt";
    QFile fichier(fileName);

    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ligne2 += "peut pas ouvrir";
    }
    else
    {
    QTextStream flux(&fichier);

    QString ligne;


/*
    QStandardItemModel model(2,10,this);
    QStandardItem entete1;
    entete1.setText("latitude");
    entete1.setEditable(false);
    model.setItem(0,0,&entete1);


    QStandardItem entete2;
    entete2.setText("logitude");
    entete2.setEditable(false);
    model.setItem(1,0,&entete2);
    ligne2 +="eu2?";
*/

    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        ligne2 += ligne + "\t\t";


        if (j == 1)
        {
            ligne2+= "\n";
            j=0;

         }
        else
        j++;
       /* ligne2 += "et sinon;";
         // on crée un item==cellule
         QStandardItem item;

         // On définir son texte
         item.setText(ligne);

         // On le met "Read Only"
         item.setEditable(false);
         model.setItem(i,j,&item);
         // Et enfin on l'associe avec notre model
        if (j == 2)
         {
            i++;
            j=0;
        }
        else
            j++;
*/
    }
  //  m_ui->tablePos->setModel(&model);

    
}
    m_ui->textBrowser->setText(ligne2);
}

void Form::on_pushButton_clicked()
{

}
