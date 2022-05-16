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
#include "../HAL/Lcd/Lcd.h"
#include <util/delay.h>

void SceneInit(void);

int main(void) {
	u8 LOC_u8Iterator = 0;
	Port_vidInit();
	Lcd_vidInit();
	u8 RunningGuy[] = { 0b01110, 0b01110, 0b00101, 0b11110, 0b00100, 0b01010,
			0b10001, 0b11111 };
	u8 Ground[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
			0b00000, 0b11111 };
	u8 Hole[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
			0b00000 };
	u8 Stairs[] = { 0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00111,
			0b01111, 0b11111 };
	u8 Wall[] = { 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001,
			0b11111 };
	u8 GuyWall[] = { 0b01111, 0b01111, 0b00101, 0b00111, 0b01101, 0b10101,
			0b00101, 0b01011 };
	Lcd_vidCreateCustomCharacter(RunningGuy, 0);
	Lcd_vidCreateCustomCharacter(Ground, 1);
	Lcd_vidCreateCustomCharacter(Hole, 2);
	Lcd_vidCreateCustomCharacter(Stairs, 3);
	Lcd_vidCreateCustomCharacter(Wall, 4);
	Lcd_vidCreateCustomCharacter(GuyWall, 5);
	while (1) {
		SceneInit();
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00);
		Lcd_vidDisplayCharacter(0);
		_delay_ms(800);
		for (LOC_u8Iterator = LCD_u8COL_01; LOC_u8Iterator <= LCD_u8COL_15;
				LOC_u8Iterator++) {
			Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter(0);
			Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00 + LOC_u8Iterator - 1);
			Lcd_vidDisplayCharacter(1);
			_delay_ms(800);
		}
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_15);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00);
		Lcd_vidDisplayCharacter(0);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(2);
		_delay_ms(800);

		for (LOC_u8Iterator = LCD_u8COL_01; LOC_u8Iterator <= LCD_u8COL_07;
				LOC_u8Iterator++) {
			Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter(0);
			Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00 + LOC_u8Iterator - 1);
			Lcd_vidDisplayCharacter(1);
			_delay_ms(800);
		}
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(0);
		_delay_ms(800);

		for (LOC_u8Iterator = LCD_u8COL_09; LOC_u8Iterator <= LCD_u8COL_15;
				LOC_u8Iterator++) {
			Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter(0);
			Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00 + LOC_u8Iterator - 1);
			Lcd_vidDisplayCharacter(1);
			_delay_ms(800);
		}
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_15);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
		Lcd_vidDisplayCharacter(0);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(3);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(2);
		_delay_ms(800);
		for (LOC_u8Iterator = LCD_u8COL_01; LOC_u8Iterator <= LCD_u8COL_07;
				LOC_u8Iterator++) {
			Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter(0);
			Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00 + LOC_u8Iterator - 1);
			Lcd_vidDisplayCharacter(1);
			_delay_ms(800);
		}
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_09);
		Lcd_vidDisplayCharacter(0);
		_delay_ms(800);
		for (LOC_u8Iterator = LCD_u8COL_10; LOC_u8Iterator <= LCD_u8COL_15;
				LOC_u8Iterator++) {
			Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter(0);
			Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00 + LOC_u8Iterator - 1);
			Lcd_vidDisplayCharacter(1);
			_delay_ms(800);
		}
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_15);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00);
		Lcd_vidDisplayCharacter(0);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(4);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(1);
		_delay_ms(800);
		for (LOC_u8Iterator = LCD_u8COL_01; LOC_u8Iterator <= LCD_u8COL_07;
				LOC_u8Iterator++) {
			Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter(0);
			Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00 + LOC_u8Iterator - 1);
			Lcd_vidDisplayCharacter(1);
			_delay_ms(800);
		}
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(5);
		_delay_ms(800);

		Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_05);
		Lcd_vidDisplayString((pu8) "Sorry!!");
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_06);
		Lcd_vidDisplayString((pu8) "DEAD");
		_delay_ms(3000);
	}
	return 0;
}

void SceneInit(void) {
	u8 LOC_u8Iterator = 0;
	Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
	for (LOC_u8Iterator = 0; LOC_u8Iterator <= LCD_u8COL_15; LOC_u8Iterator++) {
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00 + LOC_u8Iterator);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00 + LOC_u8Iterator);
		Lcd_vidDisplayCharacter(1);

	}
}
