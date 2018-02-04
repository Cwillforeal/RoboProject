//orientation.cpp - Contains all the needed parts to setup and detect orientation 

#include "I2CDevice.h"
#include "main.h"
#include "MPU9250.h"
#include "orientation.h"
#include <chrono>
#include <thread>
#include <cmath>


Data::Data(void){
}

void Data::display(void){
    cout << "DATA::: X = " << this->x << ", Y = " << this->y << ", Z = " << this->z << "\r\n";
}

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

    mpu9250->writeRegister(CONFIG,0x03);

    mpu9250->writeRegister(SMPLRT_DIV,0x04);

    uint8_t c = mpu9250->readRegister(GYRO_CONFIG);
    c = c & ~0x02; // Clear Fchoice bits [1:0] 
    c = c & ~0x18; // Clear AFS bits [4:3]
    c = c | GSCALE << 3; // Set full scale range for the gyro
    mpu9250->writeRegister(GYRO_CONFIG, c);
    
    c = mpu9250->readRegister(ACCEL_CONFIG);  //Get the current Accel settings
    c = c & ~0x18;  // Clear AFS bits [4:3]
    c = c | ASCALE << 3;  // Set the scale to 2g 
    mpu9250->writeRegister(ACCEL_CONFIG, c);

    c = mpu9250->readRegister(ACCEL_CONFIG2);
    c = c & ~0x0F;  // Clear the sample rate settings
    c = c | 0x03;  // Set the accelerometer rate to 1 kHz and bandwidth to 41 Hz
    mpu9250->writeRegister(ACCEL_CONFIG2, c);
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Accel initialized" << endl;

    this->pitch = 0;
}

//Writes the raw accel data to passed struct
//To convert to Gs multiply by 2000 then divide by 32768
void Orientation::readAccelData(accel_t &dataOut){
    uint8_t *rawData = mpu9250->readRegisters(6,ACCEL_XOUT_H);  //Get the raw accel data
    //Shift up and OR to full 16 bit value
    dataOut.X = (((int16_t)rawData[0] << 8) | rawData[1]);  
    dataOut.Y = (((int16_t)rawData[2] << 8) | rawData[3]);
    dataOut.Z = (((int16_t)rawData[4] << 8) | rawData[5]);
}

void Orientation::readGyroData(accel_t &dataOut){
  uint8_t *rawData = mpu9250->readRegisters(6, GYRO_XOUT_H);  // x/y/z gyro register data stored here
  dataOut.X = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
  dataOut.Y = ((int16_t)rawData[2] << 8) | rawData[3] ;  
  dataOut.Z = ((int16_t)rawData[4] << 8) | rawData[5] ; 
}

Data *Orientation::convertAccelData(accel_t &data){
    Data *values = new Data();
    values->x = (float)(((int16_t)(data.X))*2)/G_CONVERT;
    values->y = (float)(((int16_t)(data.Y))*2)/G_CONVERT;
    values->z = (float)(((int16_t)(data.Z))*2)/G_CONVERT;
    return values;
}

Data *Orientation::convertGyroData(accel_t &data){
    Data *values = new Data();
    values->x = (float)(((int16_t)(data.X))*250)/G_CONVERT;
    values->y = (float)(((int16_t)(data.Y))*250)/G_CONVERT;
    values->z = (float)(((int16_t)(data.Z))*250)/G_CONVERT;
    return values;
}

void Orientation::printAccelData(accel_t data){
    cout << "DATA::: X = " << data.X << ", Y = " << data.Y << ", Z = " << data.Z << "\r\n";
}

float Orientation::getPitch(void){
    accel_t raw_data;
    Data *gyro_data;
    Data *accel_data;
    this->readGyroData(raw_data);
    gyro_data = this->convertGyroData(raw_data); 
    this->readAccelData(raw_data);
    accel_data = this->convertAccelData(raw_data);

    this->pitch += gyro_data->y*0.005;
    float accel_mag = abs(accel_data->x) + abs(accel_data->y) + abs(accel_data->z);
    if(accel_mag > 0.5 && accel_mag < 2.0){
        float pitch_accel = atan2f(accel_data->z, (-1*accel_data->x))*180/(3.14159265);
        this->pitch = this->pitch*0.90 + pitch_accel*0.1;}

   return this->pitch;} 

