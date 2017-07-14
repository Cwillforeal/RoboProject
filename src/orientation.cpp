//orientation.cpp - Contains all the needed parts to setup and detect orientation 
#include "I2CDevice.h"
#include "main.h"
#include "MPU9520.h"

class Orientation {
    public:
    Orientation(void);
};

Orientation::Orientation(void){
    I2CDevice *mpu9250 = new I2CDevice(1,0);
    
    if(mpu9250->readRegister(WHO_AM_I_MPU9250) != 0x71)
    {
        cout << "Error connecting to accel/gyro, exiting" << endl;
        exit (2);
    }    
    cout << "We made it" << endl;   
}
