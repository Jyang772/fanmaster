#include "mainwindow.h"
#include <QApplication>

//C Level
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "controller.h"

//Catch signal
//http://stackoverflow.com/questions/13010531/leaving-an-infinite-while-loop-in-c

int main(int argc, char *argv[])
{

    Controller console;

    if(argc > 1){


        //Ghetto way of parsing
        for(int i=0; i<argc; i++){
            if(argv[i][0] == '-' && argv[i][1] != '-'){

                switch(argv[i][1]){
                case 'c':
                    printf("Console Mode Engaged!\n");
                    console.consoleMode();
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
