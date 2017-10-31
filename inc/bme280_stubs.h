/*
 * bme280_stubs.h:  This file holds all the stubs for the bme280 driver
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

void user_delay_ms(uint32_t period);

int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

int8_t user_init_bme280_i2c(uint8_t bus, uint8_t addr);

#ifdef __cplusplus
}
#endif
