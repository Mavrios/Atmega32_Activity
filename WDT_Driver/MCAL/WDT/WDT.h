/*
 * WDT.h
 *
 *  Created on: May 6, 2022
 *      Author: Kishk
 */

#ifndef MCAL_WDT_WDT_H_
#define MCAL_WDT_WDT_H_

typedef enum{
	WDT_enuTimedOut_16_3_Ms,
	WDT_enuTimedOut_32_5_Ms,
	WDT_enuTimedOut_65_Ms,
	WDT_enuTimedOut_0_13_Sec,
	WDT_enuTimedOut_0_26_Sec,
	WDT_enuTimedOut_0_52_Sec,
	WDT_enuTimedOut_1_Sec,
	WDT_enuTimedOut_2_1_Sec,
}WDT_tenuSleepConfig;

void WDT_vidSleepMode(WDT_tenuSleepConfig Copy_enuSleepConfig);
void WDT_vidDisable(void);
void WDT_vidRefresh(void);

#endif /* MCAL_WDT_WDT_H_ */
