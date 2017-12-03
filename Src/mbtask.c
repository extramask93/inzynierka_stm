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
#define REG_INPUT_START 1001
#define REG_INPUT_NREGS 8

static USHORT usRegInputStart = REG_INPUT_START;
static USHORT usRegInputBuf[REG_INPUT_NREGS];

void ModbusRTUTask(void const * argument)
{
  /* ABCDEF */

  volatile eMBErrorCode eStatus = eMBInit( MB_RTU, 1, 3, 19200, MB_PAR_NONE );
  eStatus = eMBEnable();
  GetCurrentReading(&usRegInputBuf[2]);
  am2302_ReadData();
  usRegInputBuf[0] = am2302_getTemperature();
  usRegInputBuf[1] = am2302_getHumidity();
  while(1) {
    eMBPoll();
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


