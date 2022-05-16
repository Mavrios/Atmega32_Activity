/*
 * Ssd.h
 *
 *  Created on: Mar 21, 2022
 *      Author: Kishk
 */

#ifndef HAL_SSD_SSD_H_
#define HAL_SSD_SSD_H_

#define SSD_u8ONE		1
#define SSD_u8TWO		2
#define SSD_u8THREE		3
#define SSD_u8FOUR		4

#define SSD_u8COMMON_CATHOD		0
#define SSD_u8COMMON_ANODE		1



typedef enum{
	Ssd_enuOk,
	Ssd_enuNumOutOfRange,
	Ssd_enuNullPointer
}Ssd_tenuErrorStatus;
/*********************************************************** PORTOTYPES **********************************************************************/
/****************************************************************************************************
 * Function:  Ssd_enuDisplayNumber																	*
 * ------------------------------------------------------------------------------------------------ *
 * DISPLAY NUMBER IN THE SEVEN SEGMENTS		                                                        *
 *                                                                                                  *
 *  Copy_u16Number: DESIRED NUMBER TO BE PRINTED IN THE SEVEN SEGMENTS DISPLAY						*
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Dio_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
Ssd_tenuErrorStatus Ssd_enuDisplayNumber(u16 Copy_u16Number);
/****************************************************************************************************
 * Function:  Ssd_enuDisableSsd																		*
 * ------------------------------------------------------------------------------------------------ *
 * DISABLE SSD UNTIL WRITE ANTHER NUMBER 		                                                    *
 *                                                                                                  *
 *  Copy_u8SsdNumber: DESIRED SSD TO BE DISABLED													*
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Dio_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
Ssd_tenuErrorStatus Ssd_enuDisableSsd(u8 Copy_u8SsdNumber);

#endif /* HAL_SSD_SSD_H_ */
