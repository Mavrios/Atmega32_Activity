/*
 * Switch.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#include "../../Services/Std_types.h"
#include "../../Services/Bit_utils.h"
#include "../../MCAL/Dio/Dio.h"
#include "Switch.h"
#include "Switch_cfg.h"
#include "Switch_prv.h"



/*
 * Function:  Switch_readState
 * --------------------
 * READ SWITCH CURRENT STATE
 *
 * Copy_u16SwitchNum: SWITCH NUMBER TO READ IT'S STATE
 * Copy_u8SwitchState: POINTER TO RETURN THE SWITCH STATE.
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Switch_tenuErrorStatus ERROR ENUM.
 */


extern Switch_tenuErrorStatus Switch_readState(u16 Copy_u16SwitchNum , u8 *Copy_u8SwitchState)
{
	/*DEFINE ERROR STATUS FOR RETURN*/
	Switch_tenuErrorStatus Loc_enuReturnStatus = Switch_Ok;
	if(Copy_u16SwitchNum >= Number_of_Switchs)
	{
		Loc_enuReturnStatus = Switch_Nok;
	}
	else
	{
		*Copy_u8SwitchState = ButtonStatus[Copy_u16SwitchNum];
	}
	return Loc_enuReturnStatus;
}

/*
 * Function:  Switch_Task
 * --------------------
 * SWITCH TASK TO BE CHECKED EVERY 5MS I.E
 *
 */


extern void Switch_Task(void)
{
	/*DECLARE GPIO CNFG STRUCT*/
	/*DECLARE VARIABLE TO STORE THE PIN VALUE*/
	u16 Loc_u16Iterator = ZERO;
	u8 Loc_u8CurButtonStatus	= ZERO;
	static u8  Loc_u8PrevButtonStatus[Number_of_Switchs];
	static u8 Counter[Number_of_Switchs];
	for(Loc_u16Iterator = ZERO ; Loc_u16Iterator< Number_of_Switchs ; Loc_u16Iterator++)
	{
		/*READ PIN VALUE*/
		Dio_enuReadChannel(Switch_u8Pin[Loc_u16Iterator] , &Loc_u8CurButtonStatus);
		if(Loc_u8CurButtonStatus == Loc_u8PrevButtonStatus[Loc_u16Iterator])
		{
			Counter[Loc_u16Iterator]++;
		}
		else
		{
			Counter[Loc_u16Iterator]=ZERO;
		}

		if(Counter[Loc_u16Iterator] == NUM_OF_CHECK)
		{
			Counter[Loc_u16Iterator] = 0;
			ButtonStatus[Loc_u16Iterator] = (u8) Loc_u8CurButtonStatus;
		}
		Loc_u8PrevButtonStatus[Loc_u16Iterator] = (u8) Loc_u8CurButtonStatus;
	}
}
