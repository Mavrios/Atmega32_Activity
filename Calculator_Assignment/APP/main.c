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
#include "../HAL/Keypad/Keypad.h"
#include <util/delay.h>
//#define DEBUG

#define FIRST_PARM_PRESSED	0
#define SECOND_PARM_PRESSED	5
#define OP_PRESSED			1
#define LAST_PRESSED		2
#define PARM1_MAX			3
#define PARM2_MAX			4

#define PREV_COLUMN			1
#define ZERO_INIT			0
#define ADDITION			0
#define SUBTRACTION			1
#define MULTIPLY			2
#define DIVIDE				3

#define NO_PRESSED_KEY		0

#define TEN					10
int main(void) {
	/*DEFINING VARIABLES*/
	/*VARIABLE TO STORE PRESSED KEY*/
	u8 LOC_u8Key = 0;
	/*VARIABLE TO SAVE THE NEXT COLUMN*/
	u8 Loc_u8Column = 0;
	/*VARIABLE FOR SETTINGS FLAGS
	 * BIT0: FIRST PARAMETER PRESSED FLAG
	 * BIT1: SECONDS PARAMETER PRESSED FLAG
	 * BIT2: OPERATOR PRESSED FLAG
	 * BIT3: LAST PRESSED FLAG OPERATOR OR DIGIT
	 * BIT4: PARAMETER1 MAX DIGITS FLAG
	 * BIT5: PARAMETER2 MAX DIGITS FLAG
	 */
	u8 Loc_u8Flag = 0;
	/*VARIABLE TO STORE PARAMETER1*/
	s8 Loc_s8Par1 = 0;
	/*VARIABLE TO STORE PARAMETER2*/
	s8 Loc_s8Par2 = 0;
	/*VARIABLE TO STORE OPERATOR*/
	u8 Loc_u8Operator = 0;

	/*INITIALIZE PORT PINS*/
	Port_vidInit();
	/*INITIALIZE LCD*/
	Lcd_vidInit();

	/*SUPER LOOP*/
	while (1) {
		/*CHECK IF IF THERE'S PRESSED KEY*/
		Keypad_enuKeyPressed(&LOC_u8Key);
		/*IF NOT EQUAL ZERO MEANS PRESSED KEY*/
		if (LOC_u8Key != NO_PRESSED_KEY) {
			/*SWITCH TO RETURN VALUE FROM PRESSED KEY*/
			switch (LOC_u8Key) {
			/*PLUS OPERATOR*/
			case '+':
				/*CHECKING IF THE FIRST PARAMETER IS ADDED AND THE LAST PRESSED KEY IS DIGIT*/
				if (GET_BIT(Loc_u8Flag,
						FIRST_PARM_PRESSED) && GET_BIT(Loc_u8Flag, LAST_PRESSED)) {
					/*SET OPERATOR IS ADDITION*/
					Loc_u8Operator = ADDITION;
					/*SET GOTOXY FOR LCD TO PRINT OPERATOR*/
					Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
					/*PRINT OPERATOR*/
					Lcd_vidDisplayCharacter('+');
					/*SET OPERATOR PRESSED FLAG*/
					SET_BIT(Loc_u8Flag, OP_PRESSED);
					/*CLR LAST PRESSED DIGIT FLAG*/
					CLR_BIT(Loc_u8Flag, LAST_PRESSED);
				}
				/*CHECK IF THE FIRST PARAMETER PRESSED AND OPERATOR IS THE LAST PRESSED KEY THAT MEAN USER WANT TO CHANGE OPERATOR*/
				else if (GET_BIT(Loc_u8Flag,
						FIRST_PARM_PRESSED) && !GET_BIT(Loc_u8Flag, LAST_PRESSED)) {
					/*SET OPERATOR AS ADDITION*/
					Loc_u8Operator = ADDITION;
					/*SET GOTOXY FOR LCD TO PRINT OPERATOR*/
					Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column - PREV_COLUMN);
					/*PRINT OPERATOR*/
					Lcd_vidDisplayCharacter('+');
					/*SET OPERATOR PRESSED FLAG*/
					SET_BIT(Loc_u8Flag, OP_PRESSED);
					/*CLR LAST PRESSED DIGIT FLAG*/
					CLR_BIT(Loc_u8Flag, LAST_PRESSED);
				}
				break;
			case '-':
				/*CHECKING IF THE FIRST PARAMETER IS ADDED AND THE LAST PRESSED KEY IS DIGIT*/
				if (GET_BIT(Loc_u8Flag,
						FIRST_PARM_PRESSED) && GET_BIT(Loc_u8Flag, LAST_PRESSED)) {
					/*SET OPERATOR IS SUBTRACTION*/
					Loc_u8Operator = SUBTRACTION;
					/*SET GOTOXY FOR LCD TO PRINT OPERATOR*/
					Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
					/*PRINT OPERATOR*/
					Lcd_vidDisplayCharacter('-');
					/*SET OPERATOR PRESSED FLAG*/
					SET_BIT(Loc_u8Flag, OP_PRESSED);
					/*CLR LAST PRESSED DIGIT FLAG*/
					CLR_BIT(Loc_u8Flag, LAST_PRESSED);
				}
				/*CHECK IF THE FIRST PARAMETER PRESSED AND OPERATOR IS THE LAST PRESSED KEY THAT MEAN USER WANT TO CHANGE OPERATOR*/
				else if (GET_BIT(Loc_u8Flag,
						FIRST_PARM_PRESSED) && !GET_BIT(Loc_u8Flag, LAST_PRESSED)) {
					/*SET OPERATOR AS SUBTRACTIONS*/
					Loc_u8Operator = SUBTRACTION;
					/*SET GOTOXY FOR LCD TO PRINT OPERATOR*/
					Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column - PREV_COLUMN);
					/*PRINT OPERATOR*/
					Lcd_vidDisplayCharacter('-');
					/*SET OPERATOR PRESSED FLAG*/
					SET_BIT(Loc_u8Flag, OP_PRESSED);
					/*CLR LAST PRESSED DIGIT FLAG*/
					CLR_BIT(Loc_u8Flag, LAST_PRESSED);
				}
				break;

			case '*':
				/*CHECKING IF THE FIRST PARAMETER IS ADDED AND THE LAST PRESSED KEY IS DIGIT*/
				if (GET_BIT(Loc_u8Flag,
						FIRST_PARM_PRESSED) && GET_BIT(Loc_u8Flag, LAST_PRESSED)) {
					/*SET OPERATOR IS MULTIPLY*/
					Loc_u8Operator = MULTIPLY;
					/*SET GOTOXY FOR LCD TO PRINT OPERATOR*/
					Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
					/*PRINT OPERATOR*/
					Lcd_vidDisplayCharacter('*');
					/*SET OPERATOR PRESSED FLAG*/
					SET_BIT(Loc_u8Flag, OP_PRESSED);
					/*CLR LAST PRESSED DIGIT FLAG*/
					CLR_BIT(Loc_u8Flag, LAST_PRESSED);
				}
				/*CHECK IF THE FIRST PARAMETER PRESSED AND OPERATOR IS THE LAST PRESSED KEY THAT MEAN USER WANT TO CHANGE OPERATOR*/
				else if (GET_BIT(Loc_u8Flag,
						FIRST_PARM_PRESSED) && !GET_BIT(Loc_u8Flag, LAST_PRESSED)) {
					/*SET OPERATOR IS MULTIPLY*/
					Loc_u8Operator = MULTIPLY;
					/*SET GOTOXY FOR LCD TO PRINT OPERATOR*/
					Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column - PREV_COLUMN);
					/*PRINT OPERATOR*/
					Lcd_vidDisplayCharacter('*');
					/*SET OPERATOR PRESSED FLAG*/
					SET_BIT(Loc_u8Flag, OP_PRESSED);
					/*CLR LAST PRESSED DIGIT FLAG*/
					CLR_BIT(Loc_u8Flag, LAST_PRESSED);
				}
				break;

			case '/':
				/*CHECKING IF THE FIRST PARAMETER IS ADDED AND THE LAST PRESSED KEY IS DIGIT*/
				if (GET_BIT(Loc_u8Flag,
						FIRST_PARM_PRESSED) && GET_BIT(Loc_u8Flag, LAST_PRESSED)) {
					/*SET OPERATOR IS DIVIDE*/
					Loc_u8Operator = DIVIDE;
					/*SET GOTOXY FOR LCD TO PRINT OPERATOR*/
					Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
					/*PRINT OPERATOR*/
					Lcd_vidDisplayCharacter('/');
					/*SET OPERATOR PRESSED FLAG*/
					SET_BIT(Loc_u8Flag, OP_PRESSED);
					/*CLR LAST PRESSED DIGIT FLAG*/
					CLR_BIT(Loc_u8Flag, LAST_PRESSED);
				}
				/*CHECK IF THE FIRST PARAMETER PRESSED AND OPERATOR IS THE LAST PRESSED KEY THAT MEAN USER WANT TO CHANGE OPERATOR*/
				else if (GET_BIT(Loc_u8Flag,
						FIRST_PARM_PRESSED) && !GET_BIT(Loc_u8Flag, LAST_PRESSED)) {
					/*SET OPERATOR IS DIVIDE*/
					Loc_u8Operator = DIVIDE;
					/*SET GOTOXY FOR LCD TO PRINT OPERATOR*/
					Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column - PREV_COLUMN);
					/*PRINT OPERATOR*/
					Lcd_vidDisplayCharacter('/');
					/*SET OPERATOR PRESSED FLAG*/
					SET_BIT(Loc_u8Flag, OP_PRESSED);
					/*CLR LAST PRESSED DIGIT FLAG*/
					CLR_BIT(Loc_u8Flag, LAST_PRESSED);

				}
				break;
				/*CLEAR BUTTON*/
			case 'C':
				/*RESET ALL FLAGS AND VARAIBLES AND CLR LCD*/
				CLR_BIT(Loc_u8Flag, FIRST_PARM_PRESSED);
				CLR_BIT(Loc_u8Flag, SECOND_PARM_PRESSED);
				CLR_BIT(Loc_u8Flag, OP_PRESSED);
				CLR_BIT(Loc_u8Flag, LAST_PRESSED);
				CLR_BIT(Loc_u8Flag, PARM1_MAX);
				CLR_BIT(Loc_u8Flag, PARM2_MAX);
				Loc_s8Par1 = ZERO_INIT;
				Loc_s8Par2 = ZERO_INIT;
				Loc_u8Column = ZERO_INIT;
				Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
				break;

				/*ENTER BUTTON*/
			case 'E':
				/*CHECK IF THE SECOND PARAMETER PRESSED*/
				if (GET_BIT(Loc_u8Flag, SECOND_PARM_PRESSED)) {
					switch (Loc_u8Operator) {
					case ADDITION:
						Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
						Lcd_vidDisplayCharacter('=');
						Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
						Lcd_vidDisplayCharacter(' ');
						Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
						Lcd_vidDisplayNumber(Loc_s8Par1 + Loc_s8Par2);
						break;
					case SUBTRACTION:
						Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
						Lcd_vidDisplayCharacter('=');
						Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
						if (Loc_s8Par1 < Loc_s8Par2) {
							Lcd_vidDisplayCharacter(' ');
							Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
							Lcd_vidDisplayCharacter('-');
							Lcd_vidDisplayNumber(Loc_s8Par2 - Loc_s8Par1);
						}
						else
						{
							Lcd_vidDisplayNumber(Loc_s8Par2 - Loc_s8Par1);

						}
						break;
					case MULTIPLY:
						Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
						Lcd_vidDisplayCharacter('=');
						Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
						Lcd_vidDisplayCharacter(' ');
						Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
						Lcd_vidDisplayNumber(Loc_s8Par1 * Loc_s8Par2);
						break;
					case DIVIDE:
						if (Loc_s8Par2 != 0) {
							Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
							Lcd_vidDisplayCharacter('=');
							Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
							Lcd_vidDisplayCharacter(' ');
							Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column++);
							Lcd_vidDisplayNumber(Loc_s8Par1 / Loc_s8Par2);
						} else {
							Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
							Lcd_vidDisplayString((pu8) "CAN'T DIVID BY 0");
							_delay_ms(3000);
							Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
						}
						break;
					}
				} else {
					Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
					Lcd_vidDisplayString((pu8) "Error Calculation!!");
					_delay_ms(3000);
					Lcd_vidSendCommand(LCD_u8CLR_DISPLAY_CFG);
				}
				/*RESET FLAGS AND VARIABLES VALUES*/
				Loc_s8Par1 = ZERO_INIT;
				Loc_s8Par2 = ZERO_INIT;
				Loc_u8Column = ZERO_INIT;
				CLR_BIT(Loc_u8Flag, FIRST_PARM_PRESSED);
				CLR_BIT(Loc_u8Flag, SECOND_PARM_PRESSED);
				CLR_BIT(Loc_u8Flag, OP_PRESSED);
				CLR_BIT(Loc_u8Flag, LAST_PRESSED);
				CLR_BIT(Loc_u8Flag, PARM1_MAX);
				CLR_BIT(Loc_u8Flag, PARM2_MAX);
				break;
				/*THAT MEANS DIGITS INPUTS*/
			default:
				Lcd_vidGoTo(LCD_u8ROW_00, Loc_u8Column);
				SET_BIT(Loc_u8Flag, LAST_PRESSED);
				if (!GET_BIT(Loc_u8Flag, OP_PRESSED)) {
					SET_BIT(Loc_u8Flag, FIRST_PARM_PRESSED);
					if (Loc_s8Par1 == ZERO_INIT) {
						Loc_u8Column++;
						Loc_s8Par1 += (LOC_u8Key - '0');
						Lcd_vidDisplayCharacter(LOC_u8Key);

					} else {
						if (!GET_BIT(Loc_u8Flag, PARM1_MAX)) {
							Loc_u8Column++;
							Loc_s8Par1 *= TEN;
							Loc_s8Par1 += (LOC_u8Key - '0');
							SET_BIT(Loc_u8Flag, PARM1_MAX);
							Lcd_vidDisplayCharacter(LOC_u8Key);
#ifdef DEBUG

							Lcd_vidGoTo(LCD_u8ROW_01 , LCD_u8COL_00);
							Lcd_vidDisplayNumber(Loc_u8Par1);
#endif
						}
					}
				} else {
					SET_BIT(Loc_u8Flag, SECOND_PARM_PRESSED);
					if (Loc_s8Par2 == ZERO_INIT) {
						Loc_u8Column++;
						Loc_s8Par2 += (LOC_u8Key - '0');
						Lcd_vidDisplayCharacter(LOC_u8Key);

					} else {
						if (!GET_BIT(Loc_u8Flag, PARM2_MAX)) {
							Loc_u8Column++;
							Loc_s8Par2 *= TEN;
							Loc_s8Par2 += (LOC_u8Key - '0');
							Lcd_vidDisplayCharacter(LOC_u8Key);
#ifdef DEBUG
							Lcd_vidGoTo(LCD_u8ROW_01 , LCD_u8COL_00);
							Lcd_vidDisplayNumber(Loc_u8Par2);
#endif
						}
					}
				}
				break;

			}
			_delay_ms(800);

		}
	}
	return 0;
}

