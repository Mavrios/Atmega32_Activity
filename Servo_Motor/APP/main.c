/*
 * main.c
 *
 *  Created on: Apr 16, 2022
 *      Author: Kishk
 */


#include "../SERVICES/Std_types.h"
#include "../SERVICES/Bit_utils.h"
#include "../SERVICES/Utility/Map/Map.h"
#include "../MCAL/Port/Port.h"
#include "../MCAL/Dio/Dio.h"
#include "../MCAL/Adc/Adc.h"
#include "../HAL/Servo/Servo.h"

#include <util/delay.h>
#include <avr/io.h>

#define ADC_u16MIN			0
#define ADC_u16MAX			1023

#define SERVO_s8MIN_ANGLE	-90
#define SERVO_s8MAX_ANGLE	90
int main(void)
{
	u16 Loc_u16AnalogResult;
	s8	Loc_s8ServoAngle;
	/*INIT SYSTEM*/
	Port_vidInit();
	Adc_vidInit();
	Servo_vidInit();

	while(1)
	{

		Adc_enuAnalogRead(ADC_AnalogChannelAdc0 , &Loc_u16AnalogResult);
		Loc_s8ServoAngle = Map(Loc_u16AnalogResult , ADC_u16MIN , ADC_u16MAX , SERVO_s8MIN_ANGLE , SERVO_s8MAX_ANGLE);
		Servo_vidSetAngle(Servo_ChA , Loc_s8ServoAngle);
	}
	return 0;
}
