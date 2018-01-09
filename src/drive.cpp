//drive.cpp:  This file handles driving the robot motors
#include <fstream>
#include "drive.h"
#include <dirent.h>

Drive::Drive(void){
    //Turn on the PWM0
    pwmchip.open("/sys/class/pwm/pwmchip0/export");
    pwmchip << "0";
    pwmchip.close();

    if(opendir("sys/class/pwm/pwmchip0/pwm0")){
        cout << "Failed open pwm0 chip files" << endl;
        exit(-1);
    }
    
    pwmchip.open("/sys/class/pwm/pwmchip0/pwm0/period");
    pwmchip << "1000000000";
    pwmchip.close();
    pwmchip.open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle");
    pwmchip << "900000000";
    pwmchip.close();
    pwmchip.open("/sys/class/pwm/pwmchip0/pwm0/enable");
    pwmchip << "1";
    pwmchip.close();
    
    cout << "PWM and motors initialized" <<endl;
}
