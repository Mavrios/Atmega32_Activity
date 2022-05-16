/*
 * main.c
 *
 *  Created on: Mar 1, 2022
 *      Author: Kishk
 */

#include <avr/io.h>
#include <util/delay.h>
#include "Bit_utils.h"
#include "Std_types.h"

#define BUTTON_u8_PIN	0
#define u8_LSB			0x01
#define ONE				1
#define DELAY_HALF_SECONDS	_delay_ms(500)

int main(void) {
	/*INIT LEDS AS OUTPUT*/
	SET_REG(DDRA);
	/*INIT BUTTON AS INPUT & ACTIVE PULLUP*/
	CLR_BIT(DDRD, BUTTON_u8_PIN);
	SET_BIT(PORTD, BUTTON_u8_PIN);
	/*INIT PORTA*/
	ASSIGN_REG(PORTA, u8_LSB);
	/*SUPER LOOP*/
	for (;;) {
		/*CHECK BUTTON IS PRESSED*/
		if (!GET_BIT(PIND, BUTTON_u8_PIN)) {
			/*LEFT CIRCULAR SHIFT THE PORTA BY 1 TO TURN ON THE NEXT LED*/
			CLSHFT_REG(PORTA, ONE);
			/*DELAY FOR HALF SECONDS*/
			DELAY_HALF_SECONDS;
		}
		/*CHECK IF THE BUTTON RELEASED*/
		if (GET_BIT(PIND, BUTTON_u8_PIN)) {
			/*RIGHT CIRCUILAR SHIFT BY 1 TO TURNN ON THE NEXT LED */
			CRSHFT_REG(PORTA, ONE);
			/*DELAY FOR HALF SECONDS*/
			DELAY_HALF_SECONDS;
		}
	}
	return 0;
}
