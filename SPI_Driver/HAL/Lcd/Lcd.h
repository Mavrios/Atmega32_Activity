/*
 * Lcd.h
 *
 *  Created on: Mar 13, 2022
 *      Author: Kishk
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#define LCD_u8FUNCTION_SET_CFG			((u8) 0b00111000)
#define LCD_u8DISPLAY_ON_CFG			((u8) 0b00001100)
#define LCD_u8CLR_DISPLAY_CFG			((u8) 0b00000001)
#define LCD_u8ENTRY_MODE_SET_CFG		((u8) 0b00000110)


#define LCD_u8ROW_00				((u8)(0x80))
#define LCD_u8ROW_01				((u8)(0x80 + 0x40))

#define LCD_u8COL_00                 0
#define LCD_u8COL_01                 1
#define LCD_u8COL_02                 2
#define LCD_u8COL_03                 3
#define LCD_u8COL_04                 4
#define LCD_u8COL_05                 5
#define LCD_u8COL_06                 6
#define LCD_u8COL_07                 7
#define LCD_u8COL_08                 8
#define LCD_u8COL_09                 9
#define LCD_u8COL_10                 10
#define LCD_u8COL_11                 11
#define LCD_u8COL_12                 12
#define LCD_u8COL_13                 13
#define LCD_u8COL_14                 14
#define LCD_u8COL_15                 15


/*
 * Function:  Lcd_vidInit
 * --------------------
 * INITIALIZE LCD TECHINIQUE
 */
void Lcd_vidInit(void);
/*
 * Function:  Lcd_vidSendCommand
 * --------------------
 * Copy_u8Command : DESIRED COMMAND.
 */
void Lcd_vidSendCommand(u8 Copy_u8Command);
/*
 * Function:  Lcd_vidDisplayCharacter
 * --------------------
 * Copy_u8Character : DESIRED DRAWN CHARACTER.
 */
void Lcd_vidDisplayCharacter(u8 Copy_u8Character);
/*
 * Function:  Lcd_vidDisplayNumber
 * --------------------
 * Copy_u8Character : DESIRED DRAWN NUMBER.
 */
void Lcd_vidDisplayNumber(u64 Copy_u64Number);
/*
 * Function:  Lcd_vidCreateCustomCharacter
 * --------------------
 * Add_pu8CustomChar : ADDRESS OF ARRAY TO BE SAVED AS CUSTOM CHARACTER.
 * Copy_u8Index : DESIRED INDEX TO SAVE THE CUSTOM CHARACTER
 */
void Lcd_vidCreateCustomCharacter(pu8 Add_pu8CustomChar,u8 Copy_u8Index);
/*
 * Function:  Lcd_vidGoTo
 * --------------------
 * Copy_u8Row : DESIRED ROW --> OPTIONS --> LCD_u8ROW_00 , LCD_u8ROW_01
 * Copy_u8Column : DESIRED COL --> OPTIONS --> START FROM LCD_u8COL_00 --> LCD_u8COL_15
 */
void Lcd_vidGoTo(u8 Copy_u8Row , u8 Copy_u8Column);
/*
 * Function:  Lcd_vidDisplayString
 * --------------------
 * Add_pu8String : ADDRESS TO ARRAY OF CHARACTER TO BE DRAWN IN LCD
 */
void Lcd_vidDisplayString(pu8 Add_pu8String);

#endif /* HAL_LCD_LCD_H_ */
