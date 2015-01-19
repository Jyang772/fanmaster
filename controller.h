#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

#include <QObject>
#include <QDebug>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    void fans();
    void change_speed(int);

    void getTime(char*);
    int getTemperature();
    int getRPM();

signals:
    void setText(std::string);


public:
    int safeTemp, criticalTemp; //These need to be set by GUI
    int manual;
    int fansLevel;
    int AUTO = 10;
    int FORCED = 100;
    int errorTemp = 0;
    int autoSpeedValue = 7;

private:
    FILE *log;

};





#endif // CONTROLLER_H
