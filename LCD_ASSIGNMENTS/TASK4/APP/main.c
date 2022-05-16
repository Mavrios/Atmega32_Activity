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

int main(void) {
	u8 LOC_UL[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00001, 0b00010,
			0b00100, 0b01111 };
	u8 LOC_UR[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b10000, 0b01000,
			0b00100, 0b11110 };
	u8 LOC_BL[] = { 0b01000, 0b01000, 0b01000, 0b01000, 0b01000, 0b00000,
			0b00000, 0b00000 };
	u8 LOC_BR[] = { 0b00010, 0b00010, 0b00010, 0b00010, 0b00010, 0b00000,
			0b00000, 0b00000 };
	u8 LOC_UL2[] = { 0b00000, 0b00001, 0b00011, 0b00110, 0b01100, 0b11000,
			0b11000, 0b11111 };
	u8 LOC_UR2[] = { 0b00000, 0b10000, 0b11000, 0b01100, 0b00110, 0b00011,
			0b00011, 0b11111 };
	u8 LOC_BL2[] = { 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000,
			0b11000, 0b00000 };
	u8 LOC_BR2[] = { 0b00011, 0b00011, 0b00011, 0b00011, 0b00011, 0b00011,
			0b00011, 0b00000 };
	u8 LOC_UL3[] = { 0b00011, 0b00110, 0b01100, 0b11000, 0b11000, 0b11000,
			0b11111, 0b11111 };
	u8 LOC_UR3[] = { 0b11000, 0b01100, 0b00110, 0b00011, 0b00011, 0b00011,
			0b11111, 0b11111 };
	u8 LOC_BL3[] = { 0b11111, 0b11111, 0b11000, 0b11000, 0b11000, 0b11000,
			0b11000, 0b11000 };
	u8 LOC_BR3[] = { 0b11111, 0b11111, 0b00011, 0b00011, 0b00011, 0b00011,
			0b00011, 0b00011 };
	u8 LOC_BL34[] = { 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000,
			0b11000, 0b11000 };
	u8 LOC_BR34[] = { 0b00011, 0b00011, 0b00011, 0b00011, 0b00011, 0b00011,
			0b00011, 0b00011 };

	u8 LOC_UR4[] = { 0b00000, 0b00000, 0b11000, 0b11000, 0b11000, 0b11000,
			0b11000, 0b11000 };

	u8 LOC_UL4[] = { 0b00000, 0b00000, 0b00011, 0b00011, 0b00011, 0b00011,
			0b00011, 0b00011 };

	u8 LOC_MR4[] = { 0b01110, 0b00111, 0b00011, 0b00011, 0b00011, 0b00011,
			0b11111, 0b11111 };
	u8 LOC_ML4[] = { 0b01100, 0b11100, 0b11000, 0b11000, 0b11000, 0b11000,
			0b11111, 0b11111 };
	Port_vidInit();
	Lcd_vidInit();

	while (1) {
		Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
		Lcd_vidCreateCustomCharacter(LOC_UL, 0);
		Lcd_vidCreateCustomCharacter(LOC_UR, 1);
		Lcd_vidCreateCustomCharacter(LOC_BL, 2);
		Lcd_vidCreateCustomCharacter(LOC_BR, 3);

		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(0);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(2);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(3);

		_delay_ms(1000);

		Lcd_vidCreateCustomCharacter(LOC_UL2, 0);
		Lcd_vidCreateCustomCharacter(LOC_UR2, 1);
		Lcd_vidCreateCustomCharacter(LOC_BL2, 2);
		Lcd_vidCreateCustomCharacter(LOC_BR2, 3);

		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(0);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(2);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(3);
		_delay_ms(1000);

		Lcd_vidCreateCustomCharacter(LOC_UL3, 0);
		Lcd_vidCreateCustomCharacter(LOC_UR3, 1);
		Lcd_vidCreateCustomCharacter(LOC_BL3, 2);
		Lcd_vidCreateCustomCharacter(LOC_BR3, 3);

		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(0);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(1);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(2);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(3);
		_delay_ms(1000);

		Lcd_vidCreateCustomCharacter(LOC_UL4, 0);
		Lcd_vidCreateCustomCharacter(LOC_UR4, 1);
		Lcd_vidCreateCustomCharacter(LOC_ML4, 2);
		Lcd_vidCreateCustomCharacter(LOC_MR4, 3);
		Lcd_vidCreateCustomCharacter(LOC_BL3, 4);
		Lcd_vidCreateCustomCharacter(LOC_BR3, 5);
		Lcd_vidCreateCustomCharacter(LOC_BL34, 6);
		Lcd_vidCreateCustomCharacter(LOC_BR34, 7);

		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_06);
		Lcd_vidDisplayCharacter(0);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(2);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(3);
		Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_09);
		Lcd_vidDisplayCharacter(1);

		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_06);
		Lcd_vidDisplayCharacter(7);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_07);
		Lcd_vidDisplayCharacter(4);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_08);
		Lcd_vidDisplayCharacter(5);
		Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_09);
		Lcd_vidDisplayCharacter(6);
		_delay_ms(1000);
	}
	return 0;
}

