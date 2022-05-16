/*
 * Lcd_prv.h
 *
 *  Created on: Mar 13, 2022
 *      Author: Kishk
 */

#ifndef HAL_LCD_LCD_PRV_H_
#define HAL_LCD_LCD_PRV_H_


#define LCD_u8DELAY_FOR_STATBILITY		((u8) 30)
#define LCD_u8DELAY_FOR_CLR_DISPLAY		((u8) 2)
#define LCD_u8DELAY_FOR_APPLYING_SEQ	((u8) 1)

#define LCD_u8BIT_D0			((u8) 0)
#define LCD_u8BIT_D1			((u8) 1)
#define LCD_u8BIT_D2			((u8) 2)
#define LCD_u8BIT_D3			((u8) 3)
#define LCD_u8BIT_D4			((u8) 4)
#define LCD_u8BIT_D5			((u8) 5)
#define LCD_u8BIT_D6			((u8) 6)
#define LCD_u8BIT_D7			((u8) 7)


#define ZERO					0
#define ONE						1
#define TEN						10

#define LCD_u8CGRAM_SPACE		8
#define LCD_u8HIGHT				8

#define Lcd_ApplyingFallingEdgeEN()					Dio_enuWriteChannel(Lcd_u8EN , DIO_u8HIGH);\
	_delay_ms(1);\
	Dio_enuWriteChannel(Lcd_u8EN , DIO_u8LOW);\
	_delay_ms(1);

static void Lcd_vidPrvSendDataBus(u8 Copy_u8Data);

#endif /* HAL_LCD_LCD_PRV_H_ */
