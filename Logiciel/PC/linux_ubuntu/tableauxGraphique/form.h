#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_graphicsView_windowIconTextChanged(const QString &iconText);

private:
    Ui::Form *ui;
};

#endif // FORM_H
