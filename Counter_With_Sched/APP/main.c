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
#include "../HAL/Sched/Sched.h"
#include "../HAL/Switch/Switch.h"
#include "../HAL/Ssd/Ssd.h"
#include <avr/io.h>
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

void ApplicationTask(void);
void BlinkTask(void);
void CountingTask(void);

/*FLAG VARIABLE
 * BIT0 : START STOP FLAG
 * BIT1 : SELECT FLAG*/
u8 Loc_u8Flag;
/*SELECTED LCD TO BE EDIT*/
u8 Loc_u8SelectSsd;

/*COUNTER VARIABLE TO BE DISPLAYED IN SSD*/
u16 Loc_u16Counter = ZERO_INIT;

int main(void) {


	Sched_tstrConfigurations SwitchTask={
			.first_delay = 2,
			.Periodicity = 5,
			.State = 1,
			.Periority = 0,
			.CallbckFcn = Switch_Task
	};

	Sched_tstrConfigurations BlinksTask={
			.first_delay = 2,
			.Periodicity = DELAY_BETWEEN_BLINK,
			.State = 1,
			.Periority = 2,
			.CallbckFcn = BlinkTask
	};

	Sched_tstrConfigurations CounterTask={
			.first_delay = 2,
			.Periodicity = SECOND,
			.State = 1,
			.Periority = 3,
			.CallbckFcn = CountingTask
	};

	Sched_tstrConfigurations AppTask={
			.first_delay = 105,
			.Periodicity = 100,
			.State = 1,
			.Periority = 1,
			.CallbckFcn = ApplicationTask
	};

	/*INITIALIZE PORT PINS*/
	Port_vidInit();
	/*DISPLAY SSD NUMBER (ZERO)*/
	Ssd_enuDisplayNumber(ZERO);

	Sched_enuRegisterTask(&SwitchTask);
	Sched_enuRegisterTask(&BlinksTask);
	Sched_enuRegisterTask(&CounterTask);
	Sched_enuRegisterTask(&AppTask);
	Sched_vidInit();
	Sched_vidStart();


	/*SUPER LOOP*/
	while (1) {

	}
	return 0;
}


void ApplicationTask(void)
{
	/*DELCARE VARIABLE*/



	/*VARIABLE TO STORE BTN STATUS*/
	u8 Loc_u8BtnStatus = ONE_INIT;

	/*READ SELECT BTN STATUS AND CHECK IF STYSTEM IS IN STOP MODE*/
	Switch_readState(Select_Btn,&Loc_u8BtnStatus);
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

	}
	/*READ INCREMENT BTN STATUS AND MAKE SURE THAT IT'S NOT IN START MODE AND IT'S IN SELECT MODE*/
	Switch_readState(Increment_Btn,&Loc_u8BtnStatus);
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
	Switch_readState(Decrement_Btn,&Loc_u8BtnStatus);
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
	Switch_readState(Start_Btn,&Loc_u8BtnStatus);
	if (Loc_u8BtnStatus == DIO_u8LOW) {
		/*TOGGLE FLAG STATUS*/
		TGL_BIT(Loc_u8Flag, START_STOP_FLAG);
		/*CLEAR SELECT FLAG TO STOP BLINKING*/
		CLR_BIT(Loc_u8Flag, SELECT_FLAG);
		/*DELAY FOR DEBOUNCING*/
	}


}



void BlinkTask(void)
{
	static u8 State = ZERO;
	/*CHECK IF SELECT IS TRUE*/
	if (GET_BIT(Loc_u8Flag , SELECT_FLAG) == TRUE) {
		/*KEEP BLINKING THE CURRENT SSD*/
		State^=0x01;
		if(State == 1)
		{
			Ssd_enuDisableSsd(Loc_u8SelectSsd);
		}
		else{
			Ssd_enuDisplayNumber(Loc_u16Counter);
		}

	}
}


void CountingTask(void){
	u8 Loc_u8BtnStatus;
	/*CHECK IF SSD IN START MODE*/
	if (GET_BIT(Loc_u8Flag , START_STOP_FLAG) == TRUE) {
		/*KEEP READ START STOP BTN STATUS*/
		Switch_readState(Start_Btn,&Loc_u8BtnStatus);
		/*IF THE COUNTER NOT REACHED ZERO OR STOPPED*/
		if (Loc_u16Counter != ZERO_INIT || Loc_u8BtnStatus == DIO_u8HIGH) {
			/*DECREMENT THE COUNTER*/
			Loc_u16Counter--;
			/*DISPLAY THE COUNTER IS SSD*/
			Ssd_enuDisplayNumber(Loc_u16Counter);
		}
		/*IF COUNTER REACHED ZERO*/
		if(Loc_u16Counter == ZERO_INIT )
		{
			/*TOGGLE THE START STOP FLAG */
			TGL_BIT(Loc_u8Flag, START_STOP_FLAG);
		}
	}
}
