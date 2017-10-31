//distance.cpp:  This file handles all distance related communication.
#include <iostream>
#include "distance.h"
#include "main.h"
#include "I2CDevice.h"
extern "C" {
#include "bme280.h"
#include "bme280_stubs.h"
}

Distance::Distance(void){
    uint8_t rslt = 0;

    cout << rslt << endl;
    if(user_init_bme280_i2c(1, 0x68) < 0){
        cout << "Error setting up i2c device" << endl;
        exit(-1);
    }
    if(user_i2c_read(0,BME280_CHIP_ID_ADDR,&rslt,1)){
        cout <<"Failed to read chip id" << endl;
        exit(-1);
    } 
    if(rslt!=BME280_CHIP_ID){
        cout <<"Incorrect chip ID"<<endl;
        exit(-1);
    }        
/*    struct bme280_dev *dev;
    int8_t rslt = BME280_OK;
    uint8_t settings_sel;

    bme280 = new I2CDevice(2,BME280_I2C_ADDR_PRIM);
    
    dev->dev_id = BME280_I2C_ADDR_PRIM;
    dev->intf = BME280_I2C_INTF;
    dev->read = user_i2c_read;
    dev->write = user_i2c_write;
    dev->delay_ms = user_delay_ms;

    rslt = bme280_init(dev);
*/
	/* Recommended mode of operation: Indoor navigation */
/*	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);
*/
}
