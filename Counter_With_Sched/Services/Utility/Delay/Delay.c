/*
 * Delay.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#ifndef SERVICES_UTILITY_DELAY_DELAY_C_
#define SERVICES_UTILITY_DELAY_DELAY_C_

#include "../../Std_types.h"
#include "../../Bit_utils.h"
#include "Delay.h"
#include "Delay_cfg.h"
#include "Delay_prv.h"

void Delay_vidDelaymsBL(f64 Copy_f64DelayMs)
{
	u16 Loc_u16Ticks;
	f64 Loc_f64Temp = ((F_CLOCK) / 24e3) * Copy_f64DelayMs;
	if (Loc_f64Temp < 1.0)
		Loc_u16Ticks = 1;
	else if (Loc_f64Temp > 65535)
	{
		//	__ticks = requested delay in 1/10 ms
		Loc_u16Ticks = (u16) (Copy_f64DelayMs * 10.0);
		while(Loc_u16Ticks)
		{
			// wait 1/10 ms
			vidBusyLoop(((F_CLOCK) / 24e3) / 10 );
			Loc_u16Ticks --;
		}
		return;
	}
	else
	{
		Loc_u16Ticks = (u16)Loc_f64Temp;
	}
	vidBusyLoop(Loc_u16Ticks);

}

static void vidBusyLoop(u16 Copy_u16Tick){

	for(u16 Iterator = 0 ; Iterator < Copy_u16Tick ; Iterator++)
	{
		asm("NOP");
	}
}

#endif /* SERVICES_UTILITY_DELAY_DELAY_C_ */
