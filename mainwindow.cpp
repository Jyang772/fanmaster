#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Default Values
    critTemp = 105;
    sleepTime = 10;
    safeTemp = 58;


    ui->setupUi(this);
    timer = new QTimer(this);
    fanMaster = new Controller();
    fanManual = new Controller();

    fanManual->moveToThread(pThread);
    pThread->start();

    connect(timer,SIGNAL(timeout()),this,SLOT(checkTemp()));
    timer->start(sleepTime*1000);

    connect(fanMaster,SIGNAL(setText(std::string)),this,SLOT(set_Label(std::string)));


    //Initial
    fanMaster->criticalTemp = critTemp;
    fanMaster->safeTemp = safeTemp;
    ui->critBox->setValue(critTemp);
    ui->safeBox->setValue(safeTemp);
    ui->sleepBox->setValue(sleepTime);

    checkTemp();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_critBox_editingFinished()
{
    ui->critBox->setMinimum(ui->safeBox->value());
    critTemp = ui->critBox->value();
}

void MainWindow::on_safeBox_editingFinished()
{
    safeTemp = ui->safeBox->value();
}


void MainWindow::on_sleepBox_editingFinished()
{
    sleepTime = ui->sleepBox->value();

}

void MainWindow::updateLCD(){

    int temp = fanManual->getTemperature()/1000;
    if(temp < critTemp)
    ui->lcdNumber->setPalette(Qt::green);
    else
        ui->lcdNumber->setPalette(Qt::red);
    ui->lcdNumber->display(fanManual->getTemperature()/1000);
}

void MainWindow::checkTemp(){

    fanMaster->fans();
    //ui->statusBar->showMessage(fanMaster-);
}

void MainWindow::set_Label(std::string string){
    ui->infoBox->append(QString::fromStdString(string));
}

void MainWindow::on_pushButton_clicked()
{
    //char time[20];

    fanMaster->criticalTemp = critTemp;
    fanMaster->safeTemp = safeTemp;
    fanMaster->fans();
    timer->setInterval(sleepTime*1000);
    //fanMaster->getTime(time);
    //printf("TIME: %s",time);
    ui->infoBox->append("Settings Applied!\n");


}


void MainWindow::on_Auto_tabBarClicked(int index)
{
    QTimer *timer = new QTimer();
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateLCD()));


}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "currentindex: " + QString::number(ui->comboBox->currentIndex());
    if(ui->comboBox->currentIndex() == 0)
    {
        timer->start();
        fanMaster->manual = 0;
        ui->infoBox->append("Manual Control Level: auto");
    }
    else{
        timer->stop();
        ui->infoBox->append("Manual Control Level: " + ui->comboBox->currentIndex());
    }

    fanMaster->change_speed(ui->comboBox->currentIndex());


}
