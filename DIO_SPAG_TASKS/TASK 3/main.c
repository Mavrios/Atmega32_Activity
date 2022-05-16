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

#define ZERO 	0
#define ONE		1
#define NUM_TRAFFIC_LIGHT_LEDS		3
#define DELAY_SECONDS(SECONDS)		_delay_ms(SECONDS * 1000);
int main(void) {
	/*DECLARE VARIABLE*/
	u8 LOC_u8Iterator = ZERO;
	/*INIT LEDS AS OUTPUT*/
	SET_REG(DDRA);
	/*INIT BUTTON AS INPUT & ACTIVE PULLUP*/
	CLR_BIT(DDRD, ZERO);
	SET_BIT(PORTD, ZERO);
	CLR_REG(PORTA);
	for (;;) {
		/*LOOP INTO TO CHANGE STATE OF TRRAFIC LIGHT*/
		for(LOC_u8Iterator = ZERO ; LOC_u8Iterator < NUM_TRAFFIC_LIGHT_LEDS ; LOC_u8Iterator++)
		{
			/*TURN OFF ALL PORTA LEDS*/
			CLR_REG(PORTA);
			/*TURN ON LED DEPENDS ON THEIR ORDER*/
			SET_BIT(PORTA,LOC_u8Iterator);
			/*DELAY FOR ONE SECOND*/
			DELAY_SECONDS(ONE);
		}
	}
	return 0;
}
