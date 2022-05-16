/*
 * main.c
 *
 *  Created on: Mar 13, 2022
 *      Author: Kishk
 */

#include "../Services/Std_types.h"
#include "../Services/Bit_utils.h"
#include "../MCAL/Port/Port.h"
#include "../MCAL/Dio/Dio.h"
#include "../HAL/Ssd/Ssd.h"
#include <util/delay.h>
//#define DEBUG

#define u8START_STOP_BTN	DIO_u8CHANNEL28
#define u8SELECT_BTN		DIO_u8CHANNEL29
#define u8INCREMENT_BTN		DIO_u8CHANNEL30
#define u8DECREMENT_BTN		DIO_u8CHANNEL31

#define ZERO_INIT			0
#define ONE_INIT			1

#define START_STOP_FLAG		0
#define SELECT_FLAG			1

#define TRUE				1
#define FALSE				0

#define STOP				0

#define DELAY_BETWEEN_BLINK		150
#define DEBOUNCING_DELAY		500

#define TEN						10
#define HUNDRED					100
#define THOUSEND				1000
#define ZERO					0
#define NINE					9
#define NINTY					90
#define NHUNDRED				900
#define NTHOUSEND				9000

#define SECOND					50

#define MAX_COUNTER				9999

int main(void) {
	/*DELCARE VARIABLE*/
	/*COUNTER VARIABLE TO BE DISPLAYED IN SSD*/
	u16 Loc_u16Counter = ZERO_INIT;
	/*SELECTED LCD TO BE EDIT*/
	u8 Loc_u8SelectSsd = ZERO_INIT;
	/*FLAG VARIABLE
	 * BIT0 : START STOP FLAG
	 * BIT1 : SELECT FLAG*/
	u8 Loc_u8Flag = ZERO_INIT;
	/*VARIABLE TO STORE BTN STATUS*/
	u8 Loc_u8BtnStatus = ONE_INIT;
	/*INITIALIZE PORT PINS*/
	Port_vidInit();
	/*DISPLAY SSD NUMBER (ZERO)*/
	Ssd_enuDisplayNumber(Loc_u16Counter);

	/*SUPER LOOP*/
	while (1) {
		/*READ SELECT BTN STATUS AND CHECK IF STYSTEM IS IN STOP MODE*/
		Dio_enuReadChannel(u8SELECT_BTN, &Loc_u8BtnStatus);
		if (Loc_u8BtnStatus == DIO_u8LOW
				&& GET_BIT(Loc_u8Flag , START_STOP_FLAG) == STOP) {
			/*SET SELECT FLAG*/
			SET_BIT(Loc_u8Flag, SELECT_FLAG);
			/*INCREMENT SELECT SSD*/
			Loc_u8SelectSsd++;
			/*LIMIT SELECTED SSD TO FOUR SSD*/
			if(Loc_u8SelectSsd > SSD_u8FOUR)
			{
				Loc_u8SelectSsd = SSD_u8ONE;
			}
			/*DELAY FOR DEBOUNCING*/
			_delay_ms(200);
		}
		/*CHECK IF SELECT IS TRUE*/
		if (GET_BIT(Loc_u8Flag , SELECT_FLAG) == TRUE) {
			/*KEEP BLINKING THE CURRENT SSD*/
			Ssd_enuDisableSsd(Loc_u8SelectSsd);
			_delay_ms(DELAY_BETWEEN_BLINK);
			Ssd_enuDisplayNumber(Loc_u16Counter);
			_delay_ms(DELAY_BETWEEN_BLINK);

		}
		/*READ INCREMENT BTN STATUS AND MAKE SURE THAT IT'S NOT IN START MODE AND IT'S IN SELECT MODE*/
		Dio_enuReadChannel(u8INCREMENT_BTN, &Loc_u8BtnStatus);
		if (Loc_u8BtnStatus == DIO_u8LOW
				&& GET_BIT(Loc_u8Flag , START_STOP_FLAG) == STOP) {
			if(GET_BIT(Loc_u8Flag , SELECT_FLAG) == TRUE)
			{
				/*SWITCH CASE IN SELECTED SSD TO BE INCREMENTED*/
				switch(Loc_u8SelectSsd)
				{
				case SSD_u8ONE:
					if(Loc_u16Counter % TEN != NINE)
					{
					Loc_u16Counter++;
					}
					else{
						Loc_u16Counter-=NINE;
					}
					break;
				case SSD_u8TWO:
					if(((Loc_u16Counter / TEN) % TEN) != NINE)
					{
						Loc_u16Counter+=TEN;
					}
					else
					{
						Loc_u16Counter-=NINTY;
					}
					break;
				case SSD_u8THREE:
					if((Loc_u16Counter / HUNDRED) % TEN != NINE)
					{
					Loc_u16Counter+=HUNDRED;
					}
					else
					{
						Loc_u16Counter-=NHUNDRED;
					}
					break;
				case SSD_u8FOUR:
					if((Loc_u16Counter / THOUSEND) % TEN != NINE)
					{
					Loc_u16Counter+=THOUSEND;
					}
					else
					{
						Loc_u16Counter-=NTHOUSEND;
					}
					break;
				}
			}
			/*DISPLAY THE NUMBER NUMBER*/
			Ssd_enuDisplayNumber(Loc_u16Counter);
		}
		/*READ DECREMNET BTN STATUS AND MAKE SURE THAT IT'S NOT IN START MODE AND IT'S IN SELECT MODE*/
		Dio_enuReadChannel(u8DECREMENT_BTN, &Loc_u8BtnStatus);
		if (Loc_u8BtnStatus == DIO_u8LOW
				&& GET_BIT(Loc_u8Flag , START_STOP_FLAG) == STOP) {
			if(GET_BIT(Loc_u8Flag , SELECT_FLAG) == TRUE)
				{
				/*SWITCH CASE IN SELECTED SSD TO BE DECREMENTED*/
					switch(Loc_u8SelectSsd)
					{
					case SSD_u8ONE:
							if(Loc_u16Counter % TEN != ZERO)
							{
							Loc_u16Counter--;
							}
							else
							{
								Loc_u16Counter+=NINE;
							}
						break;
					case SSD_u8TWO:
							if((Loc_u16Counter / TEN) % TEN != ZERO)
							{
							Loc_u16Counter-=TEN;
							}
							else
							{
								Loc_u16Counter+=NINTY;
							}
						break;
					case SSD_u8THREE:

							if((Loc_u16Counter / HUNDRED) % TEN != ZERO)
							{
								Loc_u16Counter-=HUNDRED;
							}
							else
							{
								Loc_u16Counter+=NHUNDRED;
							}
						break;
					case SSD_u8FOUR:

							if((Loc_u16Counter / THOUSEND) % TEN != ZERO)
							{
							Loc_u16Counter-=THOUSEND;
							}
							else
							{
								Loc_u16Counter+=NTHOUSEND;
							}
						break;
					}
				}
			/*DISPLAY THE NUMBER NUMBER*/
			Ssd_enuDisplayNumber(Loc_u16Counter);
		}
		/*READ START STOP BTN STATUS*/
		Dio_enuReadChannel(u8START_STOP_BTN, &Loc_u8BtnStatus);
		if (Loc_u8BtnStatus == DIO_u8LOW) {
			/*TOGGLE FLAG STATUS*/
			TGL_BIT(Loc_u8Flag, START_STOP_FLAG);
			/*CLEAR SELECT FLAG TO STOP BLINKING*/
			CLR_BIT(Loc_u8Flag, SELECT_FLAG);
			/*DELAY FOR DEBOUNCING*/
			_delay_ms(DEBOUNCING_DELAY);
		}
		/*CHECK IF SSD IN START MODE*/
		if (GET_BIT(Loc_u8Flag , START_STOP_FLAG) == TRUE) {
			/*IF THE COUNTER NOT REACHED ZERO OR STOPPED*/
			if (Loc_u16Counter != ZERO_INIT || Loc_u8BtnStatus == DIO_u8HIGH) {
				/*KEEP READ START STOP BTN STATUS*/
				Dio_enuReadChannel(u8START_STOP_BTN, &Loc_u8BtnStatus);
				/*DECREMENT THE COUNTER*/
				Loc_u16Counter--;
				/*DISPLAY THE COUNTER IS SSD*/
				Ssd_enuDisplayNumber(Loc_u16Counter);
				_delay_ms(SECOND);
			}
			/*IF COUNTER REACHED ZERO*/
			if(Loc_u16Counter == ZERO_INIT )
			{
				/*TOGGLE THE START STOP FLAG */
				TGL_BIT(Loc_u8Flag, START_STOP_FLAG);
			}
		}

	}
	return 0;
}

