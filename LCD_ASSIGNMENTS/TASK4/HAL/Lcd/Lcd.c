/*
 * Lcd.c
 *
 *  Created on: Mar 13, 2022
 *      Author: Kishk
 */

#include "../../Services/Bit_utils.h"
#include "../../Services/Std_types.h"
#include "../../MCAL/Port/Port.h"
#include "../../MCAL/Dio/Dio.h"
#include "Lcd.h"
#include "Lcd_prv.h"
#include "Lcd_cfg.h"
#include "util/delay.h"

/*
 * Function:  Lcd_vidInit
 * --------------------
 * INITIALIZE LCD TECHINIQUE
 */
void Lcd_vidInit(void) {
	/*DELAY TO MAKE SURE THE VOLTAGE IS STABLE*/
	_delay_ms(LCD_u8DELAY_FOR_STATBILITY);
	/*SET CONFIGURATION TO WRITE AN COMMAND*/
	Dio_enuWriteChannel(Lcd_u8RS, DIO_u8LOW);
	Dio_enuWriteChannel(Lcd_u8RW, DIO_u8LOW);
	/*SEND DESIRED COMMAND*/
	Lcd_vidPrvSendDataBus(LCD_u8FUNCTION_SET_CFG);
	/*APPLYING FALLING EDGE TO SEND THE COMMAND*/
	Lcd_ApplyingFallingEdgeEN()
	;
	/*DELAY FOR APPYING INITIALIZATION SYSTEM*/
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
	/*SEND DESIRED COMMAND*/
	Lcd_vidPrvSendDataBus(LCD_u8DISPLAY_ON_CFG);
	/*APPLYING FALLING EDGE TO SEND THE COMMAND*/
	Lcd_ApplyingFallingEdgeEN()
	;
	/*DELAY FOR APPYING INITIALIZATION SYSTEM*/
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
	/*SEND DESIRED COMMAND*/
	Lcd_vidPrvSendDataBus(LCD_u8CLR_DISPLAY_CFG);
	/*APPLYING FALLING EDGE TO SEND THE COMMAND*/
	Lcd_ApplyingFallingEdgeEN()
	;
	/*DELAY FOR CLEARING DISPLAY*/
	_delay_ms(LCD_u8DELAY_FOR_CLR_DISPLAY);
	/*SEND DESIRED COMMAND*/
	Lcd_vidPrvSendDataBus(LCD_u8ENTRY_MODE_SET_CFG);
	/*APPLYING FALLING EDGE TO SEND THE COMMAND*/
	Lcd_ApplyingFallingEdgeEN()
	;
	/*DELAY FOR APPYING INITIALIZATION SYSTEM*/
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);

}

/*
 * Function:  Lcd_vidSendCommand
 * --------------------
 * Copy_u8Command : DESIRED COMMAND.
 */
void Lcd_vidSendCommand(u8 Copy_u8Command) {
	/*SET CONFIGURATION TO WRITE AN COMMAND*/
	Dio_enuWriteChannel(Lcd_u8RS, DIO_u8LOW);
	Dio_enuWriteChannel(Lcd_u8RW, DIO_u8LOW);
	/*SEND DESIRED COMMAND*/
	Lcd_vidPrvSendDataBus(Copy_u8Command);
	/*APPLYING FALLING EDGE TO SEND THE COMMAND*/
	Lcd_ApplyingFallingEdgeEN()
	;
	/*DELAY FOR APPYING INITIALIZATION SYSTEM*/
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
}
/*
 * Function:  Lcd_vidDisplayCharacter
 * --------------------
 * Copy_u8Character : DESIRED DRAWN CHARACTER.
 */
void Lcd_vidDisplayCharacter(u8 Copy_u8Character) {
	/*SET CONFIGURATION TO SEND AN DATA*/
	Dio_enuWriteChannel(Lcd_u8RS, DIO_u8HIGH);
	Dio_enuWriteChannel(Lcd_u8RW, DIO_u8LOW);
	/*SEND DESIRED DATA*/
	Lcd_vidPrvSendDataBus(Copy_u8Character);
	/*APPLYING FALLING EDGE TO SEND THE COMMAND*/
	Lcd_ApplyingFallingEdgeEN()
	;
	/*DELAY FOR APPYING INITIALIZATION SYSTEM*/
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
}
/*
 * Function:  Lcd_vidDisplayNumber
 * --------------------
 * Copy_u8Character : DESIRED DRAWN NUMBER.
 */
void Lcd_vidDisplayNumber(u64 Copy_u64Number) {
	/*DEFINE VARIABLES*/
	u64 Loc_u64InverseNum = ONE;
	u8 Loc_u8ASCII = ZERO;
	/*CHECK IF THE NUMBER IS ZERO*/
	if (Copy_u64Number == ZERO) {
		/*DRAW ZERO IN LCD*/
		Lcd_vidDisplayCharacter('0');

	} else {
		/*IF IT'S ANY NUMBER EXCEPT ZERO*/
		while (Copy_u64Number != ZERO) {
			/*INVERSING THE NUMBER*/
			Loc_u64InverseNum =
					(Loc_u64InverseNum * TEN) + Copy_u64Number % TEN;
			Copy_u64Number /= TEN;
		}
		/*AFTER INVERSING THE NUMBER LOOP UNTIL DUMMY NUMBER "ONE"*/
		while (Loc_u64InverseNum != ONE) {
			/*STORE THE ASCII OF EACH DIGIT*/
			Loc_u8ASCII = '0' + (Loc_u64InverseNum % TEN);
			/*DRAW THE ASCII*/
			Lcd_vidDisplayCharacter(Loc_u8ASCII);
			/*DIVIDE BY TEN TO GET THE SECOND DIGIT*/
			Loc_u64InverseNum /= TEN;
		}
	}

}
/*
 * Function:  Lcd_vidDisplayString
 * --------------------
 * Add_pu8String : ADDRESS TO ARRAY OF CHARACTER TO BE DRAWN IN LCD
 */
void Lcd_vidDisplayString(pu8 Add_pu8String) {
	/*DEFINE ITERATOR WITH ZERO*/
	u8 Loc_u8Iterator = ZERO;
	/*WHILE LOOP UNTIL REACHING THE \0*/
	while (Add_pu8String[Loc_u8Iterator] != '\0') {
		/*DISPLAY THE CHARACTER AND INCREMENT THE ITERATOR*/
		Lcd_vidDisplayCharacter(Add_pu8String[Loc_u8Iterator]);
		Loc_u8Iterator++;
	}
}

/*
 * Function:  Lcd_vidGoTo
 * --------------------
 * Copy_u8Row : DESIRED ROW --> OPTIONS --> LCD_u8ROW_00 , LCD_u8ROW_01
 * Copy_u8Column : DESIRED COL --> OPTIONS --> START FROM LCD_u8COL_00 --> LCD_u8COL_15
 */
void Lcd_vidGoTo(u8 Copy_u8Row, u8 Copy_u8Column) {
	/*SET CONFIGURATION TO WRITE AN COMMAND*/
	Dio_enuWriteChannel(Lcd_u8RS, DIO_u8LOW);
	Dio_enuWriteChannel(Lcd_u8RW, DIO_u8LOW);
	/*SEND COMMAND TO CHANGE THE ROW AND COLUMN*/
	Lcd_vidPrvSendDataBus(Copy_u8Row + Copy_u8Column);
	/*APPLYING THE FALLING EDG TO APPLY THE COMMAND*/
	Lcd_ApplyingFallingEdgeEN()
	;
}

/*
 * Function:  Lcd_vidCreateCustomCharacter
 * --------------------
 * Add_pu8CustomChar : ADDRESS OF ARRAY TO BE SAVED AS CUSTOM CHARACTER.
 * Copy_u8Index : DESIRED INDEX TO SAVE THE CUSTOM CHARACTER
 */
void Lcd_vidCreateCustomCharacter(pu8 Add_pu8CustomChar, u8 Copy_u8Index) {
	/*DEFINE ITERATOR WITH ZERO */
	u8 Loc_u8Iterator = ZERO;
	/*CHECK IF THE DESIRED INDEX WITHIN CG-RAM RANGE*/
	if (Copy_u8Index < LCD_u8CGRAM_SPACE) {
		/*SET SENDING COMMAND CONFIGURATIONS*/
		Dio_enuWriteChannel(Lcd_u8RS, DIO_u8LOW);
		Dio_enuWriteChannel(Lcd_u8RW, DIO_u8LOW);
		/*SET POINTER TO CG RAM*/
		Lcd_vidPrvSendDataBus(0b01000000 + Copy_u8Index * 8);
		/*APPLYING THE FALLING EDGE TO APPLY THE COMMAND*/
		Lcd_ApplyingFallingEdgeEN()
		;
		/*SET SEND DATA CONFIGURATIONS*/
		Dio_enuWriteChannel(Lcd_u8RS, DIO_u8HIGH);
		Dio_enuWriteChannel(Lcd_u8RW, DIO_u8LOW);
		/*LOOP TO SAVE DESIRED CUSTOM CHARACTER*/
		for (Loc_u8Iterator = ZERO; Loc_u8Iterator < LCD_u8HIGHT; Loc_u8Iterator++) {
			Lcd_vidPrvSendDataBus(Add_pu8CustomChar[Loc_u8Iterator]);
			/*APPLYING THE FALLING EDGE TO SAVE DATA*/
			Lcd_ApplyingFallingEdgeEN()
			;
		}
	}
}
/*
 * Function:  Lcd_vidPrvSendDataBus
 * --------------------
 * PRIVATE FUNCTION TO SEND DATA IN DATA BUS
 *
 * Copy_u8Data : DESIRED SENDING DATA IN DATA BUS
 */
static void Lcd_vidPrvSendDataBus(u8 Copy_u8Data) {
	Dio_enuWriteChannel(LCD_u8D0, GET_BIT(Copy_u8Data, LCD_u8BIT_D0));
	Dio_enuWriteChannel(LCD_u8D1, GET_BIT(Copy_u8Data, LCD_u8BIT_D1));
	Dio_enuWriteChannel(LCD_u8D2, GET_BIT(Copy_u8Data, LCD_u8BIT_D2));
	Dio_enuWriteChannel(LCD_u8D3, GET_BIT(Copy_u8Data, LCD_u8BIT_D3));
	Dio_enuWriteChannel(LCD_u8D4, GET_BIT(Copy_u8Data, LCD_u8BIT_D4));
	Dio_enuWriteChannel(LCD_u8D5, GET_BIT(Copy_u8Data, LCD_u8BIT_D5));
	Dio_enuWriteChannel(LCD_u8D6, GET_BIT(Copy_u8Data, LCD_u8BIT_D6));
	Dio_enuWriteChannel(LCD_u8D7, GET_BIT(Copy_u8Data, LCD_u8BIT_D7));
}
