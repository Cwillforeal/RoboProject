//drive.cpp:  This file handles driving the robot motors
#include <fstream>
#include "drive.h"
#include <string>
#include <dirent.h>

Drive::Drive(void){
    //Turn on the PWM0
    left_wheel.open("/sys/class/pwm/pwmchip0/export");
    left_wheel << "1";
    left_wheel.close();
    right_wheel.open("/sys/class/pwm/pwmchip0/export");
    right_wheel << "0";
    right_wheel.close();

    gpio_left.open("/sys/class/gpio/export");
    gpio_left << "30";
    gpio_left.close();
    gpio_right.open("/sys/class/gpio/export");
    gpio_right << "31";
    gpio_right.close();

    if(!opendir("/sys/class/gpio/gpio30"));{
        cout << "Failed to open gpio for direct" << endl;}
    if(!opendir("/sys/class/gpio/gpio31"));{
        cout << "Failed to open gpio for direct" << endl;}
    
    if(!opendir("/sys/class/pwm/pwmchip0/pwm0")){
        cout << "Failed open pwm0 chip files" << endl;
        exit(-1);}
   
    //Setup pwm base settings 
    left_wheel.open("/sys/class/pwm/pwmchip0/pwm1/period");
    left_wheel << "1000000000";
    left_wheel.close();
    left_wheel.open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle");
    left_wheel << "0";
    left_wheel.close();
    right_wheel.open("/sys/class/pwm/pwmchip0/pwm0/period");
    right_wheel << "1000000000";
    right_wheel.close();
    right_wheel.open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle");
    right_wheel << "0";
    right_wheel.close();
    left_wheel.open("/sys/class/pwm/pwmchip0/pwm1/enable");
    left_wheel << "1";
    left_wheel.close();

    //Setup gpio base settings
    gpio_left.open("/sys/class/gpio/gpio30/direction");
    gpio_left << "out";
    gpio_left.close();
    gpio_left.open("/sys/class/gpio/gpio30/value");
    gpio_left << "1";
    gpio_right.open("/sys/class/gpio/gpio31/direction");
    gpio_right << "out";
    gpio_right.close();
    gpio_right.open("/sys/class/gpio/gpio31/value");
    gpio_right << "1";

    cout << "PWM and motors initialized" <<endl;}

void Drive::reverse_left(){
    gpio_left.open("/sys/class/gpio/gpio30/value");
    gpio_left << "0";
    gpio_left.close();}

void Drive::reverse_right(){
    gpio_right.open("/sys/class/gpio/gpio31/value");
    gpio_right << "0";
    gpio_right.close();}

void Drive::forward_left(){
    gpio_left.open("/sys/class/gpio/gpio30/value");
    gpio_left << "1";
    gpio_left.close();}

void Drive::forward_right(){
    gpio_right.open("/sys/class/gpio/gpio31/value");
    gpio_right << "1";
    gpio_right.close();}

void Drive::set_speed_left(int speed){
    left_wheel.open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle");
    left_wheel << to_string(speed);
    left_wheel.close();}
    
void Drive::set_speed_right(int speed){
    right_wheel.open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle");
    right_wheel << to_string(speed);
    right_wheel.close();}

