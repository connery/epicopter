#ifndef HAUTEUR_H
#define HAUTEUR_H

#include <QWidget>

namespace Ui {
class Hauteur;
}

class Hauteur : public QWidget
{
    Q_OBJECT

public:
    explicit Hauteur(QWidget *parent = 0);
    ~Hauteur();

protected:
    void changeEvent(QEvent *e);
      void closeEvent(QCloseEvent *event);


private:
    Ui::Hauteur *ui;
};

#endif // HAUTEUR_H
