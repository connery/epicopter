#ifndef FRM_H
#define FRM_H

#include <QWidget>
#include <QFileDialog>
#include <QXmlStreamWriter>

#include <QList>
#include <QString>

namespace Ui {
    class frm;
}

class frm : public QWidget
{
    Q_OBJECT

public:
    explicit frm(QWidget *parent = 0);
    void ajout(QString latitude, QString longitude, QString hauteur);
    void ecriture();
    void init();
    void fin();
    ~frm();

private:
    Ui::frm *ui;
    QList<QString> list;
    int avancement;

private slots:
    void on_pushButton_clicked();
};

#endif // FRM_H
