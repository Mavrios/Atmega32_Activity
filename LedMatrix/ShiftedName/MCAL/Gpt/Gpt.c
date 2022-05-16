/*
 * Gpt.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#include "../../Services/Std_types.h"
#include "../../Services/Bit_utils.h"
#include "Gpt.h"
#include "Gpt_cfg.h"
#include "Gpt_prv.h"
#include <avr/io.h>

void __vector_4(void) __attribute__((signal));
void __vector_5(void) __attribute__((signal));

void __vector_7(void) __attribute__((signal));
void __vector_8(void) __attribute__((signal));
void __vector_9(void) __attribute__((signal));
void __vector_10(void) __attribute__((signal));
void __vector_11(void) __attribute__((signal));

static Gpt_Cbf Gpt_CallbackFcn[GPT_u8NUMBERS];
static Gpt_ConfigType * Gpt_Save_Cfg;

void Gpt_Init(const Gpt_ConfigType * ConfigPtr) {
	if (ConfigPtr != NULL) {
		Gpt_Save_Cfg = (Gpt_ConfigType *) ConfigPtr;
		if (ConfigPtr->TIMER0_Cfg) {
			TCCR0 &= TCCR0_u8WVG_CLR;
			TCCR0 |= GPT_u8TIMER0_CTC_MODE;
			TIMSK &= TIMSK0_u8INTRPT_CLR;
			if (ConfigPtr->TIMER0_Cfg->Callbackfn) {
				Gpt_CallbackFcn[TIMER0] = ConfigPtr->TIMER0_Cfg->Callbackfn;
			}
		}
		if (ConfigPtr->TIMER1_Cfg) {
			TCCR1A &= TCCR1A_WGM_CLR_MSK;
			TCCR1B &= TCCR1B_WGM_CLR_MSK;

			TCCR1B |= GPT_u8TIMER1_CTC_MODE;
			TIMSK &= TIMSK1_u8INTRPT_CLR;
			if (ConfigPtr->TIMER1_Cfg->Callbackfn) {
				Gpt_CallbackFcn[TIMER1] = ConfigPtr->TIMER1_Cfg->Callbackfn;
			}
		}
		if (ConfigPtr->TIMER2_Cfg) {
			TCCR2 &= TCCR0_u8WVG_CLR;
			TCCR0 |= GPT_u8TIMER2_CTC_MODE;
			TIMSK &= TIMSK2_u8INTRPT_CLR;
			if (ConfigPtr->TIMER2_Cfg->Callbackfn) {
				Gpt_CallbackFcn[TIMER2] = ConfigPtr->TIMER2_Cfg->Callbackfn;
			}
		}
	}
}

u16 Gpt_GetTimeElapsed(u8 Copy_u8Channel) {
	u16 Loc_u16ElapsedTime = 0;
	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		Loc_u16ElapsedTime = TCNT0;
		break;
	case Gpt_enuTimer1:
		Loc_u16ElapsedTime = TCNT1;
		break;
	case Gpt_enuTimer2:
		Loc_u16ElapsedTime = TCNT2;
		break;
	}
	return Loc_u16ElapsedTime;
}

u16 Gpt_GetTimeRemaining(u8 Copy_u8Channel) {
	u16 Loc_u16RemainingTime = 0;
	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		Loc_u16RemainingTime = OCR0 - TCNT0;
		break;
	case Gpt_enuTimer1:
		Loc_u16RemainingTime = OCR1A - TCNT1;
		break;
	case Gpt_enuTimer2:
		Loc_u16RemainingTime = OCR2 - TCNT2;
		break;
	}
	return Loc_u16RemainingTime;
}

void Gpt_StartTimer(u8 Copy_u8Channel, u16 Copy_u16Value) {
	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		if (Copy_u16Value <= 0xFF) {
			OCR0 = Copy_u16Value;
			if (Gpt_Save_Cfg != NULL && Gpt_Save_Cfg->TIMER0_Cfg != NULL) {
				TCCR0 &= TCCR0_u8PRESCL_CLR;
				TCCR0 |= Gpt_Save_Cfg->TIMER0_Cfg->Prescaller;
			}
		}
		break;
	case Gpt_enuTimer1:
		OCR1A = Copy_u16Value;
		if (Gpt_Save_Cfg != NULL && Gpt_Save_Cfg->TIMER1_Cfg != NULL) {
			TCCR1B &= TCCR1B_u8PRESCL_CLR;
			TCCR1B |= Gpt_Save_Cfg->TIMER1_Cfg->Prescaller;
		}
		break;
	case Gpt_enuTimer2:
		if (Copy_u16Value <= 0xFF) {
			OCR2 = Copy_u16Value;
			if (Gpt_Save_Cfg != NULL && Gpt_Save_Cfg->TIMER2_Cfg != NULL) {
				TCCR2 &= TCCR0_u8PRESCL_CLR;
				TCCR2 |= Gpt_Save_Cfg->TIMER0_Cfg->Prescaller;
			}
		}
		break;
	}

}

void Gpt_StopTimer(u8 Copy_u8Channel) {

	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		TCCR0 &= TCCR0_u8PRESCL_CLR;
		break;
	case Gpt_enuTimer1:

		TCCR1B &= TCCR1B_u8PRESCL_CLR;

		break;
	case Gpt_enuTimer2:

		TCCR2 &= TCCR0_u8PRESCL_CLR;
		break;

	}
}

void Gpt_EnableNotification(u8 Copy_u8Channel)
{

	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		TIMSK &= TIMSK0_u8INTRPT_CLR;
		TIMSK |= GPT_u8TIMER0_CTC_INTERRUPT;
		break;
	case Gpt_enuTimer1:
		TIMSK &= TIMSK1_u8INTRPT_CLR;
		TIMSK |= GPT_u8TIMER1_CTC_INTERRUPT;
		break;
	case Gpt_enuTimer2:
		TIMSK &= TIMSK2_u8INTRPT_CLR;
		TIMSK |= GPT_u8TIMER2_CTC_INTERRUPT;
		break;

	}
}


void Gpt_DisableNotification(Gpt_ChannelType Copy_u8Channel)
{

	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		TIMSK &= TIMSK0_u8INTRPT_CLR;
		break;
	case Gpt_enuTimer1:
		TIMSK &= TIMSK1_u8INTRPT_CLR;
		break;
	case Gpt_enuTimer2:
		TIMSK &= TIMSK2_u8INTRPT_CLR;
		break;

	}
}



void __vector_4(void) {
	if (Gpt_CallbackFcn[TIMER2]) {
		Gpt_CallbackFcn[TIMER2]();
	}
}

void __vector_5(void) {
	if (Gpt_CallbackFcn[TIMER2]) {
		Gpt_CallbackFcn[TIMER2]();
	}
}

void __vector_7(void) {
	if (Gpt_CallbackFcn[TIMER1]) {
		Gpt_CallbackFcn[TIMER1]();
	}
}

void __vector_8(void) {
	if (Gpt_CallbackFcn[TIMER1]) {
		Gpt_CallbackFcn[TIMER1]();
	}
}

void __vector_9(void) {
	if (Gpt_CallbackFcn[TIMER1]) {
		Gpt_CallbackFcn[TIMER1]();
	}
}

void __vector_10(void) {
	if (Gpt_CallbackFcn[TIMER0]) {
		Gpt_CallbackFcn[TIMER0]();
	}
}

void __vector_11(void) {
	if (Gpt_CallbackFcn[TIMER0]) {
		Gpt_CallbackFcn[TIMER0]();
	}
}

