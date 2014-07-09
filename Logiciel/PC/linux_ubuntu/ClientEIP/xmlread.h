#ifndef XMLREAD_H
#define XMLREAD_H

#include <QWidget>
#include <QXmlStreamReader>
#include <QFileDialog>

#include <QList>
#include <QString>

#include <QDebug>

namespace Ui {
    class xmlRead;
}

class xmlRead : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(xmlRead)
public:
    explicit xmlRead(QWidget *parent = 0);
    virtual ~xmlRead();
    void    lire();
    QList<QString> getList();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::xmlRead *m_ui;
    QList<QString> list;

};

#endif // XMLREAD_H
