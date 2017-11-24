//orientation.cpp - Contains all the needed parts to setup and detect orientation 

#include "I2CDevice.h"
#include "main.h"
#include "MPU9250.h"
#include "orientation.h"
#include <chrono>
#include <thread>

//Set up the accelerometer for direction detection
Orientation::Orientation(void){
    mpu9250 = new I2CDevice(2,0x68);
    
    if(mpu9250->readRegister(WHO_AM_I_MPU9250) != 0x71)
    {
        cout << "Error connecting to accel/gyro, exiting" << endl;
        exit (2);
    }    

    mpu9250->writeRegister(PWR_MGMT_1,0x00);  //Turn on the sensors
    this_thread::sleep_for(chrono::milliseconds(100));    

    mpu9250->writeRegister(PWR_MGMT_1, 0x01);  //Set clock source to be PLL
    this_thread::sleep_for(chrono::milliseconds(200));    

    uint8_t c = mpu9250->readRegister(ACCEL_CONFIG);  //Get the current Accel settings
    c = c & ~0x18;  // Clear AFS bits [4:3]
    c = c | ASCALE << 3;  // Set the scale to 2g 
    mpu9250->writeRegister(ACCEL_CONFIG, c);

    c = mpu9250->readRegister(ACCEL_CONFIG2);
    c = c & ~0x0F;  // Clear the sample rate settings
    c = c | 0x03;  // Set the accelerometer rate to 1 kHz and bandwidth to 41 Hz
    mpu9250->writeRegister(ACCEL_CONFIG2, c);
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Accel initialized" << endl;
}

//Writes the raw accel data to passed struct
//To convert to Gs multiply by 2000 the divide by 32768
void Orientation::getAccelData(accel_t* dataOut){
    unsigned char *rawData = mpu9250->readRegisters(6,ACCEL_XOUT_H);  //Get the raw ECG data
    //Shift up and OR to full 16 bit value
    dataOut->X = (((int32_t)rawData[0] << 8) | rawData[1]);  
    dataOut->Y = (((int32_t)rawData[2] << 8) | rawData[3]);
    dataOut->Z = (((int32_t)rawData[4] << 8) | rawData[5]);
}
