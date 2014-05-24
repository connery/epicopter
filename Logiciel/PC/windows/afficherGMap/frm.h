#ifndef FRM_H
#define FRM_H

#include <QWidget>
#include <QFileDialog>
#include <QXmlStreamWriter>


namespace Ui {
    class frm;
}

class frm : public QWidget
{
    Q_OBJECT

public:
    explicit frm(QWidget *parent = 0);
    ~frm();

private:
    Ui::frm *ui;

private slots:
    void on_btnsave_clicked();
};

#endif // FRM_H
