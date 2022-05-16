/*
 * Pwm.c
 *
 *  Created on: Apr 16, 2022
 *      Author: Kishk
 */

#include "../../SERVICES/Std_types.h"
#include "../../SERVICES/Bit_utils.h"

#include "Pwm.h"
#include "Pwm_cfg.h"
#include "Pwm_prv.h"
#include <avr/io.h>


extern Pwm_tenuErrorStatus Pwm_enuInit(Pwm_tstrInit * Add_pfCfg)
{
	Pwm_tenuErrorStatus Loc_enuReturnStatus=Pwm_enuOk;
	if(Add_pfCfg == NULL)
	{
		Loc_enuReturnStatus = Pwm_enuErrorNullPointer;
	}
	else
	{
		if(Add_pfCfg->Pwm_Timer0 != NULL)
		{
			TCCR0=0;
			TCCR0|=Add_pfCfg->Pwm_Timer0->Pwm_u8Mode;
			TCCR0|=((Add_pfCfg->Pwm_Timer0->Pwm_u8CmpOutputMode) << 4);
			TCCR0|=Add_pfCfg->Pwm_Timer0->Pwm_u8Prescaller;
		}
		if(Add_pfCfg->Pwm_Timer1 != NULL)
		{
			TCCR1A=0;
			TCCR1B=0;
//			TCCR1A|=Add_pfCfg->Pwm_Timer0->Pwm_u8Mode;
			TCCR1A|=GET_BIT(Add_pfCfg->Pwm_Timer1->Pwm_u8Mode , 0);
			TCCR1A|=(GET_BIT(Add_pfCfg->Pwm_Timer1->Pwm_u8Mode , 1)<<1);
			TCCR1B|=(GET_BIT(Add_pfCfg->Pwm_Timer1->Pwm_u8Mode , 2)<<3);
			TCCR1B|=(GET_BIT(Add_pfCfg->Pwm_Timer1->Pwm_u8Mode , 3)<<4);
			TCCR1A|=((Add_pfCfg->Pwm_Timer1->Pwm_u8CmpOutputModeChA) << 6);
			TCCR1A|=((Add_pfCfg->Pwm_Timer1->Pwm_u8CmpOutputModeChB) << 4);
			TCCR1B|=Add_pfCfg->Pwm_Timer1->Pwm_u8Prescaller;
		}
		if(Add_pfCfg->Pwm_Timer2 != NULL)
		{
			TCCR2=0;
			TCCR2|=Add_pfCfg->Pwm_Timer2->Pwm_u8Mode;
			TCCR2|=((Add_pfCfg->Pwm_Timer2->Pwm_u8CmpOutputMode) << 4);
			TCCR2|=Add_pfCfg->Pwm_Timer2->Pwm_u8Prescaller;
		}
	}

	return Loc_enuReturnStatus;
}


extern Pwm_tenuErrorStatus Pwm_enuSetOCR(Pwm_tenuOCR_Channel Copy_enuOcrChannel , u16 Copy_u16Value)
{
	Pwm_tenuErrorStatus Loc_enuReturnStatus = Pwm_enuOk;
	if(Copy_enuOcrChannel > PWM_enuOCR2)
	{
		Loc_enuReturnStatus = Pwm_enuErrorOCRChannel;
	}
	else
	{
		switch(Copy_enuOcrChannel)
		{
		case PWM_enuOCR0:
			OCR0 = (u8) Copy_u16Value;
			break;
		case PWM_enuOCR1A:
			OCR1A = Copy_u16Value;
			break;
		case PWM_enuOCR1B:
			OCR1B = Copy_u16Value;
			break;
		case PWM_enuOCR2:
			OCR2 = (u8) Copy_u16Value;
			break;
		}
	}
	return Loc_enuReturnStatus;

}
extern void Pwm_enuSetICR(u16 Copy_u16Value)
{
	ICR1  = Copy_u16Value;
}

