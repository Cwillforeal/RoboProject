//This is a super basic example.
#include <iostream>
#include "main.h"
#include "orientation.h"
#include <unistd.h>

int main()
{
    Orientation orientation;
    accel_t accelData;

    while(1){
        orientation.getAccelData(&accelData);
        cout << "X scale data: " << accelData.X << endl;
        cout << "Y scale data: " << accelData.Y << endl;
        cout << "Z scale data: " << accelData.Z << endl;
        usleep(50000);
    }
    return 0;
}
