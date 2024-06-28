/*
 * pH_value.h
 *
 *  Created on: May 23, 2024
 *      Author: makesh
 */

#include "main.h"

#ifndef INC_PH_VALUE_H_
#define INC_PH_VALUE_H_

float Get_pH_value(void);

void pH_Init(ADC_HandleTypeDef *hadc);

void pH_uart2(ADC_HandleTypeDef *huart2);

#endif /* INC_PH_VALUE_H_ */
