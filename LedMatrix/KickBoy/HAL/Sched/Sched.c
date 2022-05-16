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

void Sched_vidInit(void)
{
	Gpt_ChannelCfg TIMER0 = {
			.Prescaller = Timer_Div_By_64,
			.Callbackfn = Sched_vidSchedular
	};
	Gpt_ConfigType Gpt_Cfg = {
			.TIMER0_Cfg = &TIMER0,
			.TIMER1_Cfg = NULL,
			.TIMER2_Cfg = NULL,
	};

	Gpt_Init(&Gpt_Cfg);
	Gpt_EnableNotification(Gpt_enuTimer0);
	SREG |= (1<<7);
}

Sched_tenuErrorStatus Sched_enuRegisterTask(Sched_tstrConfigurations * Add_pstrCfg)
{
	Sched_tenuErrorStatus Loc_enuReturnStatus = Sched_enuOk;
	if(Add_pstrCfg == NULL || Add_pstrCfg->CallbckFcn == NULL)
	{
		Loc_enuReturnStatus = Sched_enuErrorNullPointer;
	}
	else
	{
		if(TasksCfg[Add_pstrCfg->Periority] != NULL || Add_pstrCfg->Periority >= SCHED_u16NUM_OF_TASKS)
		{
			Loc_enuReturnStatus = Sched_enuErrorPeriority;
		}
		else
		{
			TasksCfg[Add_pstrCfg->Periority] = Add_pstrCfg;
		}
	}
	return Loc_enuReturnStatus;
}

static void Sched_vidSchedular(void)
{
	u16 Loc_u16Iter;
	for(Loc_u16Iter = 0 ; Loc_u16Iter< SCHED_u16NUM_OF_TASKS ; Loc_u16Iter++)
	{
		if(TasksCfg[Loc_u16Iter] != NULL)
		{
			if(TasksCfg[Loc_u16Iter]->State == SCHED_u8ACTIVE)
			{
				if(TasksCfg[Loc_u16Iter]->first_delay == 0)
				{
					TasksCfg[Loc_u16Iter]->CallbckFcn();
					TasksCfg[Loc_u16Iter]->first_delay = TasksCfg[Loc_u16Iter]->Periodicity - 1;
				}
				else
				{
					TasksCfg[Loc_u16Iter]->first_delay--;
				}
			}
		}
	}
}


void Sched_vidStart(void)
{
	Gpt_StartTimer(Gpt_enuTimer0 , 250);
	while(1);
}
