/*
 * ambient_light.c
 *
 *  Created on: Apr 20, 2019
 *      Author: santhosh
 */
#include "ambient_light.h"
#include "src/log.h"
#include "src/wait_funct/wait_funct.h"

uint8_t read_buffer[3];
uint16_t value;
I2C_TransferSeq_TypeDef seq;
I2C_TransferReturn_TypeDef ret;
void ambient_light_init()
{
	ambient_light_enable();
	Ambient_Light_I2C_Init();
	i2c_write_ambient_light_reg(I2C0,AMBIENT_LIGHT_ADDRESS,DEVICE_ID_REGISTER);
	i2c_read_ambient_light_reg(I2C0,AMBIENT_LIGHT_ADDRESS,DEVICE_ID_REGISTER);

	value = read_buffer[1]<<8 | read_buffer[2];
	LOG_INFO("light value: %d", value);
}

void ambient_light_enable()
{
	GPIO_PinModeSet(AMBIENT_LIGHT_ENABLE_PORT, AMBIENT_LIGHT_ENABLE_PIN, gpioModePushPull, 1);
}

void Ambient_Light_I2C_Init()
{

		I2CSPM_Init_TypeDef init_ambient_light ={
				I2C0,                       /* Use I2C instance 0 */                       \
			    gpioPortC,                  /* SCL port */                                 \
			    10,                         /* SCL pin */                                  \
			    gpioPortC,                  /* SDA port */                                 \
			    11,                         /* SDA pin */                                  \
			    14,                         /* Location of SCL */                          \
			    16,                         /* Location of SDA */                          \
			    0,                          /* Use currently configured reference clock */ \
			    I2C_FREQ_STANDARD_MAX,      /* Set to standard rate  */                    \
			    i2cClockHLRStandard,        /* Set to use 4:4 low/high duty cycle */       \
			  };
		I2CSPM_Init(&init_ambient_light);

		LOG_INFO("temperature sensor is initialized");
}



void i2c_read_ambient_light_reg(I2C_TypeDef *i2c, uint8_t slaveAddr, uint8_t reg_addr)
{

	//since using 7 -bit address mode, we shift the address
	seq.addr = (uint16_t)((slaveAddr<<1));

	read_buffer[0] =  reg_addr;
	seq.buf[0].data = read_buffer;
	seq.buf[0].len = 1;
	read_buffer[0] = 0;
	read_buffer[1] = 0;
	read_buffer[2] = 0;
	seq.flags = I2C_FLAG_READ;
	read_buffer[1] = 0;
	seq.buf[1].data = read_buffer+1;
	seq.buf[1].len = 1;

	I2C_TransferReturn_TypeDef ret = I2CSPM_Transfer(i2c, &seq);
	LOG_INFO("I2C result: %d", ret);
	//I2C_TransferInit(i2c, &seq);
	//NVIC_EnableIRQ(I2C0_IRQn);



}

void i2c_write_ambient_light_reg(I2C_TypeDef *i2c, uint8_t slaveAddr, uint8_t reg_addr)
{

	//since using 7 -bit address mode, we shift the address
	seq.addr = (uint16_t)((slaveAddr<<1) & ((uint8_t)0xFE));

	read_buffer[0] =  reg_addr;
	seq.buf[0].data = read_buffer;
	seq.buf[0].len = 1;

	seq.flags = I2C_FLAG_WRITE;

//	read_buffer[1] = 0;
//	seq.buf[1].data = read_buffer+1;
//	seq.buf[1].len = 1;

	I2C_TransferReturn_TypeDef ret = I2CSPM_Transfer(i2c, &seq);
	LOG_INFO("I2C result: %d", ret);
	NVIC_EnableIRQ(I2C0_IRQn);


}



void I2C0_IRQHandler(void)
{
	I2C_TransferReturn_TypeDef ret = I2C_Transfer(I2C0);

	if(ret == i2cTransferDone)
		{
			value = read_buffer[1]<<8 | read_buffer[2];
			LOG_INFO("light value: %d", value);
		}
	else if(ret != i2cTransferInProgress)
		{
			LOG_ERROR("I2C Error %d",ret);
//			event |= I2C_TRANSFER_ERROR;
		}
}
