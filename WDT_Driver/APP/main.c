/*
 * main.c
 *
 *  Created on: Apr 6, 2022
 *      Author: Kishk
 */

#include "../Services/Bit_utils.h"
#include "../Services/Std_types.h"
#include <avr/io.h>
#include "../MCAL/Port/Port.h"
#include "../MCAL/Dio/Dio.h"
#include "../MCAL/WDT/WDT.h"
#include "../HAL/Sched/Sched.h"
#include "../HAL/Switch/Switch.h"
#include "../HAL/Ssd/Ssd.h"
#include <util/delay.h>

void IncSSD(void);
void SwitchCheck(void);


Sched_tstrConfigurations SSDTask={
		.first_delay = 1,
		.Periodicity = 1000,
		.State = 1,
		.Periority = 1,
		.CallbckFcn = IncSSD
};

Sched_tstrConfigurations SwitchTask={
		.first_delay = 2,
		.Periodicity = 5,
		.State = 1,
		.Periority = 0,
		.CallbckFcn = Switch_Task
};
Sched_tstrConfigurations SwitchPressedTask={
		.first_delay = 200,
		.Periodicity = 200,
		.State = 1,
		.Periority = 2,
		.CallbckFcn = SwitchCheck
};
Sched_tstrConfigurations WDRTask={
		.first_delay = 2,
		.Periodicity = 500,
		.State = 1,
		.Periority = 3,
		.CallbckFcn = WDT_vidRefresh
};

int main(void)
{


	Port_vidInit();
	Sched_vidInit();
	Sched_enuRegisterTask(&SwitchTask);
	Sched_enuRegisterTask(&SSDTask);
	Sched_enuRegisterTask(&SwitchPressedTask);
	Sched_enuRegisterTask(&WDRTask);
	WDT_vidSleepMode(WDT_enuTimedOut_1_Sec);
	Sched_vidStart();



}
void IncSSD(void)
{
	static u8 Number;
	Ssd_enuDisplayNumber(Number++);
	if(Number == 10)
	{
		Number = 0;
	}
}

void SwitchCheck(void)
{
	u8 Loc_u8SwitchState;
	Switch_readState(Start_Switch , &Loc_u8SwitchState);
	if(Loc_u8SwitchState == 0)
	{
		WDRTask.State = 0;
	}
}
