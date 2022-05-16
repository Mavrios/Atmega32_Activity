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
  0b00010000,
  0b00010010,
  0b00010100,
  0b00011000,
  0b00011000,
  0b00010100,
  0b00010010,
  0b00010000
},{
  0b01000001,
  0b01001000,
  0b01010000,
  0b01100000,
  0b01100000,
  0b01010000,
  0b01001000,
  0b01000001
},{
  0b10000011,
  0b10010001,
  0b10100001,
  0b11000001,
  0b11000001,
  0b10100001,
  0b10010001,
  0b10000011
},{
  0b00000111,
  0b00100010,
  0b01000010,
  0b10000010,
  0b10000010,
  0b01000010,
  0b00100010,
  0b00000111
},{
  0b00001110,
  0b01000100,
  0b10000100,
  0b00000100,
  0b00000100,
  0b10000100,
  0b01000100,
  0b00001110
},{
  0b00011100,
  0b10001000,
  0b00001000,
  0b00001000,
  0b00001000,
  0b00001000,
  0b10001000,
  0b00011100
},{
  0b00111001,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00010000,
  0b00010000,
  0b00010000,
  0b00111001
},{
  0b01110011,
  0b00100010,
  0b00100010,
  0b00100011,
  0b00100000,
  0b00100000,
  0b00100000,
  0b01110011
},{
  0b11100111,
  0b01000100,
  0b01000100,
  0b01000111,
  0b01000000,
  0b01000000,
  0b01000000,
  0b11100111
},{
  0b11001111,
  0b10001000,
  0b10001000,
  0b10001111,
  0b10000001,
  0b10000001,
  0b10000001,
  0b11001111
},{
  0b10011110,
  0b00010000,
  0b00010000,
  0b00011110,
  0b00000010,
  0b00000010,
  0b00000010,
  0b10011110
},{
  0b00111100,
  0b00100000,
  0b00100000,
  0b00111100,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00111100
},{
  0b01111001,
  0b01000001,
  0b01000001,
  0b01111001,
  0b00001001,
  0b00001001,
  0b00001001,
  0b01111001
},{
  0b11110010,
  0b10000010,
  0b10000010,
  0b11110011,
  0b00010010,
  0b00010010,
  0b00010010,
  0b11110010
},{
  0b11100100,
  0b00000100,
  0b00000100,
  0b11100111,
  0b00100100,
  0b00100100,
  0b00100100,
  0b11100100
},{
  0b11001001,
  0b00001001,
  0b00001001,
  0b11001111,
  0b01001001,
  0b01001001,
  0b01001001,
  0b11001001
},{
  0b10010010,
  0b00010010,
  0b00010010,
  0b10011110,
  0b10010010,
  0b10010010,
  0b10010010,
  0b10010010
},{
  0b00100100,
  0b00100100,
  0b00100100,
  0b00111100,
  0b00100100,
  0b00100100,
  0b00100100,
  0b00100100
},{
  0b01001001,
  0b01001001,
  0b01001001,
  0b01111001,
  0b01001001,
  0b01001001,
  0b01001001,
  0b01001001
},{
  0b10010010,
  0b10010010,
  0b10010010,
  0b11110010,
  0b10010011,
  0b10010010,
  0b10010010,
  0b10010010
},{
  0b00100100,
  0b00100100,
  0b00100100,
  0b11100101,
  0b00100110,
  0b00100101,
  0b00100100,
  0b00100100
},{
  0b01001000,
  0b01001000,
  0b01001001,
  0b11001010,
  0b01001100,
  0b01001010,
  0b01001001,
  0b01001000
},{
  0b10010000,
  0b10010000,
  0b10010010,
  0b10010100,
  0b10011000,
  0b10010100,
  0b10010010,
  0b10010000
},{
  0b00100000,
  0b00100000,
  0b00100100,
  0b00101000,
  0b00110000,
  0b00101000,
  0b00100100,
  0b00100000
},{
  0b01000000,
  0b01000000,
  0b01001000,
  0b01010000,
  0b01100000,
  0b01010000,
  0b01001000,
  0b01000000
},{
  0b10000000,
  0b10000000,
  0b10010000,
  0b10100000,
  0b11000000,
  0b10100000,
  0b10010000,
  0b10000000
},{
  0b00000000,
  0b00000000,
  0b00100000,
  0b01000000,
  0b10000000,
  0b01000000,
  0b00100000,
  0b00000000
},{
  0b00000000,
  0b00000000,
  0b01000000,
  0b10000000,
  0b00000000,
  0b10000000,
  0b01000000,
  0b00000000
},{
  0b00000000,
  0b00000000,
  0b10000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b10000000,
  0b00000000
},{
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
}};
static const int IMAGES_LEN = sizeof(Loc_u8LedCols)/8;
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
