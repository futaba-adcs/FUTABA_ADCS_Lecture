/*
 * INA260.h
 *
 *  Created on: Oct 20, 2019
 *      Author: t.goto
 */

#ifndef INC_INA260_H_
#define INC_INA260_H_

#include "stm32f4xx_hal.h"
#include "main.h"

uint16_t ina260_who_am_i();
void set_torquer_OCP(float current); //磁気トルカの最大電流の設定[mA]
int16_t get_torquer_current(); //電流取得
int16_t get_torquer_voltage(); //電圧取得
float get_torquer_current_f(); //電流取得[mA]
float get_torquer_voltage_f(); //電圧取得[mV]

uint16_t reset_torquer_OCP(); //OCP復帰


#endif /* INC_INA260_H_ */
