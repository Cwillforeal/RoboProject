//distance.cpp:  This file handles all distance related communication.

#include <iostream>
#include "distance.h"
#include "main.h"
#include "I2CDevice.h"
extern "C" {
#include "bme280.h"
#include "bme280_stubs.h"
}

//Set up the temp and humidity sensor
//Check to make sure the distance sensor is working
Distance::Distance(void){
    struct bme280_dev dev;
    struct bme280_data comp_data;
    int8_t rslt = BME280_OK;
    uint8_t settings_sel;

    //Set up the user stub functions
    if(user_init_bme280_i2c(1,BME280_I2C_ADDR_PRIM)<0){
        cout << "FAILED to setup BME280" << endl;
        exit(-1);
    }
    
    dev.dev_id = BME280_I2C_ADDR_PRIM;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_ms = user_delay_ms;

    if(bme280_init(&dev) != BME280_OK){
        cout << "FAILED to setup BME280" << endl;
        exit(-1);
    }

	/* Recommended mode of operation: Indoor navigation */
	dev.settings.osr_h = BME280_OVERSAMPLING_1X;
	dev.settings.osr_p = BME280_OVERSAMPLING_16X;
	dev.settings.osr_t = BME280_OVERSAMPLING_2X;
	dev.settings.filter = BME280_FILTER_COEFF_16;
	dev.settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	if(bme280_set_sensor_settings(settings_sel, &dev) != BME280_OK){
        cout << "FAILED to initialize BME280" <<endl;
        exit(-1);
    }
	if(bme280_set_sensor_mode(BME280_NORMAL_MODE, &dev) != BME280_OK){
        cout << "FAILED to initialize BME280" <<endl;
        exit(-1);
    }

    cout << "BME280 Initialized" <<endl;
}
