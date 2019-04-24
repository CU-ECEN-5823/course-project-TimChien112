/*
 * ambient_light.h
 *
 *  Created on: Apr 20, 2019
 *      Author: santhosh
 */
#include <stdbool.h>
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "i2cspm.h"



#ifndef SRC_AMBIENT_LIGHT_H_
#define SRC_AMBIENT_LIGHT_H_

#define AMBIENT_LIGHT_ENABLE_PORT gpioPortF
#define AMBIENT_LIGHT_ENABLE_PIN  3
#define AMBIENT_LIGHT_ADDRESS 0x39
#define DEVICE_ID_REGISTER    0x0A
#define MANUFACTURER_ID_REGISTER 0x7E


void ambient_light_init();
void ambient_light_enable();
void Ambient_Light_I2C_Init();
void i2c_read_ambient_light_reg(I2C_TypeDef *i2c, uint8_t slaveAddr, uint8_t reg_addr);
void i2c_write_ambient_light_reg(I2C_TypeDef *i2c, uint8_t slaveAddr, uint8_t reg_addr);



#endif /* SRC_AMBIENT_LIGHT_H_ */
