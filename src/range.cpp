//range.cpp - Contains all the needed parts to setup and use range detection
#include "I2CDevice.h"
#include "main.h"

class Range {
    public:
    Range(void);
};

Range::Range(void){
    I2CDevice *temp_humidity = new I2CDevice(1,0);
}
