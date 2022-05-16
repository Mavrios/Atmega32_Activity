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

void LcdIntroPattern(void);

int main(void) {
	u8 LOC_u8Iterator = 0;
	u8 LOC_u8Row[2] = { LCD_u8ROW_00, LCD_u8ROW_01 };
	Port_vidInit();
	Lcd_vidInit();
	LcdIntroPattern();
	while (1) {
		while (LOC_u8Iterator + 4 <= 15) {
			Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
			Lcd_vidGoTo(LOC_u8Row[LOC_u8Iterator & 0x01],
					LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter('K');
			Lcd_vidGoTo(LOC_u8Row[!(LOC_u8Iterator & 0x01)],
					LCD_u8COL_00 + LOC_u8Iterator + 1);
			Lcd_vidDisplayCharacter('I');
			Lcd_vidGoTo(LOC_u8Row[LOC_u8Iterator & 0x01],
					LCD_u8COL_00 + LOC_u8Iterator + 2);
			Lcd_vidDisplayCharacter('S');
			Lcd_vidGoTo(LOC_u8Row[!(LOC_u8Iterator & 0x01)],
					LCD_u8COL_00 + LOC_u8Iterator + 3);
			Lcd_vidDisplayCharacter('H');
			Lcd_vidGoTo(LOC_u8Row[LOC_u8Iterator & 0x01],
					LCD_u8COL_00 + LOC_u8Iterator + 4);
			Lcd_vidDisplayCharacter('K');
			_delay_ms(700);
			LOC_u8Iterator++;
		}
		LOC_u8Iterator = 14;

		while (LOC_u8Iterator - 4 >= 0) {
			Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
			Lcd_vidGoTo(LOC_u8Row[LOC_u8Iterator & 0x01],
					LCD_u8COL_00 + LOC_u8Iterator - 4);
			Lcd_vidDisplayCharacter('K');
			Lcd_vidGoTo(LOC_u8Row[!(LOC_u8Iterator & 0x01)],
					LCD_u8COL_00 + LOC_u8Iterator - 3);
			Lcd_vidDisplayCharacter('I');
			Lcd_vidGoTo(LOC_u8Row[LOC_u8Iterator & 0x01],
					LCD_u8COL_00 + LOC_u8Iterator - 2);
			Lcd_vidDisplayCharacter('S');
			Lcd_vidGoTo(LOC_u8Row[!(LOC_u8Iterator & 0x01)],
					LCD_u8COL_00 + LOC_u8Iterator - 1);
			Lcd_vidDisplayCharacter('H');
			Lcd_vidGoTo(LOC_u8Row[LOC_u8Iterator & 0x01],
					LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter('K');
			_delay_ms(700);
			LOC_u8Iterator--;
		}
		LOC_u8Iterator = 1;
	}
	return 0;
}

void LcdIntroPattern(void){
	Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
	Lcd_vidGoTo(LCD_u8ROW_00,LCD_u8COL_00 );
	Lcd_vidDisplayCharacter('K');
	_delay_ms(800);
	Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
	Lcd_vidGoTo(LCD_u8ROW_00,LCD_u8COL_00 );
	Lcd_vidDisplayCharacter('H');
	Lcd_vidGoTo(LCD_u8ROW_01,LCD_u8COL_01 );
	Lcd_vidDisplayCharacter('K');
	_delay_ms(800);
	Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
	Lcd_vidGoTo(LCD_u8ROW_00,LCD_u8COL_00 );
	Lcd_vidDisplayCharacter('S');
	Lcd_vidGoTo(LCD_u8ROW_01,LCD_u8COL_01 );
	Lcd_vidDisplayCharacter('H');
	Lcd_vidGoTo(LCD_u8ROW_00,LCD_u8COL_02 );
	Lcd_vidDisplayCharacter('K');
	_delay_ms(800);
	Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
	Lcd_vidGoTo(LCD_u8ROW_00,LCD_u8COL_00 );
	Lcd_vidDisplayCharacter('I');
	Lcd_vidGoTo(LCD_u8ROW_01,LCD_u8COL_01 );
	Lcd_vidDisplayCharacter('S');
	Lcd_vidGoTo(LCD_u8ROW_00,LCD_u8COL_02 );
	Lcd_vidDisplayCharacter('H');
	Lcd_vidGoTo(LCD_u8ROW_01,LCD_u8COL_03 );
	Lcd_vidDisplayCharacter('K');
	_delay_ms(800);

}

