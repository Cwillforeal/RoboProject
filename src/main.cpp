//This is a super basic example.
#include <iostream>
#include "main.h"
#include "orientation.h"
#include <unistd.h>
#include <iomanip>
#include "distance.h"


int main()
{
    Orientation orientation;
    Distance distance;
    accel_t accelData;
    char esc(27);

    while(1){
        orientation.getAccelData(&accelData);
        cout << "X scale data: " << accelData.X << endl;
        cout << "Y scale data: " << accelData.Y << endl;
        cout << "Z scale data: " << accelData.Z << endl;
        usleep(50000);
        cout << esc << "[3A\r";
    }
    return 0;
}
