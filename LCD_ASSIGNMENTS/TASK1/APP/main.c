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

int main(void)
{
	u8 LOC_u8Iterator = 0;
	Port_vidInit();
	Lcd_vidInit();

	while(1)
	{
		for(LOC_u8Iterator = 0 ; LOC_u8Iterator <= LCD_u8COL_15 ; LOC_u8Iterator++)
		{
			Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
			Lcd_vidGoTo(LCD_u8ROW_00 , LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter('X');
			_delay_ms(500);
		}
		for(LOC_u8Iterator = 0 ; LOC_u8Iterator <= LCD_u8COL_15 ; LOC_u8Iterator++)
		{
			Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
			Lcd_vidGoTo(LCD_u8ROW_01 , LCD_u8COL_00 + LOC_u8Iterator);
			Lcd_vidDisplayCharacter('X');
			_delay_ms(500);
		}
	}
	return 0;
}

