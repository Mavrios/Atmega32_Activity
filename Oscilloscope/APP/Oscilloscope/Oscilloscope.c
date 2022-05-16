/*
 * Oscilloscope.c
 *
 *  Created on: May 7, 2022
 *      Author: Kishk
 */

#include "../../SERVICES/Std_types.h"
#include "../../SERVICES/Bit_utils.h"
#include "../../SERVICES/Atmega32_Registers.h"
#include "../../MCAL/ICU/ICU.h"
#include "../../HAL/Lcd/Lcd.h"
#include "util/delay.h"
#include "Oscilloscope.h"
#include "Oscilloscope_prv.h"
void Oscilloscope_vidOvfCount(void);

ICU_tstrConfig ICU_Cfg = { .ICU_pfCbf = Oscilloscope_vidInterrupt, .OVF_pfCbf =
		Oscilloscope_vidOvfCount, .ICU_u8EdgeSelect = ICU_u8RISING_EDGE,
		.ICU_u8NoiseCanceler =
		ICU_u8NOISE_CANCELER_N_ACT, .ICU_u8Prescaller = ICU_Div_By_1,
		.ICU_u8InterruptCtrl = ICU_u8INTERRUPT_ON };

volatile OSC_tenuStates Osc_enuStates;

volatile u64 Osc_Snap1;
volatile u64 Osc_Snap2;
volatile u64 Osc_Snap3;
volatile u16 Osc_Counter;
u8 Upper[] = { 0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
		0b00000 };
u8 Buttom[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111,
		0b11111 };
u8 Split0[] = { 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000,
		0b10000 };
u8 Split1[] = { 0b11000, 0b01000, 0b01000, 0b01000, 0b01000, 0b01000, 0b01000,
		0b01000 };
u8 Split2[] = { 0b11100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100,
		0b00100 };
u8 Split3[] = { 0b11110, 0b00010, 0b00010, 0b00010, 0b00010, 0b00010, 0b00010,
		0b00010 };
u8 Split4[] = { 0b11111, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001,
		0b00001 };

void Oscilloscope_vidInit(void) {
	Lcd_vidInit();
	Lcd_vidCreateCustomCharacter(Upper, 0);
	Lcd_vidCreateCustomCharacter(Buttom, 1);
	Lcd_vidCreateCustomCharacter(Split0, 2);
	Lcd_vidCreateCustomCharacter(Split1, 3);
	Lcd_vidCreateCustomCharacter(Split2, 4);
	Lcd_vidCreateCustomCharacter(Split3, 5);
	Lcd_vidCreateCustomCharacter(Split4, 6);
	Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00);
	SREG |= (1 << 7);
	ICU_enuInitStart(&ICU_Cfg);

}

void Oscilloscope_vidInterrupt(void) {
	switch (Osc_enuStates) {
	case OSC_enuStart:
		Osc_Snap1 = Osc_Snap2 = Osc_Snap3 = Osc_Counter=0;
		Osc_Snap1 = ICU_u16ReadICR();
		ICU_Cfg.ICU_u8EdgeSelect = ICU_u8FALLING_EDGE;
		ICU_enuInitStart(&ICU_Cfg);
		Osc_enuStates++;
		break;

	case OSC_enuF1:
		Osc_Snap2 = ICU_u16ReadICR() + (Osc_Counter * 65536);
		ICU_Cfg.ICU_u8EdgeSelect = ICU_u8RISING_EDGE;
		ICU_enuInitStart(&ICU_Cfg);
		Osc_enuStates++;
		break;

	case OSC_enuEND:
		Osc_Snap3 = ICU_u16ReadICR() + (Osc_Counter * 65536);
		ICU_vidStop();
		Oscilloscope_vidDisplay();
		ICU_Cfg.ICU_u8EdgeSelect = ICU_u8RISING_EDGE;
		Osc_enuStates = OSC_enuStart;
		_delay_ms(500);
		ICU_enuInitStart(&ICU_Cfg);
		break;
	}
}

void Oscilloscope_vidDisplay(void) {
	u8 Loc_u8Iter;
	u32 Loc_u32Ton = (Osc_Snap2 - Osc_Snap1);
	u32 Loc_u32Ttotal = Osc_Snap3 - Osc_Snap1;
	u64 Loc_u64Freq = F_CPU / Loc_u32Ttotal;
	u32 Loc_u32Duty = (Loc_u32Ton*100.0) / (float)Loc_u32Ttotal;
	u8 Loc_u8Split = ((Loc_u32Duty % 10) / 2) + 2;
	u8 Loc_u8UpperNum = (Loc_u32Duty / 100.0) * 16;
	u8 Loc_u8ButtomNum = 16 - Loc_u8UpperNum;
	Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
//	Lcd_vidDisplayNumber(Loc_u32Duty);
	Lcd_vidGoTo(LCD_u8ROW_00, LCD_u8COL_00);
	for (Loc_u8Iter = 0; Loc_u8Iter < Loc_u8UpperNum; Loc_u8Iter++) {
		Lcd_vidDisplayCharacter(0);
	}
	Lcd_vidDisplayCharacter(Loc_u8Split);
	for (Loc_u8Iter = 0; Loc_u8Iter < Loc_u8ButtomNum; Loc_u8Iter++) {
		Lcd_vidDisplayCharacter(1);
	}
	Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_00);
	Lcd_vidDisplayString((pu8) "Freq=");
	if (Loc_u64Freq >= OSC_MHZ) {
		Lcd_vidDisplayNumber(Loc_u64Freq / OSC_MHZ);
		Lcd_vidDisplayString((pu8) "MHz");
	} else if (Loc_u64Freq >= OSC_KHZ) {
		Lcd_vidDisplayNumber(Loc_u64Freq / OSC_KHZ);
		Lcd_vidDisplayString((pu8) "KHz");
	} else {
		Lcd_vidDisplayNumber(Loc_u64Freq);
		Lcd_vidDisplayString((pu8) "Hz");
	}
	Lcd_vidGoTo(LCD_u8ROW_01, LCD_u8COL_13);
	Lcd_vidDisplayNumber(Loc_u32Duty);
	Lcd_vidDisplayCharacter('%');

}

void Oscilloscope_vidOvfCount(void) {
	Osc_Counter++;
}
