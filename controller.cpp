#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{

}


void Controller::fans(){

    int cpu_temp;
    FILE *tempInput, *sysIn;

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
    fgets(tmpString,9,sysIn);
    pclose(sysIn);

    sprintf(message,"Temperature: %dC, Checked at %s",cpu_temp,tmpString);
    printf("%s\n",message);
    emit setText(message);


    if(cpu_temp >= criticalTemp && fansLevel == AUTO){
        switch(autoSpeedValue){
        case 0: strcpy(speedString, "auto"); break;
        case 8: strcpy(speedString, "full-speed"); break;
        default: sprintf(speedString, "%d",autoSpeedValue);
        }
        change_speed(autoSpeedValue);
        fansLevel = FORCED;
        sprintf(tempMessage,"\n%s\nTemperature is %d, critical is %d\nTurning fans to %s!",tmpString,cpu_temp,criticalTemp,speedString);
        emit setText(tempMessage);

    }

    else if(cpu_temp<=safeTemp){
        // changing fans level to auto
        change_speed(0);
        fansLevel = AUTO;
        // putting log message
        sprintf(tempMessage,"\n%s\nTemperature is %d, safe is %d\nTurning fans to auto!",tmpString,cpu_temp,safeTemp);
        emit setText(tempMessage);
    }
    else if(errorTemp){
        errorTemp=0;
    }

}

void getTime(char* time){

    FILE *sysIn;
    sysIn = popen("date '+%H:%M:%S'","r");
    fgets(time,9,sysIn);
    pclose(sysIn);

}

int Controller::getTemperature()
{
    FILE *tempInput;
    int cpu_temp;
    tempInput = fopen("/sys/class/thermal/thermal_zone1/temp","r");
    fscanf(tempInput,"%d",&cpu_temp);
    return cpu_temp;
}


void Controller::change_speed(int speed){
    char tmpString[60];
    char speedString[15];

    switch(speed){
        case 0: strcpy(speedString,"auto"); break;
        case 8: strcpy(speedString,"full-speed"); break;
        default: sprintf(speedString,"%d",speed);
    }
    sprintf(tmpString,"echo level %s > /proc/acpi/ibm/fan",speedString);
    system(tmpString);
    sprintf(tmpString,"Fans level - %s",speedString);
    emit setText(tmpString);

    sprintf(tmpString,"ThinkPad Fan Control .:: level - %s ::.",speedString);
    emit setText(tmpString);

    printf("** Speed level changed to %s **\n",speedString);
}

