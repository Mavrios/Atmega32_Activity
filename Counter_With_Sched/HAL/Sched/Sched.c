/*
 * Sched.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#include "../../Services/Bit_utils.h"
#include "../../Services/Std_types.h"
#include "Sched.h"
#include "Sched_cfg.h"
#include "Sched_prv.h"
#include "../../MCAL/Gpt/Gpt.h"
#include <avr/io.h>

static Sched_tstrConfigurations * TasksCfg[SCHED_u16NUM_OF_TASKS];

/*
 * Function:  Sched_vidInit
 * --------------------
 * INITIALIZE THE SCHED WITH TICK TIME 1 MS
 *
 */
void Sched_vidInit(void)
{
	/*SET TIMER0 CONFIGRATIONS*/
	Gpt_ChannelCfg TIMER0 = {
			.Prescaller = Timer_Div_By_64,
			.Callbackfn = Sched_vidSchedular
	};
	Gpt_ConfigType Gpt_Cfg = {
			.TIMER0_Cfg = &TIMER0,
			.TIMER1_Cfg = NULL,
			.TIMER2_Cfg = NULL,
	};

	/*INITIALIZE TIMER 0*/
	Gpt_Init(&Gpt_Cfg);
	/*ENABLE NOTIFICATIONS*/
	Gpt_EnableNotification(Gpt_enuTimer0);
	/*ENABLE GLOBAL INTERRUPT*/
	SREG |= (1<<7);
}
/*
 * Function:  Sched_enuRegisterTask
 * --------------------
 * REGISTER DESIRED TASKS TO BE CALLED WITH IT'S DESIRED PERIODIC TIME
 *
 * Add_pstrCfg: ADDRESS OF CONFIGIRATION OF THE TASK "ZCOPY"
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Sched_tenuErrorStatus ERROR ENUM.
 */
Sched_tenuErrorStatus Sched_enuRegisterTask(Sched_tstrConfigurations * Add_pstrCfg)
{
	/*DECLARE ERROR STATUS*/
	Sched_tenuErrorStatus Loc_enuReturnStatus = Sched_enuOk;
	/*VALIDATE THE CFG AND CBF*/
	if(Add_pstrCfg == NULL || Add_pstrCfg->CallbckFcn == NULL)
	{
		/*ASSIGN ERROR*/
		Loc_enuReturnStatus = Sched_enuErrorNullPointer;
	}
	else
	{
		/*CHECK IF THE PERIORITY IS EMPTY AND NUMBER OF TASKS IS VALID*/
		if(TasksCfg[Add_pstrCfg->Periority] != NULL || Add_pstrCfg->Periority >= SCHED_u16NUM_OF_TASKS)
		{
			/*ASSIGN ERROR*/
			Loc_enuReturnStatus = Sched_enuErrorPeriority;
		}
		else
		{
			/*SAVE THE TASK CONFIGURATION TO BE CALLED IN IT'S DESIRED TIME*/
			TasksCfg[Add_pstrCfg->Periority] = Add_pstrCfg;
		}
	}
	return Loc_enuReturnStatus;
}


/*
 * Function:  Sched_vidSchedular
 * --------------------
 * SCHEDULER FUNCTION TO BE CALLED FROM TIMER HANDLER
 *
 */
static void Sched_vidSchedular(void)
{
	/*DECLARE ITERATOR TO BE USED FOR LOOP*/
	u16 Loc_u16Iter;
	/*LOOP IN THE TASKS*/
	for(Loc_u16Iter = 0 ; Loc_u16Iter< SCHED_u16NUM_OF_TASKS ; Loc_u16Iter++)
	{
		/*CHECK IF THE TASK NOT EQUAL NULL*/
		if(TasksCfg[Loc_u16Iter] != NULL)
		{
			/*CHECK THE TASK STATE*/
			if(TasksCfg[Loc_u16Iter]->State == SCHED_u8ACTIVE)
			{
				/*IF THE FIST DELAY EQUAL 0*/
				if(TasksCfg[Loc_u16Iter]->first_delay == 0)
				{
					/*CALL THE TASK*/
					TasksCfg[Loc_u16Iter]->CallbckFcn();
					/*ASSIGN THE FIRST DELAY WITH PERIODIC TIME -1 */
					TasksCfg[Loc_u16Iter]->first_delay = TasksCfg[Loc_u16Iter]->Periodicity - 1;
				}
				else
				{
					/*DECREMENT THE FIRST DELAY*/
					TasksCfg[Loc_u16Iter]->first_delay--;
				}
			}
		}
	}
}

/*
 * Function:  Sched_vidInit
 * --------------------
 * START SCHEDULER
 *
 */
void Sched_vidStart(void)
{
	/*START TIMER WITH 250 TICK --> 1MS*/
	Gpt_StartTimer(Gpt_enuTimer0 , 250);
	/*STUCK IN WHILE LOOP*/
	while(1);
}
