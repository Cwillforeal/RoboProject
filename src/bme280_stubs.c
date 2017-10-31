/*
 * bme280_stubs.c:  This file holds all the bme280 stubs for the driver
 *
 */
#include "stdint.h"
#include "bme280_stubs.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include "bme280_defs.h"

#define BB_I2C_0 "/dev/i2c-0"
#define BB_I2C_1 "/dev/i2c-2"

int file;  //This needs to be global for on and off access

static int8_t setup_read(uint8_t address){
    int8_t rslt = 0;

    if(write(file,&address,1)!=1){
        perror("Failed to set up read");
        return -1;
    }
    return rslt;
}

int8_t user_init_bme280_i2c(uint8_t bus, uint8_t addr)
{
    int8_t rslt = 0;
    //Connect to the I2C bus
    if(bus == 0){
        if((file=open(BB_I2C_0, O_RDWR)) < 0){
            perror("Failed to open bus");
            return -1;
        }
    } else {
        if((file=open(BB_I2C_1, O_RDWR)) < 0){
            perror("Failed to open bus");
            return -1;
        }
    }
    //Connect to the sensor
    if(ioctl(file, I2C_SLAVE, BME280_I2C_ADDR_PRIM) < 0){
        perror("Failed to connect to sensor");
        return -1;
    } 
    return rslt;
}

void user_delay_ms(uint32_t period)
{

}

int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    uint8_t bme280_regs[100];
    if(setup_read(reg_addr) < 0){
        return -1;
    }
    if(read(file,bme280_regs,len)!=len){
        perror("Failed to read registers");
        return -1;
    } 
    return rslt;
}

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    return rslt;
}
