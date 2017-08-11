//orientation.cpp - Contains all the needed parts to setup and detect orientation 
#include "I2CDevice.h"
#include "main.h"
#include "MPU9250.h"
#include "orientation.h"
#include <chrono>
#include <thread>

//Inits the orientation class 
Orientation::Orientation(void){
    I2CDevice *mpu9250 = new I2CDevice(1,0x68);
    
    if(mpu9250->readRegister(WHO_AM_I_MPU9250) != 0x71)
    {
        cout << "Error connecting to accel/gyro, exiting" << endl;
        exit (2);
    }    

    mpu9250->writeRegister(PWR_MGMT_1,0x00);  //Turn on the sensors
    this_thread::sleep_for(chrono::milliseconds(100));    

    mpu9250->writeRegister(PWR_MGMT_1, 0x01);  //Set clock source to be PLL
    this_thread::sleep_for(chrono::milliseconds(200));    

    uint8_t c = mpu9250->readByte(ACCEL_CONFIG);  //Get the current Accel settings
    c = c & ~0x18;  // Clear AFS bits [4:3]
    c = c | ASCALE << 3;  // Set the scale to 2g 
    mpu9250->writeByte(ACCEL_CONFIG, c);

    c = mpu9250->readByte(ACCEL_CONFIG2);
    c = c & ~0x0F;  // Clear the sample rate settings
    c = c | 0x03;  // Set the accelerometer rate to 1 kHz and bandwidth to 41 Hz
    mpu9250->writeByte(ACCEL_CONFIG2, c);
    this_thread::sleep_for(chrono::milliseconds(100));

    //Calibrate the accelerometer
    mpu9250->writeRegister(PWR_MGMT_1,0x80);  // Reset the device
    this_thread::sleep_for(chrono::milliseconds(100));

    //Get stable time source
    mpu9250->writeRegister(PWR_MGMT_1,0x01);
    mpu9250->writeRegister(PWR_MGMT_2,0x00);
    this_thread::sleep_for(chrono::milliseconds(200));

    //Configure for self test mode
    mpu9250->writeRegister(INT_ENABLE,0x00);  // Disable all interrupts
    mpu9250->writeRegister(FIFO_EN,0x00);  //Disable FIFO
    mpu9250->writeRegister(PWR_MGMT_1, 0x00);  //Turn on internal clock source
    mpu9250->writeRegister(I2C_MST_CTRL, 0x00);  //Disable I2C master
    mpu9250->writeRegister(USER_CTRL, 0x00);  // Disable FIFO and I2C master modes
    mpu9250->writeRegister(USER_CTRL, 0x0C);  // Reset FIFO and DMP
    this_thread::sleep_for(chrono::milliseconds(15));

    //Configure accelerometer for bias calculation
    mpu9250->writeRegister(CONFIG, 0x01);  // Set low pass filter to 188Hz
    mpu9250->writeRegister(SMPLRT_DIV, 0x00);  // Set sample rate to 1kHz
    mpu9250->writeRegister(ACCEL_CONFIG, 0x00);  // Set accelerometer full-scale to 2 g, maximum sensitivity

    uint16_t accelsensitivity = 16384;  // = 16384 LSB/g

    //Configure FIFO for accelerometer
    mpu9250->writeRegister(USER_CTRL, 0x40);  // Enable FIFO
    mpu9250->writeRegister(FIFO_EN, 0x08);  // Enable accelerometer FIFO
    this_thread::sleep_for(chrono::milliseconds(40);

    uint8_t data[12];
    uint16_t packet_count, fifo_count;
    //After getting all the samples turn off FIFO sensor read
    mpu9250->writeRegster(FIFO_EN, 0x00);
    data = mpu9250->readRegisters(2, FIFO_COUNT);  // Read the sample count 
    fifo_count = ((uint16_t)data[0] << 8) | data[1];
    packet_count = fifo_count/12;  

    for(uint16_t ii = 0; ii < packet_count; ii++)
    {
        int16_t accel_temp[3] = {0,0,0};
        data = mpu9250->readRegistes(12, FIFO_R_W);

}
