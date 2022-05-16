/*
 * ICU.c
 *
 *  Created on: May 6, 2022
 *      Author: Kishk
 */

#include "../../SERVICES/Std_types.h"
#include "../../SERVICES/Bit_utils.h"
#include "../../SERVICES/Atmega32_Registers.h"
#include "../../MCAL/ICU/ICU.h"
#include "../../MCAL/ICU/ICU_cfg.h"
#include "../../MCAL/ICU/ICU_prv.h"

ICU_Cbf ICU_pfCbfSave;
ICU_Cbf Ovf_pfCbfSave;

void __vector_6(void) __attribute__((signal,used));
void __vector_9(void) __attribute__((signal,used));

ICU_tenuErrorStatus ICU_enuInitStart(ICU_tstrConfig * Add_pstrConfigurations) {
	ICU_tenuErrorStatus Loc_enuReturnStatus = ICU_enuOk;
	if (Add_pstrConfigurations == NULL) {
		Loc_enuReturnStatus = ICU_enuNullPointer;
	} else {
		TCCR1B = 0;
		TCCR1B = Add_pstrConfigurations->ICU_u8NoiseCanceler
				| Add_pstrConfigurations->ICU_u8EdgeSelect;
		TIMSK &= ~(ICU_u8INTERRUPT_ON);
		TIMSK |= (Add_pstrConfigurations->ICU_u8InterruptCtrl);
		SET_BIT(TIMSK,TOIE1);
		ICU_pfCbfSave = Add_pstrConfigurations->ICU_pfCbf;
		Ovf_pfCbfSave = Add_pstrConfigurations->OVF_pfCbf;
		ICR1=0;
		TCCR1B = Add_pstrConfigurations->ICU_u8Prescaller;
	}

	return Loc_enuReturnStatus;
}

void ICU_vidStop(void) {
	TCCR1B &= ICU_u8CLK_CLR;
	TIMSK &= ~(ICU_u8INTERRUPT_ON);
	CLR_BIT(TIMSK,TOIE1);
	TCNT1=0;
	ICR1=0;
}

u16 ICU_u16ReadICR(void) {
	return ICR1;
}

void __vector_6(void)
{
	if(ICU_pfCbfSave)
	{
		ICU_pfCbfSave();
	}
	CLR_BIT(TIFR,ICF1);
}
void __vector_9(void)
{
	if(Ovf_pfCbfSave)
	{
		Ovf_pfCbfSave();
	}
	CLR_BIT(TIFR,TOV1);
}
