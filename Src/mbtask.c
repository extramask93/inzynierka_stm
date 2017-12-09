/*
 * mbtask.c
 *
 *  Created on: 26.11.2017
 *      Author: LENOVO
 */
#include "mb.h"
#include "mbport.h"
#include "mbtask.h"
#include "am2302.h"
#include "BV1750FVI.h"
#include "stm32f1xx_hal_tim.h"
#include "stm32f1xx_hal_pwr.h"
#include "usart.h"
#include "tim.h"
#include "rtc.h"
#include "i2c.h"
#include "adc.h"

#define REG_INPUT_START 1001
#define REG_INPUT_NREGS 8
extern TIM_HandleTypeDef htim4;extern TIM_HandleTypeDef htim3;extern UART_HandleTypeDef huart1;
static USHORT usRegInputStart = REG_INPUT_START;
static USHORT usRegInputBuf[REG_INPUT_NREGS];
uint16_t timcnt = 0;
TH_Data data=(const TH_Data){ 0 };

void GoToStop() {

	__disable_irq();
	InitIterruptOnUSART();
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFE);
	__enable_irq();
	SystemClock_Config();
	MX_ADC1_Init();
	MX_RTC_Init();
	MX_TIM4_Init();
	am2302_Init();
	BV_Init();
	MX_USART1_UART_Init();
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_12);
	eMBInit( MB_RTU, 1, 3, 19200, MB_PAR_NONE);
	eMBEnable();
}

void ModbusRTUTask(void const * argument)
{
  GoToStop();
  while(1) {
    eMBPoll();
    usRegInputBuf[3] = timcnt;
    int res = BV_ReadData(&usRegInputBuf[2]);
    int result = am2302_ReadData(&data);
    usRegInputBuf[0] = data.itemperature;
    usRegInputBuf[1] = data.ihumidity;
    data=(const TH_Data){ 0 };
  }
}

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
    return MB_ENOREG;
}


eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}

