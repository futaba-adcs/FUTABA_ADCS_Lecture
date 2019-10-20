/*
 * INA260.c
 *
 *  Created on: Oct 20, 2019
 *      Author: t.goto
 */

#include "pins.h"
#include "..\Inc\INA260.h"

extern I2C_HandleTypeDef INA260_PORT;

#define CONFIGURATION	0x00
#define CURRENT			0x01
#define BUS_VOLTAGE		0x02
#define POWER			0x03
#define MASK_ENABLE		0x06
#define ALERT_LIMIT		0x07
#define WHO_AM_I		0xFF //0x2270

uint16_t ina260_who_am_i(){
	uint8_t rx_buff[2];
	HAL_I2C_Mem_Read(&INA260_PORT, INA260_READ, WHO_AM_I, I2C_MEMADD_SIZE_8BIT, rx_buff, 2, 50);
	uint16_t res = (uint16_t)(rx_buff[0] << 8) | rx_buff[1];
	return res;
}

void set_torquer_OCP(float current){
	uint8_t tx_buff[2];
	tx_buff[0] = 0b01100101;
	tx_buff[1] = 0b10110111;

	HAL_I2C_Mem_Write(&INA260_PORT, INA260_WRITE, CONFIGURATION, I2C_MEMADD_SIZE_8BIT, tx_buff, 2, 50);

	tx_buff[0] = 0b10000000;
	          //   ||||||
	          //   ||||||
			  //   ||||||
			  //   ||||||
			  //   ||||||
			  //   |||||+CNRV
			  //   ||||+POL
			  //   |||+BUL
			  //   ||+BOL
			  //   |+UCL
			  //   +OCL(過電流保護)
	tx_buff[1] = 0b00000011;
			  //         |+LEN(1:Latch enabled )
			  //         +APOL Alert Pin mode 1:Inverted(active-high)

	HAL_I2C_Mem_Write(&INA260_PORT, INA260_WRITE, MASK_ENABLE, I2C_MEMADD_SIZE_8BIT, tx_buff, 2, 50);


	int16_t ocp = (int16_t) (current / 1.25);
	tx_buff[0] = (uint8_t)(ocp >> 8);
	tx_buff[1] = (uint8_t)ocp;

	HAL_I2C_Mem_Write(&INA260_PORT, INA260_WRITE, ALERT_LIMIT, I2C_MEMADD_SIZE_8BIT, tx_buff, 2, 50);

	return;
}

int16_t get_torquer_current(){
	uint8_t rx_buff[2];
	HAL_I2C_Mem_Read(&INA260_PORT, INA260_READ, CURRENT, I2C_MEMADD_SIZE_8BIT, rx_buff, 2, 50);
	int16_t res = (uint16_t)(rx_buff[0] << 8) | rx_buff[1];
	return res;
}

int16_t get_torquer_voltage(){
	uint8_t rx_buff[2];
	HAL_I2C_Mem_Read(&INA260_PORT, INA260_READ, BUS_VOLTAGE, I2C_MEMADD_SIZE_8BIT, rx_buff, 2, 50);
	int16_t res = (uint16_t)(rx_buff[0] << 8) | rx_buff[1];
	return res;
}

float get_torquer_current_f(){
	return (float)1.25 * get_torquer_current();
}

float get_torquer_voltage_f(){
	return (float)1.25 * get_torquer_voltage();
}

uint16_t reset_torquer_OCP(){
	uint8_t rx_buff[2];
	HAL_I2C_Mem_Read(&INA260_PORT, INA260_READ, MASK_ENABLE, I2C_MEMADD_SIZE_8BIT, rx_buff, 2, 50);
	uint16_t res = (rx_buff[0] << 8) + rx_buff[1];
	return res;
}
