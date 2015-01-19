#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>

#include "controller.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_critBox_editingFinished();

    void on_safeBox_editingFinished();

    void on_sleepBox_editingFinished();

    void on_pushButton_clicked();

    void set_Label(std::string);

    void checkTemp();

    void on_Auto_tabBarClicked(int index);

    void updateLCD();

    void updateStatus();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    //Fan Controller
    //TODO: Put in separate class

    int safeTemp;
    int critTemp;
    int sleepTime;

    QTimer *timer;
    QTimer *status;

    Controller *fanMaster;
    Controller *fanManual;

    QThread *pThread = new QThread();
    FILE *log;

};

#endif // MAINWINDOW_H
