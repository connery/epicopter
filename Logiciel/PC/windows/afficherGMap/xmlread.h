#ifndef XMLREAD_H
#define XMLREAD_H

#include <QtGui/QWidget>
#include <QXmlStreamReader>
#include <QFileDialog>

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


protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::xmlRead *m_ui;
};

#endif // XMLREAD_H
