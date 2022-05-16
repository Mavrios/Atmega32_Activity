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

#define BUTTON_u8_PIN	0
#define u8_LSB			0x01
#define ONE		1
#define DELAY_HALF_SECONDS	_delay_ms(500)

int main (void)
{
	/*DEFINE VARAIABLE*/
	u8 LOC_u8ButtonStatus ;
	u8 LOC_u8LedPresent   = u8_LSB ;
	Dio_tenuErrorStatus LOC_enuErrorChecker;
	/*CALL INIT PORT FUNCTIONS*/
	Port_vidInit();
	/*SUPER LOOP*/
	for(;;)
	{
		LOC_enuErrorChecker = Dio_enuReadChannel(DIO_u8CHANNEL24,&LOC_u8ButtonStatus);
		/*CHECK BUTTON IS PRESSED*/
		if(LOC_enuErrorChecker == Dio_enuOk && LOC_u8ButtonStatus == DIO_u8HIGH)
		{
			LOC_enuErrorChecker = Dio_enuReadChannel(DIO_u8CHANNEL24,&LOC_u8ButtonStatus);
			/*RIGHT CIRCUILAR SHIFT BY ONE TO TURN ON THE NEXT LED*/
			CRSHFT_REG(LOC_u8LedPresent,ONE);
			Dio_enuWritePort(DIO_u8PORTA,LOC_u8LedPresent);
			/*DELAY FOR HALF SECOND*/
			DELAY_HALF_SECONDS;
		}
	}
	return 0;
}
