/*
 * main.c
 *
 *  Created on: Mar 1, 2022
 *      Author: Kishk
 */

#include <avr/io.h>
#include <util/delay.h>
#include "../Services/Bit_utils.h"
#include "../Services/Std_types.h"
#include "../MCAL/Dio/Dio.h"
#include "../MCAL/Port/Port.h"

#define ZERO 	0
#define ONE		2
#define YELLOW		1
#define NUM_OF_YELLOW_BLINKING	5
#define NUM_TRAFFIC_LIGHT_LEDS		3
#define DELAY_SECONDS(SECONDS)		_delay_ms(SECONDS * 1000);
int main(void) {
	/*DECLARE VARIABLE*/
	u8 LOC_u8Iterator = ZERO;
	/*INIT LEDS AS OUTPUT*/
	Port_vidInit();
	for (;;) {
		Dio_enuWritePort(DIO_u8PORTA , DIO_u8PORT_LOW);
		Dio_enuWriteChannel(DIO_u8CHANNEL00 , DIO_u8HIGH);
		DELAY_SECONDS(ONE);
		/*LOOP INTO TO CHANGE STATE OF TRRAFIC LIGHT*/
		for(LOC_u8Iterator = ZERO ; LOC_u8Iterator < NUM_OF_YELLOW_BLINKING ; LOC_u8Iterator++)
		{
			/*DELAY FOR 100  MILLI-SECOND*/
			_delay_ms(100);
			Dio_enuWriteChannel(DIO_u8CHANNEL01 , DIO_u8HIGH);
			/*TURN ON LED DEPENDS ON THEIR ORDER*/
			_delay_ms(100);
			Dio_enuWritePort(DIO_u8PORTA , DIO_u8PORT_LOW);

		}
		Dio_enuWritePort(DIO_u8PORTA , DIO_u8PORT_LOW);
		Dio_enuWriteChannel(DIO_u8CHANNEL02 , DIO_u8HIGH);
		DELAY_SECONDS(ONE);
	}
	return 0;
}
