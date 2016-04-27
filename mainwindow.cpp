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
    lcd = new QTimer(this);

    status = new QTimer(this);
    fanMaster = new Controller();
    fanManual = new Controller();

    fanManual->moveToThread(pThread);
    pThread->start();

    connect(lcd,SIGNAL(timeout()),this,SLOT(updateLCD()));
    connect(timer,SIGNAL(timeout()),this,SLOT(checkTemp()));
    connect(status,SIGNAL(timeout()),this,SLOT(updateStatus()));
    timer->start(sleepTime*1000);
    status->start(1000);

    connect(fanMaster,SIGNAL(setText(std::string)),this,SLOT(set_Label(std::string)));

    //Initial
    fanMaster->criticalTemp = critTemp;
    fanMaster->safeTemp = safeTemp;
    ui->critBox->setValue(critTemp);
    ui->safeBox->setValue(safeTemp);
    ui->sleepBox->setValue(sleepTime);
    ui->autoSpeed->setCurrentIndex(8);

    char current[40];
    sprintf(current,"%d,%d,%d,%d",sleepTime,safeTemp,critTemp,ui->autoSpeed->currentIndex());
    ui->currentOptions->setText(QString::fromStdString(current));

    checkTemp();

}
	//Destructor for ui object
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
    //int temp = fanMaster->getTemperature()/1000;
    if(temp < critTemp)
        ui->lcdNumber->setPalette(Qt::green);
    else
        ui->lcdNumber->setPalette(Qt::red);
    //ui->lcdNumber->display(fanManual->getTemperature()/1000);
    ui->lcdNumber->display(temp);
}

void MainWindow::checkTemp(){

    fanMaster->fans();
}

void MainWindow::updateStatus(){

    char time[20];
    fanMaster->getTime(time);
    ui->statusBar->showMessage("Temperature: " + QString::number(fanMaster->getTemperature()/1000) + "C " + QString::number(fanMaster->getRPM()) + "RPM Checked at " + time);

}

void MainWindow::set_Label(std::string string){

    ui->infoBox->append(QString::fromStdString(string));
    ui->message->setText(QString::fromStdString(string));

}

void MainWindow::on_pushButton_clicked()
{
    //char time[20];
    FILE *log;
    log = fopen("log","a+");

    fanMaster->criticalTemp = critTemp;
    fanMaster->safeTemp = safeTemp;
    fanMaster->autoSpeedValue = ui->autoSpeed->currentIndex();
    timer->setInterval(sleepTime*1000);
    //fanMaster->getTime(time);
    //printf("TIME: %s",time);

    qDebug() << fanMaster->manual;
    if(fanMaster->manual){
        ui->pushButton->setText("Apply Current Options");
    }
    ui->infoBox->append("Settings Applied!\n");
    if(log != NULL){
        fprintf(log,"Settings Applied!\n");
        fclose(log);
    }

    char current[40];
    sprintf(current,"%d,%d,%d,%d",sleepTime,safeTemp,critTemp,ui->autoSpeed->currentIndex());
    ui->currentOptions->setText(QString::fromStdString(current));

    fanMaster->fans();
    timer->start();

}


void MainWindow::on_Auto_tabBarClicked(int index)
{
    lcd->start(1000);
}

void MainWindow::on_pushButton_2_clicked()
{
    FILE *log;
    log = fopen("log","a+");

    //Bug here that cashes application to crash
    //qDebug() << "currentindex: " + QString::number(ui->comboBox->currentIndex());
    timer->stop(); //Stop timer for infoBox

    if(ui->comboBox->currentIndex() == 0)
    {
        ui->infoBox->append("Manual Control Level: auto");
        if(log != NULL){
            fprintf(log,"Manual Control Level: auto\n");
            fclose(log);
        }

    }
    else{
        int index;

        if(ui->comboBox->currentIndex() == 9)
            index = 0;
        ui->infoBox->append("Manual Control Level: " + index);

        if(log != NULL){
            fprintf(log,"Manual Control Level: %d\n",index);
            fclose(log);
        }
    }

    ui->pushButton->setText("Run Auto Control");
    fanMaster->manual = 1;
    fanMaster->change_speed(ui->comboBox->currentIndex());


}

void MainWindow::on_pushButton_3_clicked()
{
    close();
}
