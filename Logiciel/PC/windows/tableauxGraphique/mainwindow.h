#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void load();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
     QGraphicsLineItem *ligne;
};

#endif // MAINWINDOW_H
