#include "mainwindow.h"
#include <QApplication>

//C Level
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "controller.h"

//Catch signal
//http://stackoverflow.com/questions/13010531/leaving-an-infinite-while-loop-in-c

volatile sig_atomic_t stop;

void inthand(int signum){
    stop = 1;
}

void monitorLoop(){

    stop = 0;
    signal(SIGINT,inthand);
    while(1){
        printf("LOOPING!!\n");
        sleep(2);

        if(stop)
            break;

    }
    printf("Exited Loop Gracefully!\n");
    return;
}

void consoleMode(){

    int AUTO = 7;
    int FULL = 8;
    int fansLevel = AUTO;
    int temp, safeTemp=57, criticalTemp=60,sleepTime=120;
    FILE* tempInput;


    printf("Enter sleep time: ");
    scanf("%d",&sleepTime);

    printf("Enter safe temperature: ");
    scanf("%d",&safeTemp);

    printf("Enter critical temperature: ");
    scanf("%d",&criticalTemp);

    printf("----------------------------------------\n");
    printf("   Safe: %d, Critical: %d, Sleep: %d\n",safeTemp, criticalTemp,sleepTime);
    printf("----------------------------------------\n");

        while(1){
            signal(SIGINT,inthand);
            if(stop)
                break;
            tempInput = fopen("/sys/class/thermal/thermal_zone1/temp","r");
            fscanf(tempInput,"%d",&temp);
            temp /= 1000;
            fclose(tempInput);
            printf("Temperature: %d\n",temp);
            if(temp>=criticalTemp && fansLevel==AUTO){
                system("date '+.:: %H:%M:%S ::.'");
                printf("Temperature is %d, critical is %d\n",temp,criticalTemp);
                printf("Turning fans to full-speed!\n");
                printf("----------------------------------------\n");
                system("echo level full-speed > /proc/acpi/ibm/fan");
                fansLevel = FULL;
            }
            else if(temp<=safeTemp && fansLevel==FULL){
                system("date '+.:: %H:%M:%S ::.'");
                printf("Temperature is %d, safe is %d\n",temp,safeTemp);
                printf("Turning fans to auto!\n");
                printf("----------------------------------------\n");
                system("echo level auto > /proc/acpi/ibm/fan");
                fansLevel = AUTO;
            }
            sleep(1);
        }
}

int main(int argc, char *argv[])
{


    if(argc > 1){


        //Ghetto way of parsing
        for(int i=0; i<argc; i++){
            if(argv[i][0] == '-' && argv[i][1] != '-'){

                switch(argv[i][1]){
                case 'c':
                    printf("Console Mode Engaged!\n");
                    consoleMode();
                    break;
                case 'd':
                    printf("Debug Mode Engaged!\n");
                    break;
                default:
                    break;
                }
            }
        }
        exit(1);
    }


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
