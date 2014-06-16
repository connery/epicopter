#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTabletEvent>
#include <QDebug>

#include <qfile.h>
#include <qtextstream.h>

#include "frm.h"

namespace Ui {
    class Form;
}

class Form : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(Form)
public:
    explicit Form(QWidget *parent = 0);
    virtual ~Form();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Form *m_ui;
    QList<QString> coord;

private slots:
    void on_pushButton_clicked();
    void on_Btnload_clicked();
};

#endif // FORM_H
