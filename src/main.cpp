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

int main()
{
    Orientation orientation;  //TODO: Show have these throwing errors and catching them here
    Distance distance;
    Drive drive;

    cout << "Device initialized, entering run mode" << endl;

    int count=0;
    bool positive=true;
    drive.set_speed_left(WHEEL_PERIOD);
    drive.set_speed_right(WHEEL_PERIOD);

    while(1)
    {
        
        this_thread::sleep_for(chrono::milliseconds(100));
        count++;
        if(count==10){
            count = 0;
            if(positive){
                positive = false;
                drive.reverse_left();
                drive.forward_right();}
            else{
                positive = true;
                drive.forward_left();
                drive.reverse_right();}}        
    }
    return 0;
}
