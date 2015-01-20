#include "controller.h"
#include <signal.h>
#include <errno.h>


volatile sig_atomic_t stop;

void inthand(int signum){
    stop = 1;
}

Controller::Controller(QObject *parent) :
    QObject(parent)
{


}


void Controller::fans(){

    int cpu_temp;
    FILE *tempInput, *sysIn;
    FILE *log;
    log = fopen("log","a+");


    char message[80];
    char tempMessage[120];
    char tmpString[45];
    char speedString[15];

    char label[100];
    std::string label_ = label;


    if(safeTemp >= criticalTemp)
    {
        //Leave it for MainWindow
        sprintf(label,"CRITICAL TEMP MUST BE GREATER THAN SAFE TEMP!!\n");
        emit setText(label);
        return;
    }

    if(manual){
        change_speed(0);
        fansLevel = AUTO;
        manual = 0;
    }

    tempInput = fopen("/sys/class/thermal/thermal_zone1/temp","r");
    if(tempInput == NULL){
        printf("ERROR! Could not retreive temperature information.\n");

    }

    fscanf(tempInput,"%d",&cpu_temp);

    cpu_temp /= 1000;
    fclose(tempInput);

    sysIn = popen("date '+%H:%M:%S'","r");
    if(sysIn != NULL){
        fgets(tmpString,9,sysIn);
        pclose(sysIn);
    }
    else{
        //Print Error Code
        qDebug() << "Error: " + errno;
    }

    sprintf(message,"Temperature: %dC, Checked at %s",cpu_temp,tmpString);
    fprintf(log,"%s\n",message);
    printf("%s\n",message);


    if(cpu_temp >= criticalTemp /*&& fansLevel == AUTO*/){
        switch(autoSpeedValue){
        case 0: strcpy(speedString, "auto"); break;
        case 8: strcpy(speedString, "full-speed"); break;
        default: sprintf(speedString, "%d",autoSpeedValue);
        }
        change_speed(autoSpeedValue);
        fansLevel = FORCED;
        sprintf(tempMessage,"\n%s\nTemperature is %d, critical is %d\nTurning fans to %s!",tmpString,cpu_temp,criticalTemp,speedString);
        fprintf(log,"%s",tempMessage);
        emit setText(tempMessage);

    }

    else if(cpu_temp<=safeTemp || cpu_temp <= criticalTemp){
        // changing fans level to auto
        change_speed(0);
        fansLevel = AUTO;
        // putting log message
        sprintf(tempMessage,"\n%s\nTemperature is %d, safe is %d\nTurning fans to auto!",tmpString,cpu_temp,safeTemp);
        fprintf(log,"%s",tempMessage);
        emit setText(tempMessage);
    }
    else if(errorTemp){
        errorTemp=0;
    }


    fclose(log);

}

void Controller::getTime(char* time){

    FILE *sysIn;
    sysIn = popen("date '+%H:%M:%S'","r");
    if(sysIn != NULL)
    {fgets(time,20,sysIn);
        pclose(sysIn);
    }
    else{
        //Print Error Code
        qDebug() << "Error: " + errno;
    }

}

int Controller::getTemperature()
{
    FILE *tempInput;
    int cpu_temp;
    tempInput = fopen("/sys/class/thermal/thermal_zone1/temp","r");
    if(tempInput != NULL){
        fscanf(tempInput,"%d",&cpu_temp);
        fclose(tempInput);
        return cpu_temp;
    }
    else{
        //Print Error Code
        qDebug() << "Error: " + errno;
        return 1;
    }
}

int Controller::getRPM()
{
    FILE *fp;
    char RPM[20];
    fp = popen("sensors | grep 'RPM' | awk '{print $2}'","r");
    if(fp != NULL)
    fgets(RPM,sizeof(RPM),fp);
    return atoi(RPM);
}


void Controller::change_speed(int speed){
    char tmpString[60];
    char speedString[15];
    FILE *log;
    log = fopen("log","a+");


    switch(speed){
    case 0: strcpy(speedString,"auto"); break;
    case 8: strcpy(speedString,"full-speed"); break;
    case 9: speed = 0;
    default: sprintf(speedString,"%d",speed);
    }
    sprintf(tmpString,"echo level %s > /proc/acpi/ibm/fan",speedString);
    system(tmpString);
    sprintf(tmpString,"Fans level - %s",speedString);
    fprintf(log,"%s\n",tmpString);
    emit setText(tmpString);

    sprintf(tmpString,"ThinkPad Fan Control .:: level - %s ::.",speedString);
    fprintf(log,"%s\n",tmpString);
    emit setText(tmpString);

    printf("** Speed level changed to %s **\n",speedString);
    fclose(log);
}

void Controller::consoleMode(){
    int choice;
    int level;
    int AUTO = 7;
    int FULL = 8;
    int fansLevel = AUTO;
    int temp, safeTemp=57, criticalTemp=60,sleepTime=120;
    FILE* tempInput;

    while(1){
        printf("\n[1] Monitor Mode\n");
        printf("[2] Manual Mode\n");
        printf("[3] Exit\n");
        scanf("%d",&choice);

        switch(choice){
        case 1:

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
                if(stop){
                    stop = 0;
                    break;
                }
                tempInput = fopen("/sys/class/thermal/thermal_zone1/temp","r");
                fscanf(tempInput,"%d",&temp);
                temp /= 1000;
                fclose(tempInput);
                printf("Temperature: %d Fan: %d\n",temp,getRPM());
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
                sleep(sleepTime);
            }

            break;
        case 2:
            printf("MANUAL MODE!\n");
            printf("Set Level <0-8> (z=auto,8=full): ");
            scanf("%d",&level);
            change_speed(level);
            while(1){
                signal(SIGINT,inthand);
                if(stop){
                    printf("Resetting to auto!\n");
                    change_speed(0);
                    stop = 0;
                    break;
                }
                printf("Temperature: %d Fan: %d\n",temp,getRPM());
                sleep(1);
            }
            break;
        case 3:
            exit(1);
            break;
        default:
            break;
        }

    }

}


