#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTabletEvent>
#include <QtGui>
#include <qfile.h>
#include <qtextstream.h>

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

private slots:
    void on_pushButton_clicked();
    void on_Btnload_clicked();
};

#endif // FORM_H
