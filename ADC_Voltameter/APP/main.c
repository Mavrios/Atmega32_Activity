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

//#define DEBUG

#define SwitchPin		DIO_u8CHANNEL16
#define VOLTAGE			(5)
#define MilliVolt		((u32) 1000)
#define DecimalVolt		((u32) 100)
#define RESLUTION		1023.0
#define ZERO 			0


int main(void) {
	/*DEFINE VARIABLES*/
	/*VARIABLE TO STORE ANALOG RESULT*/
	u16 Loc_u16AnalogResult = ZERO;
	/*VARIABE TO STORE VOLTAGE*/
	u32 Loc_u32Voltage= 0 ;
	/*VARIABLE TO READ SWITCH*/
	u8  Loc_u8SwitchResult = 0;
	/*VARIABLE TO STORE FIRST DIGIT*/
	u8  Loc_u8FirstDigits = 0;
	/*VARIABLE TO CHECK ADC ERROR*/
	Adc_tenuErrorStatus CheckError;
	/*INIT SYSTEM*/
	Port_vidInit();
	Lcd_vidInit();
	Adc_vidInit();

	while (1) {
		/*READ SWITCH PIN*/
		Dio_enuReadChannel(SwitchPin , &Loc_u8SwitchResult);
		/*READ ANALOG VALUE*/
		CheckError = Adc_enuAnalogRead(ADC_AnalogChannelAdc0 , &Loc_u16AnalogResult);
#ifdef DEBUG
		if(CheckError != ADC_enuOk)
		{
			Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
			Lcd_vidDisplayString((pu8) "ERROR");
			_delay_ms(10000);
		}
#endif
		/*IF SWITCH NOT PRESSED*/
		if(Loc_u8SwitchResult == DIO_u8HIGH)
		{
			/*CLR LCD*/
			Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
			Lcd_vidGoTo(LCD_u8ROW_00,LCD_u8COL_03);
			/*PRINT ZEERO IN THE SECOND DIGIT AFTER POINT*/
			Lcd_vidDisplayCharacter('0');
			Lcd_vidGoTo(LCD_u8ROW_00,LCD_u8COL_00);
			/*CALCULATE THE VOLTAGE AND PRINT IT*/
			Loc_u32Voltage = Loc_u16AnalogResult * VOLTAGE * DecimalVolt;
			Loc_u32Voltage/= RESLUTION;
			Loc_u8FirstDigits = Loc_u32Voltage / DecimalVolt;
			Lcd_vidDisplayNumber(Loc_u8FirstDigits);
			Lcd_vidDisplayCharacter('.');

			Lcd_vidDisplayNumber(Loc_u32Voltage % DecimalVolt);
			Lcd_vidGoTo(LCD_u8ROW_01,LCD_u8COL_15);
			Lcd_vidDisplayCharacter('V');
		}
		else
		{
			/*CLR LCD*/
			Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
			Lcd_vidGoTo(LCD_u8ROW_00,LCD_u8COL_00);
			/*CALCULATE THE VOLTAGE AND PRINT IT*/
			Loc_u32Voltage = Loc_u16AnalogResult * VOLTAGE * MilliVolt;
			Loc_u32Voltage/= RESLUTION;
			Lcd_vidDisplayNumber(Loc_u32Voltage);
			Lcd_vidGoTo(LCD_u8ROW_01,LCD_u8COL_14);
			Lcd_vidDisplayString((pu8)"mV");
		}
		_delay_ms(500);
	}

	return 0;
}

