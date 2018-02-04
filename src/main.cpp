//This is a super basic example.
#include <iostream>
#include "main.h"
#include "orientation.h"
#include <unistd.h>
#include <iomanip>
#include "distance.h"
#include "drive.h"
#include <chrono>
#include <thread>
#include <cmath>

int main()
{
    Orientation orientation;  //TODO: Show have these throwing errors and catching them here
    Distance distance;
    Drive drive;
    accel_t raw_data;

    drive.set_speed_left(500000);
    drive.set_speed_right(500000);
    drive.forward_left();
    drive.forward_right();

    cout << "Device initialized, entering run mode" << endl;

    Data *accel_converted;
    Data *gyro_converted;
    float pitch = 0;
    float pitch_accel;
    while(1)
    {
        
        this_thread::sleep_for(chrono::milliseconds(5));
        orientation.readGyroData(raw_data);
        gyro_converted = orientation.convertGyroData(raw_data);
        orientation.readAccelData(raw_data);
        accel_converted = orientation.convertAccelData(raw_data);
        
        pitch += gyro_converted->y*0.005; 
        float accelMag = abs(accel_converted->x)+abs(accel_converted->y)+abs(accel_converted->z);
        if(accelMag > 0.5 && accelMag < 2){
            pitch_accel = atan2f(accel_converted->z,(-1*accel_converted->x))*180/(3.14159265);
            pitch = pitch*0.90 + pitch_accel*0.1;}

        cout << "Robot angle: " << pitch << endl; 
        if(pitch < 0){
            drive.forward_left();
            drive.forward_right();}
        else{
            drive.reverse_left();
            drive.reverse_right();}
    }
    return 0;
}

