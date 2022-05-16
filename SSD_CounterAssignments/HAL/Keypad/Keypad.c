/*
 * Keypad.c
 *
 *  Created on: Mar 19, 2022
 *      Author: Kishk
 */

#include "../../Services/Std_types.h"
#include "../../Services/Bit_utils.h"

#include "../../MCAL/Dio/Dio.h"

#include "Keypad.h"
#include "Keypad_cfg.h"
#include "Keypad_prv.h"


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
Keypad_tenuErrorStatus Keypad_enuKeyPressed(pu8 Add_pu8PreessedKey) {
	/*DEFINE VARIABLES*/
	/*DEFINE ERROR STATUS WITH OK*/
	Keypad_tenuErrorStatus Loc_enuReturnStatus = Keypad_Ok;
	/*ITERATOR FOR ROW*/
	u8 Loc_u8RowIterator = INITZERO;
	/*ITERATOR FOR COL*/
	u8 Loc_u8ColIterator = INITZERO;
	/*PIN STATUS VARIABLE TO READ PINS*/
	u8 Loc_u8PinStatus = DIO_u8HIGH;
	/*ARRAY OF COLS PINS*/
	u8 Loc_u8ArrCol[KEYPAD_u8COLS] = { KEYPAD_u8COL0_PIN, KEYPAD_u8COL1_PIN,
			KEYPAD_u8COL2_PIN, KEYPAD_u8COL3_PIN };
	*Add_pu8PreessedKey = INITZERO;
	/*CHECK IF THE PASSED ADDRESS IS NULL*/
	if (Add_pu8PreessedKey == NULL) {
		/*ASSIGN NULL POINTER ERROR TO RETURN STATUS*/
		Loc_enuReturnStatus = Keypad_ErrorNullPointer;
	} else {
		/*LOOP TO ITERATE INTO ROWS */
		for (Loc_u8RowIterator = INITZERO; Loc_u8RowIterator < KEYPAD_u8ROWS;
				Loc_u8RowIterator++) {
			/*SET PATTERN ON THE CURRENT ROW*/
			vidSetRowPattern(Loc_u8RowIterator);
			/*LOOP TO ITERATE INTO COLUMNS AND STOP IF THE PIN STATUS WAS ZERO OR FINISHING ITERATION*/
			for (Loc_u8ColIterator = INITZERO; Loc_u8ColIterator < KEYPAD_u8COLS && Loc_u8PinStatus ;Loc_u8ColIterator++) {
				/*READ EACH COLUMNS*/
				Dio_enuReadChannel(Loc_u8ArrCol[Loc_u8ColIterator],&Loc_u8PinStatus);
			}
			/*IF THE PIN STATUS WAS LOW*/
			if(Loc_u8PinStatus == DIO_u8LOW)
			{
				/*RETURN THE ROW AND COL VALUE DEPENDS ON ARRAY*/
				*Add_pu8PreessedKey = KeypadOutput[(Loc_u8RowIterator * KEYPAD_u8ROWS) + Loc_u8ColIterator - 1];
				/*BREAK OF THE LOOP*/
				break;
			}
		}
	}

	return Loc_enuReturnStatus;
}

/****************************************************************************************************
 * Function:  vidSetRowPattern																		*
 * ------------------------------------------------------------------------------------------------ *
 * PRIVATE FUNCTION TO APPLY BUTTON PATTERNS														*
 *                                                                                                  *
 *  Copy_u8Row: ROW NUMBER TO APPLY THE PATTERN INTO											    *
 *																									*
 *                                                                                                  *                                                    *
 ****************************************************************************************************/
static void vidSetRowPattern(u8 Copy_u8Row) {
	/*DEFINE ITERATOR FOR ROWS*/
	u8 Loc_u8RowIterator = INITZERO;
	/*LOCAL ARRAY TO HAVE ROWS PINS*/
	u8 Loc_u8ArrRow[KEYPAD_u8ROWS] = { KEYPAD_u8ROW0_PIN, KEYPAD_u8ROW1_PIN,KEYPAD_u8ROW2_PIN, KEYPAD_u8ROW3_PIN };
	/*LOOP TO SET ALL PINS WITH HIGH STATE*/
	for (Loc_u8RowIterator = INITZERO; Loc_u8RowIterator < KEYPAD_u8ROWS ;Loc_u8RowIterator++) {
		Dio_enuWriteChannel(Loc_u8ArrRow[Loc_u8RowIterator] , DIO_u8HIGH);
	}
	/*SET DESIRED ROW WITH LOW*/
	Dio_enuWriteChannel(Loc_u8ArrRow[Copy_u8Row] , DIO_u8LOW);

}
