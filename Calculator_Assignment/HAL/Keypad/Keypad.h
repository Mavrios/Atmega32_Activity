
/*
 * Keypad.h
 *
 *  Created on: Mar 19, 2022
 *      Author: Kishk
 */

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

/*ENUM*/
/*ERROR STATUS*/
typedef enum{
	Keypad_Ok,
	Keypad_ErrorNullPointer
}Keypad_tenuErrorStatus;

/*********************************************************** PORTOTYPES **********************************************************************/
/****************************************************************************************************
 * Function:  Keypad_enuKeyPressed																	*
 * ------------------------------------------------------------------------------------------------ *
 * RETURN PRESSED KEY VALUE IF THERE'S NO PRESSED KEY RETURN 0										*
 *                                                                                                  *
 *  Add_pu8PreessedKey: AN ADDRESSED TO STORE PRESSED KEY VALUE ON THIS ADDRESS					    *
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Keypad_tenuErrorStatus ERROR ABOVE.                                                       *
 ****************************************************************************************************/
Keypad_tenuErrorStatus Keypad_enuKeyPressed(pu8 Add_pu8PreessedKey);
#endif /* HAL_KEYPAD_KEYPAD_H_ */
