/*
 * WDT.c
 *
 *  Created on: May 6, 2022
 *      Author: Kishk
 */

#include "../../SERVICES/Std_types.h"
#include "../../SERVICES/Bit_utils.h"
#include "../../SERVICES/Atmega32_Registers.h"
#include "../../MCAL/WDT/WDT.h"
#include "../../MCAL/WDT/WDT_cfg.h"
#include "../../MCAL/WDT/WDT_prv.h"

void WDT_vidSleepMode(WDT_tenuSleepConfig Copy_enuSleepConfig)
{
	/*RESET WDT CONFIGURATIONS*/
	WDTCR |= WDT_u8CTRL_WDTCR;
	WDTCR = 0;
	WDTCR = (Copy_enuSleepConfig | (WDT_u8WDTCR_WDE));

}
void WDT_vidDisable(void)
{
	/*RESET WDT CONFIGURATIONS*/
	WDTCR |= WDT_u8CTRL_WDTCR;
	WDTCR = 0;
}
void WDT_vidRefresh(void)
{
	asm("WDR");
}
