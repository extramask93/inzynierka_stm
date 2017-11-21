/*
 * am2302.h
 *
 *  Created on: 18.11.2017
 *      Author: LENOVO
 */

#ifndef AM2302_H_
#define AM2302_H_

void am2302_Init();
int am2302_ReadData();
float am2302_getTemperature();
float am2302_getHumidity();
void am2302_pinOut();
void am2302_inInput();

#endif /* AM2302_H_ */
