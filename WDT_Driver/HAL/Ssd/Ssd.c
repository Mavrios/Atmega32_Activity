/*
 * Ssd.c
 *
 *  Created on: Mar 21, 2022
 *      Author: Kishk
 */

#include "../../Services/Std_types.h"
#include "../../Services/Bit_utils.h"
#include "../../MCAL/Dio/Dio.h"
#include <util/delay.h>
#include "Ssd.h"
#include "Ssd_cfg.h"
#include "Ssd_prv.h"

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
Ssd_tenuErrorStatus Ssd_enuDisplayNumber(u16 Copy_u16Number) {
	/*DEFINE RETURN ERROR VARIABLE*/
	Ssd_tenuErrorStatus Loc_enuReturnStatus = Ssd_enuOk;
	/*DEFINE ITERATOR FOR LOOP USING*/
	u8 Loc_u8Iterator = SSD_u8INITZERO;
	/*DEFINE SSD0 PINS IN ARRAY */
	const u8 Loc_u8Ssd0Pins[] = { SSD0_u8PINA, SSD0_u8PINB, SSD0_u8PINC,
			SSD0_u8PIND, SSD0_u8PINE, SSD0_u8PINF, SSD0_u8PING };
	/*STORE THE FIRST DIGIT OF THE PASSED ARGUMENT TO VARIABLE */
	u8 Loc_u8FirstDigit	= (Copy_u16Number % 10);

	/*CHECK IF THE CONFIGURATION USING TWO OR MORE SSD*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8TWO || SSD_u8NUMBER_OF_SDD == SSD_u8THREE || SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
	/*DEFINE SSD1 PINS IN ARRAY */
	const u8 Loc_u8Ssd1Pins[] = { SSD1_u8PINA, SSD1_u8PINB, SSD1_u8PINC,
			SSD1_u8PIND, SSD1_u8PINE, SSD1_u8PINF, SSD1_u8PING };
	/*STORE THE SECOND DIGIT OF THE PASSED ARGUMENT TO VARIABLE */
	u8 Loc_u8SecondDigit	= (Copy_u16Number / 10) % 10;
	#endif
	/*CHECK IF THE CONFIGURATION USING THREE OR MORE SSD*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8THREE || SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
	/*DEFINE SSD2 PINS IN ARRAY */
	u8 Loc_u8Ssd2Pins[] = { SSD2_u8PINA, SSD2_u8PINB, SSD2_u8PINC,
			SSD2_u8PIND, SSD2_u8PINE, SSD2_u8PINF, SSD2_u8PING };
	/*STORE THE SECOND DIGIT OF THE PASSED ARGUMENT TO VARIABLE */
	u8 Loc_u8ThirdDigit	= (Copy_u16Number / SSD_u8HUNDRED) % SSD_u8TEN;

	#endif
	/*CHECK IF THE CONFIGURATION USING FOUR OR MORE SSD*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
	/*DEFINE SSD3 PINS IN ARRAY */
	u8 Loc_u8Ssd3Pins[] = { SSD3_u8PINA, SSD3_u8PINB, SSD3_u8PINC,
			SSD3_u8PIND, SSD3_u8PINE, SSD3_u8PINF, SSD3_u8PING };
	u8 Loc_u8FourthDigit	= (Copy_u16Number / SSD_u8THOUSEND) % SSD_u8TEN;

	#endif
	/*CHECK IF THE CONFIGURATION ONE SSD*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8ONE
	/*CHECK IF THE NUMBER OUT OF THE RANGE*/
	if(Copy_u16Number > SSD_u8ONE_SSD_MAXIMUM_NUMBER)
#endif
	/*CHECK IF THE CONFIGURATION TWO SSD*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8TWO
	/*CHECK IF THE NUMBER OUT OF THE RANGE*/
	if(Copy_u16Number > SSD_u8TWO_SSD_MAXIMUM_NUMBER)
#endif
	/*CHECK IF THE CONFIGURATION THREE SSD*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8THREE
	/*CHECK IF THE NUMBER OUT OF THE RANGE*/
	if(Copy_u16Number > SSD_u8THREE_SSD_MAXIMUM_NUMBER)
#endif
	/*CHECK IF THE CONFIGURATION FOUR SSD*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
	/*CHECK IF THE NUMBER OUT OF THE RANGE*/
	if(Copy_u16Number > SSD_u8FOUR_SSD_MAXIMUM_NUMBER)
#endif
	{
		/*STORE ERROR OUT OF THE RANGE*/
		Loc_enuReturnStatus = Ssd_enuNumOutOfRange;
	}
	else
	{
		/*LOOP TO SET CONFIGURATION IN EVERY SSD PIN*/
		for (Loc_u8Iterator = SSD_u8INITZERO; Loc_u8Iterator < SSD_u8NUMBER_OF_PINS; Loc_u8Iterator++)
		{
			/*CHECK IF THE SSD IS COMMON CATHOD*/
#if	SSD_u8COMMON == SSD_u8COMMON_CATHOD
			/*APPLY WRITE CHANNEL IN EACH PIN IN SSD0*/
			Dio_enuWriteChannel(Loc_u8Ssd0Pins[Loc_u8Iterator] , GET_BIT(Ssd_u8NumbersPattern[Loc_u8FirstDigit] , Loc_u8Iterator));
/*CHECK IF THE SSD CONFUGRATION IS TWO SSD OR MORE*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8TWO || SSD_u8NUMBER_OF_SDD == SSD_u8THREE || SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
			/*APPLY WRITE CHANNEL IN EACH PIN IN SSD1*/
			Dio_enuWriteChannel(Loc_u8Ssd1Pins[Loc_u8Iterator] , GET_BIT(Ssd_u8NumbersPattern[Loc_u8SecondDigit] , Loc_u8Iterator));
#endif
	/*CHECK IF THE SSD CONFUGRATION IS THREE SSD OR MORE*/
#if  SSD_u8NUMBER_OF_SDD == SSD_u8THREE || SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
			/*APPLY WRITE CHANNEL IN EACH PIN IN SSD2*/
			Dio_enuWriteChannel(Loc_u8Ssd2Pins[Loc_u8Iterator] , GET_BIT(Ssd_u8NumbersPattern[Loc_u8ThirdDigit] , Loc_u8Iterator));
#endif
	/*CHECK IF THE SSD CONFUGRATION IS FOUR SSD*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
			/*APPLY WRITE CHANNEL IN EACH PIN IN SSD3*/
			Dio_enuWriteChannel(Loc_u8Ssd3Pins[Loc_u8Iterator],	GET_BIT(Ssd_u8NumbersPattern[Loc_u8FourthDigit],Loc_u8Iterator));
#endif
			/*CHECK IF THE SSD IS COMMON ANODE*/
#elif SSD_u8COMMON == SSD_u8COMMON_ANODE
			/*APPLY WRITE CHANNEL IN EACH PIN IN SSD0*/
			Dio_enuWriteChannel(Loc_u8Ssd0Pins[Loc_u8Iterator] , !GET_BIT(Ssd_u8NumbersPattern[*(u8 *) Copy_pvNumber] , Loc_u8Iterator));
			/*CHECK IF THE SSD CONFUGRATION IS TWO SSD OR MORE*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8TWO || SSD_u8NUMBER_OF_SDD == SSD_u8THREE || SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
			/*APPLY WRITE CHANNEL IN EACH PIN IN SSD1*/
			Dio_enuWriteChannel(Loc_u8Ssd1Pins[Loc_u8Iterator] , !GET_BIT(Ssd_u8NumbersPattern[Loc_u8SecondDigit] , Loc_u8Iterator));
#endif
			/*CHECK IF THE SSD CONFUGRATION IS THREE SSD OR MORE*/
#if  SSD_u8NUMBER_OF_SDD == SSD_u8THREE || SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
			/*APPLY WRITE CHANNEL IN EACH PIN IN SSD2*/
			Dio_enuWriteChannel(Loc_u8Ssd2Pins[Loc_u8Iterator] , !GET_BIT(Ssd_u8NumbersPattern[Loc_u8ThirdDigit] , Loc_u8Iterator));
#endif
			/*CHECK IF THE SSD CONFUGRATION IS FOUR SSD OR MORE*/
#if SSD_u8NUMBER_OF_SDD == SSD_u8FOUR
			/*APPLY WRITE CHANNEL IN EACH PIN IN SSD3*/
			Dio_enuWriteChannel(Loc_u8Ssd3Pins[Loc_u8Iterator],	!GET_BIT(Ssd_u8NumbersPattern[Loc_u8FourthDigit],Loc_u8Iterator));
#endif
#endif
		}
	}

	/*RETURN AN ERROR STATUS*/
	return Loc_enuReturnStatus;
}



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
Ssd_tenuErrorStatus Ssd_enuDisableSsd(u8 Copy_u8SsdNumber)
{
	/*DEFINE RETURN ERROR VARIABLE*/
	Ssd_tenuErrorStatus Loc_enuReturnStatus = Ssd_enuOk;
	/*SWITCH CASE ON THE SSD NUMBER*/
	switch(Copy_u8SsdNumber)
	{
	case SSD_u8ONE:
		SSD_DisableSSD0();
		break;
	case SSD_u8TWO:
		SSD_DisableSSD1();
		break;
	case SSD_u8THREE:
		SSD_DisableSSD2();
		break;
	case SSD_u8FOUR:
		SSD_DisableSSD3();
		break;
	default:
		Loc_enuReturnStatus = Ssd_enuNumOutOfRange;
	}
	return Loc_enuReturnStatus;
}
