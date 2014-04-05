#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap("../affmap/2015_logo_epicopter.png"));
    //QGridLayout *layout = new QGridLayout( this );

    //
    // Boutons
    //
   /*
    QPushButton *btnLeft = new QPushButton( "Left", this );
    QPushButton *btnRight = new QPushButton( "Right", this );
    QPushButton *btnUp = new QPushButton( "Up", this );
    QPushButton *btnDown = new QPushButton( "Down", this );
    QPushButton *btnHome = new QPushButton( "Home", this );

    connect( btnLeft, SIGNAL(clicked()), this, SLOT(goLeft()) );
    connect( btnRight, SIGNAL(clicked()), this, SLOT(goRight()) );
    connect( btnUp, SIGNAL(clicked()), this, SLOT(goUp()) );
    connect( btnDown, SIGNAL(clicked()), this, SLOT(goDown()) );
    connect( btnHome, SIGNAL(clicked()), this, SLOT(goHome()) );

    layout->addWidget( btnLeft, 3, 1 );
    layout->addWidget( btnRight, 3, 3 );
    layout->addWidget( btnUp, 2, 2 );
    layout->addWidget( btnDown, 4, 2 );
    layout->addWidget( btnHome, 3, 2 );
*/


    //
    // pageweb
    //


 //   layout->addWidget( mView, 1, 4, 5, 1 );
    //form = new QWidget()

}




MainWindow::~MainWindow()
{
    delete ui;
}
/*
MainWindow::geoCode(QString local)
{
   QUrl geoCodeUrl("http://maps.google.com/maps/geo");
   geoCodeUrl.addQueryItem("q", local);
   geoCodeUrl.addQueryItem("output", "csv");
   geoCodeUrl.addQueryItem("key", "GOOGLE_MAPS_KEY");
   manager->get( QNetworkRequest(geoCodeUrl) );
}
*/

void MainWindow::SetAd(QString ad)
{
    this->adresse = ad;
}

void MainWindow::load()
{
   /*
    mView = new QWebView( this );
    mView->settings()->setAttribute( QWebSettings::JavascriptEnabled, true );
    QString fileName = qApp->applicationDirPath() + "/map.html";
    if( !QFile(fileName).exists() ) {
        qDebug() << "File not found:" << fileName;
    }

    QUrl url = QUrl::fromLocalFile( fileName );
    mView->load( url );
    QGridLayout *layout = new QGridLayout(ui->widgetMap);
    //layout->addWidget( mView,1,1,5,1);
    layout->addWidget( mView);
   // layout->setSizeConstraint(

*/
}

void MainWindow::on_btnMap_clicked()
{
   QDesktopServices::openUrl(QUrl("../affmap/map.html", QUrl::TolerantMode));
   //QDesktopServices::openUrl(QUrl(adresse, QUrl::TolerantMode));
 //   load();
}

void MainWindow::on_Btnvalidation_clicked()
{
   Form *parcour = new Form();
}

void MainWindow::on_btnLogin_clicked()
{
  // Login *log = new Login();
}
