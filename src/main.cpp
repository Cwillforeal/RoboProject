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

    //drive.set_speed_left(500000);
    //drive.set_speed_right(500000);
    //drive.forward_left();
    //drive.forward_right();

    cout << "Device initialized, entering run mode" << endl;

    float pitch = 0;
    while(1)
    {
        
        this_thread::sleep_for(chrono::milliseconds(5));
        pitch = orientation.getPitch();
        cout << "Robot angle: " << pitch << endl; 
    }
    return 0;
}

