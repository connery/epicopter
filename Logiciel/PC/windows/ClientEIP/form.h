#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QTabletEvent>

#include <qfile.h>
#include <qtextstream.h>

#include <QDebug>

#include <QDir>

#include "sender.h"
#include "frm.h"
#include "xmlread.h"

namespace Ui {
    class Form;
}

class Form : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(Form)
public:
    explicit Form(QWidget *parent = 0);
    virtual ~Form();
    void setId(int mapid);
    void setSender(Sender *s1);
    QString getCurrentDir();
    void dragTable();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Form *m_ui;
    Sender *s;
    int id;
      QList<QString> coord;

private slots:
    void on_pushButton_clicked();
    void on_Btnload_clicked();
    void on_pushButton_2_clicked();
};

#endif // FORM_H
