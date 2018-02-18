//This is a super basic example.
#include <iostream>
#include "main.h"
#include "orientation.h"
#include <unistd.h>
#include <iomanip>
#include "distance.h"
#include "drive.h"
#include "pid.h"
#include "test.h"
#include "input_thread.h"
#include <chrono>
#include <thread>
#include <cmath>
#include <signal.h>
#include <cstring>

double Kp;
double Kd;
double Ki;
bool exitRobot = false;
bool dataReady = false;

bool quitClean = false; //Was that the intent of exitRobot bool?

void sigHandler(int)
{
    cout << "CTRL+C triggered and caught." << endl;
    quitClean = true;
}

int main()
{
    /* CTRL+C exit handling setup. */
    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = sigHandler;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT,&sa,NULL);


    /* Begin program initialization. */
    Orientation orientation;  //TODO: Show have these throwing errors and catching them here
    Distance distance;
    Drive drive;
    PID pid(0.5, 30, -30, 0, 0, 0);

    TestOutput debug;

    drive.set_speed_left(DRIVE_SPEED_PERCENT(100));
    drive.set_speed_right(DRIVE_SPEED_PERCENT(100));
    drive.forward_left();
    drive.forward_right();

    cout << "Device initialized, entering run mode" << endl;
    // thread input (inputMain);

    float pitch = 0;
    float pitch_adj=0;

    // drive.set_speed_left(100);
    // drive.set_speed_right(100);
    while(1)
    {
        this_thread::sleep_for(chrono::milliseconds(5));
        if(dataReady){
            pid.update_values(Kp, Kd, Ki);
            dataReady = false;
        }

        pitch = orientation.getPitch();
        //pitch_adj = pid.calculate(0, pitch);
        cout << "Robot angle: " << pitch << endl; 
        if(pitch < 0.0){
            drive.forward_left();
            drive.forward_right();
        }
        else{
            drive.reverse_left();
            drive.reverse_right();
        }
        //pitch = abs(pitch_adj)*33333;
        // pitch = (pitch*pitch)*6000;
        // drive.set_speed_left(pitch);
        // drive.set_speed_right(pitch);

        cout << "Adjusted angle: " << pitch << endl;

        if (quitClean) break;
    }
    // input.join();
    return 0;
}

