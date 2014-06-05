#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::load()
{
    ui->graphicsView->setGeometry(QRect(0, 0, 250, 250));


    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,250,250);

    ligne = new QGraphicsLineItem(0, 0, 230, 230);
    ligne->setFlag( QGraphicsItem::ItemIsMovable);
    scene->addItem(ligne);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("x");

    ui->label->setText(QString::number (ligne->pos().x()));

    ui->label_2->setText(QString::number (ligne->pos().y()));

   // ligne->
}
