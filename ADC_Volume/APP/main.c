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
#include "../MCAL/Adc/Adc.h"
#include "../HAL/Lcd/Lcd.h"
#include <avr/io.h>
#include <util/delay.h>

#define VVLOW_RANGE			0
#define VLOW_RANGE			128
#define LOW_RANGE			256
#define MID_RANGE			384
#define HIGH_RANGE			512
#define VHIGH_RANGE			640
#define VVHIGH_RANGE		768
#define MAX_RANGE			896

void Lcd_InitCG(void);

int main(void) {
	u16 Loc_u16AnalogResult = 0;
	Adc_tenuErrorStatus ReturnError;

	Port_vidInit();
	Lcd_vidInit();
	Adc_vidInit();
	Lcd_InitCG();
	while (1) {
		ReturnError = Adc_enuAnalogRead(ADC_AnalogChannelAdc0,
				&Loc_u16AnalogResult);
		Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00);
		Lcd_vidDisplayString((pu8) "VOLUME");
		if (ReturnError == ADC_enuOk) {
			if (Loc_u16AnalogResult >= VVLOW_RANGE
					&& Loc_u16AnalogResult < VLOW_RANGE) {
				Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
				Lcd_vidDisplayCharacter(0);
			} else if (Loc_u16AnalogResult >= VLOW_RANGE
					&& Loc_u16AnalogResult < LOW_RANGE) {
				Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
				Lcd_vidDisplayCharacter(0);
				Lcd_vidDisplayCharacter(1);

			} else if (Loc_u16AnalogResult >= LOW_RANGE
					&& Loc_u16AnalogResult < MID_RANGE) {
				Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
				Lcd_vidDisplayCharacter(0);
				Lcd_vidDisplayCharacter(1);
				Lcd_vidDisplayCharacter(2);

			} else if (Loc_u16AnalogResult >= MID_RANGE
					&& Loc_u16AnalogResult < HIGH_RANGE) {
				Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
				Lcd_vidDisplayCharacter(0);
				Lcd_vidDisplayCharacter(1);
				Lcd_vidDisplayCharacter(2);
				Lcd_vidDisplayCharacter(3);

			} else if (Loc_u16AnalogResult >= HIGH_RANGE
					&& Loc_u16AnalogResult < VHIGH_RANGE) {
				Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
				Lcd_vidDisplayCharacter(0);
				Lcd_vidDisplayCharacter(1);
				Lcd_vidDisplayCharacter(2);
				Lcd_vidDisplayCharacter(3);
				Lcd_vidDisplayCharacter(4);
			} else if (Loc_u16AnalogResult >= VHIGH_RANGE
					&& Loc_u16AnalogResult < VVHIGH_RANGE) {
				Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
				Lcd_vidDisplayCharacter(0);
				Lcd_vidDisplayCharacter(1);
				Lcd_vidDisplayCharacter(2);
				Lcd_vidDisplayCharacter(3);
				Lcd_vidDisplayCharacter(4);
				Lcd_vidDisplayCharacter(5);
			} else if (Loc_u16AnalogResult >= VVHIGH_RANGE
					&& Loc_u16AnalogResult < MAX_RANGE) {
				Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
				Lcd_vidDisplayCharacter(0);
				Lcd_vidDisplayCharacter(1);
				Lcd_vidDisplayCharacter(2);
				Lcd_vidDisplayCharacter(3);
				Lcd_vidDisplayCharacter(4);
				Lcd_vidDisplayCharacter(5);
				Lcd_vidDisplayCharacter(6);
			} else if (Loc_u16AnalogResult >= MAX_RANGE) {
				Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
				Lcd_vidDisplayCharacter(0);
				Lcd_vidDisplayCharacter(1);
				Lcd_vidDisplayCharacter(2);
				Lcd_vidDisplayCharacter(3);
				Lcd_vidDisplayCharacter(4);
				Lcd_vidDisplayCharacter(5);
				Lcd_vidDisplayCharacter(6);
				Lcd_vidDisplayCharacter(7);
			}
		}
		_delay_ms(500);
	}

	return 0;
}



void Lcd_InitCG(void)
{

	u8 VVeryLow[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
			0b00000, 0b11111 };
	u8 VeryLow[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
			0b11111, 0b11111 };
	u8 Low[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111,
			0b11111 };
	u8 MID[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111,
			0b11111 };
	u8 HIGH[] = { 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111,
			0b11111 };
	u8 VHIGH[] = { 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111,
			0b11111, 0b11111 };
	u8 VVHIGH[] = { 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111,
			0b11111, 0b11111 };
	u8 MAX[] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111,
			0b11111 };
	Lcd_vidCreateCustomCharacter(VVeryLow, 0);
	Lcd_vidCreateCustomCharacter(VeryLow, 1);
	Lcd_vidCreateCustomCharacter(Low, 2);
	Lcd_vidCreateCustomCharacter(MID, 3);
	Lcd_vidCreateCustomCharacter(HIGH, 4);
	Lcd_vidCreateCustomCharacter(VHIGH, 5);
	Lcd_vidCreateCustomCharacter(VVHIGH, 6);
	Lcd_vidCreateCustomCharacter(MAX, 7);
}
