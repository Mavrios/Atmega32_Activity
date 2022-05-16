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
#define ONE				1
#define DELAY_HALF_SECONDS	_delay_ms(500)

int main(void) {
	/*DEFINE VARIABLES*/
	u8 LOC_u8ButtonStatus;
	u8 LOC_u8LedPresentation = u8_LSB;
	Dio_tenuErrorStatus LOC_enuErrorCheck;
	/*CALL PORT INIT FUNCTION*/
	Port_vidInit();
	/*SUPER LOOP*/
	for (;;) {
		LOC_enuErrorCheck = Dio_enuReadChannel(DIO_u8CHANNEL24 , &LOC_u8ButtonStatus);
		/*CHECK BUTTON IS PRESSED*/
		if (LOC_enuErrorCheck == Dio_enuOk && LOC_u8ButtonStatus == DIO_u8LOW) {
			/*LEFT CIRCULAR SHIFT THE PORTA BY 1 TO TURN ON THE NEXT LED*/
			CLSHFT_REG(LOC_u8LedPresentation, ONE);
			Dio_enuWritePort(DIO_u8PORTA , LOC_u8LedPresentation);
			/*DELAY FOR HALF SECONDS*/
			DELAY_HALF_SECONDS;
		}
		LOC_enuErrorCheck = Dio_enuReadChannel(DIO_u8CHANNEL24 , &LOC_u8ButtonStatus);
		/*CHECK IF THE BUTTON RELEASED*/
		if (LOC_enuErrorCheck == Dio_enuOk && LOC_u8ButtonStatus == DIO_u8HIGH) {
			/*RIGHT CIRCUILAR SHIFT BY 1 TO TURNN ON THE NEXT LED */
			CRSHFT_REG(LOC_u8LedPresentation, ONE);
			Dio_enuWritePort(DIO_u8PORTA , LOC_u8LedPresentation);
			/*DELAY FOR HALF SECONDS*/
			DELAY_HALF_SECONDS;
		}
	}
	return 0;
}
