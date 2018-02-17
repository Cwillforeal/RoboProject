//This is the file that will run a thread for user input
#include "main.h"
#include <chrono>
#include <thread>
#include <mutex>

mutex mtx;

void inputMain(void){
    float lKp;
    float lKd;
    float lKi;

    while(1){
        while(dataReady);  //Wait for the data to be read
        cout <<"Input parameters below:"<<endl;
        cout <<"Kp: ";
        cin >> lKp;
        cout <<"Kd: ";
        cin >> lKd;
        cout <<"Ki: ";
        cin >> lKi;
        
        mtx.lock();
        if(lKp==-1 || lKd==-1 || lKi==-1){
            exitRobot = true;
            break;}
        Kp = lKp;
        Kd = lKd;
        Ki = lKi;
        dataReady = true;
        mtx.unlock();}
}
