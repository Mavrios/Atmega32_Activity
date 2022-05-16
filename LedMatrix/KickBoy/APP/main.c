/*
 * main.c
 *
 *  Created on: Apr 16, 2022
 *      Author: Kishk
 */


#include "../SERVICES/Std_types.h"
#include "../SERVICES/Bit_utils.h"
#include "../MCAL/Port/Port.h"
#include "../MCAL/Dio/Dio.h"
#include "../HAL/Sched/Sched.h"
#include <util/delay.h>
#include <avr/io.h>

static u8 Loc_u8Scene;
void Led_DisplayTask(void);
void Led_DisplaySceneTask(void);

static const u8 Loc_u8LedCols[][8] = {
		{
		  0b00111000,
		  0b00111000,
		  0b00111000,
		  0b10010000,
		  0b01111011,
		  0b00010011,
		  0b00101100,
		  0b00100000
		},{
		  0b00111000,
		  0b00111000,
		  0b00111000,
		  0b10010011,
		  0b01111011,
		  0b00010000,
		  0b00101000,
		  0b00100100
		}};
		const int IMAGES_LEN = sizeof(Loc_u8LedCols)/8;

int main(void)
{
	Sched_tstrConfigurations Loc_LedMatrixTask={
			.first_delay = 0,
			.Periodicity = 1,
			.State =1 ,
			.Periority = 1,
			.CallbckFcn=Led_DisplayTask,
	};
	Sched_tstrConfigurations Loc_LedMatrixSceneTask={
			.first_delay = 0,
			.Periodicity = 100,
			.State =1 ,
			.Periority = 0,
			.CallbckFcn=Led_DisplaySceneTask,
	};
	/*INIT SYSTEM*/
	Port_vidInit();
	Sched_vidInit();
	Sched_enuRegisterTask(&Loc_LedMatrixTask);
	Sched_enuRegisterTask(&Loc_LedMatrixSceneTask);
	Sched_vidStart();


	while(1);

	return 0;
}

void Led_DisplaySceneTask(void)
{
	Loc_u8Scene++;
	if(Loc_u8Scene >= IMAGES_LEN)
	{
		Loc_u8Scene = 0;
	}
}


void Led_DisplayTask(void)
{
	static u8 Loc_u8Iterator;
	static u8 state;
	static u8 Loc_u8LedRows[8]={0xFE,0xFD,0xFB , 0xF7 , 0xEF,0xDF,0xBF,0x7F};
	if(Loc_u8Iterator>7)
	{
		Loc_u8Iterator = 0;
	}
	if(state)
	{
		Dio_enuWritePort(DIO_u8PORTD , 0);

	}
	else{

		Dio_enuWritePort(DIO_u8PORTA , Loc_u8LedRows[Loc_u8Iterator]);
		Dio_enuWritePort(DIO_u8PORTD , Loc_u8LedCols[Loc_u8Scene][Loc_u8Iterator]);
		Loc_u8Iterator++;
	}
	state ^=1;
}
