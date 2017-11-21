/*
 * SoilMoisture.c
 *
 *  Created on: 19.11.2017
 *      Author: LENOVO
 */

#include "SoilMoisture.h"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;
void SoilInit() {
	  ADC_ChannelConfTypeDef sConfig;
	  sConfig.Channel = ADC_CHANNEL_1;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
	  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}
int ReadValue() {
	int16_t result=0;
	HAL_ADC_Start(&hadc1);
	if(HAL_ADC_PollForConversion(&hadc1,100) == HAL_OK)
		result = HAL_ADC_GetValue(&hadc1);
		else {
			result= -1;
		}
	HAL_ADC_Stop(&hadc1);
	return result;
}
