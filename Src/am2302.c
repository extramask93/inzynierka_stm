/*
 * am2302.c
 *
 *  Created on: 18.11.2017
 *      Author: LENOVO
 */

#include "am2302.h"
#include "stm32f1xx_hal.h"
#include <string.h>
#include "i2c.h"
#include "tim.h"

int8_t am2302Data[4];
volatile int timeOutFlag;
extern TIM_HandleTypeDef htim3;
static void am2302_pinOut() {
	  GPIO_InitTypeDef GPIO_InitStruct;
	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	  /*Configure GPIO pin : PB3 */
	  GPIO_InitStruct.Pin = GPIO_PIN_3;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
static void am2302_pinInput() {

	  GPIO_InitTypeDef GPIO_InitStruct;
	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	  /*Configure GPIO pin : PB3 */
	  GPIO_InitStruct.Pin = GPIO_PIN_3;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}
static void am2302_getTemperature(TH_Data *data) {
	  uint16_t retVal=0;
	  float temperature=0;
	  retVal = am2302Data[2];
	  retVal <<= 8;
	  retVal |= (am2302Data[3]) & 0xFF;
	  temperature = retVal;
	  temperature /= 10;
	  data->itemperature=retVal;
	  data->temperature = temperature;
}
static void am2302_getHumidity(TH_Data *data) {
	  uint16_t retVal=0;
	  float humidity=0;
	  retVal = am2302Data[0] & 0xFF;
	  retVal <<= 8;
	  retVal |= (am2302Data[1]) & 0xFF;
	  humidity = retVal;
	  humidity /= 10;
	  data->ihumidity=retVal;
	  data->humidity = humidity;
}
void am2302_Init() {
	MX_TIM3_Init();
	am2302_pinOut();
}
void am2302_DeIninit() {
	MX_TIM3_DeInit();
}
int am2302_ReadData(TH_Data *result) {
	memset(am2302Data,0x0,4); //reset
	timeOutFlag=0;
	int currentByte=0;
	int counter = 7;
	am2302_pinOut();
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
	HAL_Delay(1);//start -> data line for 1ms down
	am2302_pinInput();
	HAL_TIM_Base_Start(&htim3);
	TIM3->CNT = 0;
	while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)){ if(TIM3->CNT>500) return 1;}
	TIM3->CNT = 0;
	while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)){ if(TIM3->CNT>500) return 1;}
	TIM3->CNT = 0;
	while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)){ if(TIM3->CNT>500) return 1;}
	for(int i=0;i<40;i++) { //receieve 40 bits
		TIM3->CNT = 0;
		while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)){ if(TIM3->CNT>500) return 1;}
		uint32_t time = TIM3->CNT;
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)){ if(TIM3->CNT>500) return 1;}
		if((TIM3->CNT - time) >30) {
			am2302Data[currentByte] |= (1 << counter);
		}
		if(counter == 0) {
			counter=7;
			currentByte++;
		}
		else {
			counter--;
		}
	}
	HAL_TIM_Base_Stop(&htim3);
	am2302_getTemperature(result);
	am2302_getHumidity(result);
	return 0;
}
