//distance.h
#include "main.h"

class Distance
{
    private:
        I2CDevice * bme280;
    public:
        int8_t i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
        Distance(void);
};

