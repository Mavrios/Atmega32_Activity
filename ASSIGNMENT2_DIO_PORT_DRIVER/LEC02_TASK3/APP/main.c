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

		/* MACROS */
#define INCREMENT_u8_PIN		0
#define DECREMENT_u8_PIN		1
#define START_STOP_u8_PIN		2
#define u8_LSB					0x01
#define ONE						1
#define ZERO					0
#define DELAY_HALF_SECONDS		_delay_ms(500)
#define DELAY_FOR_DEBOUNCING	_delay_ms(400)
#define INCREMENT_PRESSED		0
#define DECREMENT_PRESSED		1
#define START_STOP_PRESSED		2
#define START_FLAG				3
#define MAX_LEDS				8

		/* START POINT */
int main(void) {
	/*DECLARE VARIABLE*/
	u8 LOC_u8Counter = ZERO, LOC_u8Flags = ZERO, LOC_u8TempReg = ZERO;
	u8 LOC_u8IncrementBtn = ZERO , LOC_u8DecrementBtn = ZERO , LOC_u8StartStopBtn = ZERO;
	Dio_tenuErrorStatus LOC_enuErrorChecker;
	/**
	 * LOC_u8Flags
	 * BIT(0): (0) IF THE INCREMENTS RELEASED, (1) IF THE INCREMENTS PRESSED
	 * BIT(1): (0) IF THE DECREMENTS RELEASED, (1) IF THE DECREMENTS PRESSED
	 * BIT(2): (0) IF THE START/STOP RELEASED, (1) IF THE START/STOP PRESSED
	 * BIT(3): (0) STOP STATE                , (1) START STATE
	 */

	/*INIT LEDS AS OUTPUT*/
	Port_vidInit();
	/*	SUPER LOOP	*/
	for (;;) {
		LOC_enuErrorChecker = Dio_enuReadChannel(DIO_u8CHANNEL24 , &LOC_u8IncrementBtn);
		/*CHECK IF INCREMENT BUTTON PRESSED & CHECK IF THE PREVIOUS STATE WAS RELEASED & CHECK IF THE SYSTEM WAS NOT STARTED*/
		if (LOC_u8IncrementBtn == DIO_u8LOW && !GET_BIT(LOC_u8Flags, INCREMENT_PRESSED) && !GET_BIT(LOC_u8Flags , START_FLAG)) {
			/*SET THE PRESSED INCREMENT FLAG */
			SET_BIT(LOC_u8Flags, INCREMENT_PRESSED);
			/*INCREMENT COUNTER FOR LED*/
			LOC_u8Counter++;
			/*LIMIT THE COUNTER TO THE MAXIMUM LED*/
			if (LOC_u8Counter >= MAX_LEDS) {
				LOC_u8Counter = MAX_LEDS;
			}
			/*TURN ON THE LED BASED ON COUNTER */
			Dio_enuWriteChannel(DIO_u8CHANNEL00 + LOC_u8Counter-ONE , DIO_u8HIGH);
			/*DELAY FOR DEBOUNCING*/
			DELAY_FOR_DEBOUNCING;
		}
		/*CHECK IF THE INCREMENT BUTTON RELEASED*/
		else if(LOC_u8IncrementBtn == DIO_u8HIGH)
		{
			/*CLEAR THE INCREMENT PRESSED FLAG */
			CLR_BIT(LOC_u8Flags, INCREMENT_PRESSED);
		}

		LOC_enuErrorChecker = Dio_enuReadChannel(DIO_u8CHANNEL25 , &LOC_u8DecrementBtn);
		/*CHECK IF DECREMENT BUTTON PRESSED & CHECK IF THE PREVIOUS STATE WAS RELEASED & CHECK IF THE SYSTEM WAS NOT STARTED*/
		if (LOC_u8DecrementBtn == DIO_u8LOW  && !GET_BIT(LOC_u8Flags, DECREMENT_PRESSED) && !GET_BIT(LOC_u8Flags , START_FLAG)) {
			/*SET THE PRESSED DECREMENT FLAG */
			SET_BIT(LOC_u8Flags, DECREMENT_PRESSED);
			/*LIMIT COUNTER LIMITATION TO ZERO*/
			if (LOC_u8Counter == ZERO) {
				LOC_u8Counter = ZERO;
			}
			else
			{
				/*DECREMENT COUNTER FOR LED*/
				LOC_u8Counter--;
			}
			/*TURN OFF THE LED BASED ON COUNTER */
			Dio_enuWriteChannel(DIO_u8CHANNEL00 + LOC_u8Counter , DIO_u8LOW);
			CLR_BIT(PORTA,LOC_u8Counter);
			/*DELAY FOR DEBOUNCING*/
			DELAY_FOR_DEBOUNCING;
		}
		/*CHECK IF THE DECREMENT BUTTON RELEASED*/
		else if(LOC_u8DecrementBtn == DIO_u8HIGH)
		{
			/*CLEAR THE DECREMENT PRESSED FLAG */
			CLR_BIT(LOC_u8Flags, DECREMENT_PRESSED);
		}

		LOC_enuErrorChecker = Dio_enuReadChannel(DIO_u8CHANNEL26 , &LOC_u8StartStopBtn);

		/*CHECK IF START/STOP BUTTON PRESSED & CHECK IF THE PREVIOUS STATE WAS RELEASED */
		if(LOC_u8StartStopBtn == DIO_u8LOW && !GET_BIT(LOC_u8Flags, START_STOP_PRESSED) )
		{
			/*SET THE PRESSED START/STOP FLAG */
			SET_BIT(LOC_u8Flags, START_STOP_PRESSED);
			/*TOGGLE THE START STATE FLAG*/
			TGL_BIT(LOC_u8Flags , START_FLAG);
			/*DELAY FOR DEBOUNCING*/
			DELAY_FOR_DEBOUNCING;
		}
		/*CHECK IF THE START/STOP BUTTON RELEASED*/
		else if(LOC_u8StartStopBtn == DIO_u8HIGH)
		{
			/*CLEAR THE START/STOP PRESSED FLAG */
			CLR_BIT(LOC_u8Flags, START_STOP_PRESSED);
		}

		/*CHECK IF THE START FLAG IS SET TO TOGGLE LED*/
		if(GET_BIT(LOC_u8Flags , START_FLAG))
		{
			/*SAVE CURRENT STATE OF PORTA*/
			Dio_enuReadPort(DIO_u8PORTA , &LOC_u8TempReg);
//			LOC_u8TempReg = PORTA;
			/*CLEAR PORTA TO TURN OFF ALL LEDS*/
			Dio_enuWritePort(DIO_u8PORTA , DIO_u8PORT_LOW);
			/*DELAY FOR HALF SECOND*/
			DELAY_HALF_SECONDS;
			/*ASSIGN THE SAVED VALUE OF PORTA A AGAIN TO TOGGLE LEDS*/
			Dio_enuWritePort(DIO_u8PORTA , LOC_u8TempReg);
			/*DELAY FOR HALF SECONDS*/
			DELAY_HALF_SECONDS;
		}
	}
	return 0;
}
