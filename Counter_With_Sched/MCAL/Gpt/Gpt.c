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

/*
 * Function:  Gpt_Init
 * --------------------
 * INITIALIZE GENRAL PURPUSS TIMERS 0 , 1 , 2
 *
 * ConfigPtr: CONFIGURATION OF TIMER0 , TIMER1, TIMER2 "ZCOPY"
 *
 */
void Gpt_Init(const Gpt_ConfigType * ConfigPtr) {
	/*CHECK IF THE CFG IS VALID*/
	if (ConfigPtr != NULL) {
		/*SAVE THE CFG TO BE USED*/
		Gpt_Save_Cfg = (Gpt_ConfigType *) ConfigPtr;
		/*CFG TIMER0*/
		if (ConfigPtr->TIMER0_Cfg) {
			/*SET WAVEGENERATION AS CTC AND DISABLE INTERRUPTS*/
			TCCR0 &= TCCR0_u8WVG_CLR;
			TCCR0 |= GPT_u8TIMER0_CTC_MODE;
			TIMSK &= TIMSK0_u8INTRPT_CLR;
			/*SAVE CBF TO BE USED AS NOTIFICATION*/
			if (ConfigPtr->TIMER0_Cfg->Callbackfn) {
				Gpt_CallbackFcn[TIMER0] = ConfigPtr->TIMER0_Cfg->Callbackfn;
			}
		}
		/*CFG TIMER1*/
		if (ConfigPtr->TIMER1_Cfg) {
			/*SET WAVEGENERATION AS CTC AND DISABLE INTERRUPTS*/
			TCCR1A &= TCCR1A_WGM_CLR_MSK;
			TCCR1B &= TCCR1B_WGM_CLR_MSK;
			TCCR1B |= GPT_u8TIMER1_CTC_MODE;
			TIMSK &= TIMSK1_u8INTRPT_CLR;
			/*SAVE CBF TO BE USED AS NOTIFICATION*/
			if (ConfigPtr->TIMER1_Cfg->Callbackfn) {
				Gpt_CallbackFcn[TIMER1] = ConfigPtr->TIMER1_Cfg->Callbackfn;
			}
		}
		/*CFG TIMER2*/
		if (ConfigPtr->TIMER2_Cfg) {
			/*SET WAVEGENERATION AS CTC AND DISABLE INTERRUPTS*/
			TCCR2 &= TCCR0_u8WVG_CLR;
			TCCR0 |= GPT_u8TIMER2_CTC_MODE;
			TIMSK &= TIMSK2_u8INTRPT_CLR;
			/*SAVE CBF TO BE USED AS NOTIFICATION*/
			if (ConfigPtr->TIMER2_Cfg->Callbackfn) {
				Gpt_CallbackFcn[TIMER2] = ConfigPtr->TIMER2_Cfg->Callbackfn;
			}
		}
	}
}

/*
 * Function:  Gpt_GetTimeElapsed
 * --------------------
 * GET THE ELAPSED TIME
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 * return: ELAPSED TIME
 */
u16 Gpt_GetTimeElapsed(u8 Copy_u8Channel) {
	/*DELCARE VARIABLE TO BE USED IN RETURN */
	u16 Loc_u16ElapsedTime;
	/*CHECK THE CHANNEL*/
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
	/*RETURN THE ELAPSED TIME*/
	return Loc_u16ElapsedTime;
}
/*
 * Function:  Gpt_GetTimeRemaining
 * --------------------
 * GET THE REMAINING TIME TO REACH THE DESIRED VALUE
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 * return: REMAINING TIME
 */
u16 Gpt_GetTimeRemaining(u8 Copy_u8Channel) {
	/*DELCARE VARIABLE TO BE USED IN RETURN */
	u16 Loc_u16RemainingTime = 0;
	/*CHECK THE CHANNEL*/
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
	/*RETURN THE ELAPSED TIME*/
	return Loc_u16RemainingTime;
}

/*
 * Function:  Gpt_StartTimer
 * --------------------
 * START TIMER FOR COUNTING
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 * Copy_u16Value: DESIRED VALUE TO REACH
 *
 */
void Gpt_StartTimer(u8 Copy_u8Channel, u16 Copy_u16Value) {
	/*CHECK THE CHANNEL*/
	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		/*VALIDATE THE VALUE*/
		if (Copy_u16Value <= 0xFF) {
			/*SET THE VALUE*/
			OCR0 = Copy_u16Value;
			/*START THE TIMER*/
			if (Gpt_Save_Cfg != NULL && Gpt_Save_Cfg->TIMER0_Cfg != NULL) {
				TCCR0 &= TCCR0_u8PRESCL_CLR;
				TCCR0 |= Gpt_Save_Cfg->TIMER0_Cfg->Prescaller;
			}
		}
		break;
	case Gpt_enuTimer1:
		/*SET THE VALUE*/
		OCR1A = Copy_u16Value;
		/*START THE TIMER*/
		if (Gpt_Save_Cfg != NULL && Gpt_Save_Cfg->TIMER1_Cfg != NULL) {
			TCCR1B &= TCCR1B_u8PRESCL_CLR;
			TCCR1B |= Gpt_Save_Cfg->TIMER1_Cfg->Prescaller;
		}
		break;
	case Gpt_enuTimer2:
		/*VALIDATE THE VALUE*/
		if (Copy_u16Value <= 0xFF) {
			/*SET THE VALUE*/
			OCR2 = Copy_u16Value;
			/*START THE TIMER*/
			if (Gpt_Save_Cfg != NULL && Gpt_Save_Cfg->TIMER2_Cfg != NULL) {
				TCCR2 &= TCCR0_u8PRESCL_CLR;
				TCCR2 |= Gpt_Save_Cfg->TIMER0_Cfg->Prescaller;
			}
		}
		break;
	}

}

/*
 * Function:  Gpt_StopTimer
 * --------------------
 * STOP TIMER COUNTING
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 */

void Gpt_StopTimer(u8 Copy_u8Channel) {
	/*CHECK THE CHANNEL*/
	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		/*STOP THE TIMER*/
		TCCR0 &= TCCR0_u8PRESCL_CLR;
		break;
	case Gpt_enuTimer1:
		/*STOP THE TIMER*/
		TCCR1B &= TCCR1B_u8PRESCL_CLR;

		break;
	case Gpt_enuTimer2:
		/*STOP THE TIMER*/
		TCCR2 &= TCCR0_u8PRESCL_CLR;
		break;

	}
}
/*
 * Function:  Gpt_EnableNotification
 * --------------------
 * ENABLE INTERRUPT WHEN REACH DESIRED VALUE
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 */
void Gpt_EnableNotification(u8 Copy_u8Channel)
{
	/*CHECK THE CHANNEL*/
	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		/*ENABLE THE INTERRUPT*/
		TIMSK &= TIMSK0_u8INTRPT_CLR;
		TIMSK |= GPT_u8TIMER0_CTC_INTERRUPT;
		break;
	case Gpt_enuTimer1:
		/*ENABLE THE INTERRUPT*/
		TIMSK &= TIMSK1_u8INTRPT_CLR;
		TIMSK |= GPT_u8TIMER1_CTC_INTERRUPT;
		break;
	case Gpt_enuTimer2:
		/*ENABLE THE INTERRUPT*/
		TIMSK &= TIMSK2_u8INTRPT_CLR;
		TIMSK |= GPT_u8TIMER2_CTC_INTERRUPT;
		break;

	}
}

/*
 * Function:  Gpt_EnableNotification
 * --------------------
 * DISABLE INTERRUPT WHEN REACH DESIRED VALUE
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 */
void Gpt_DisableNotification(Gpt_ChannelType Copy_u8Channel)
{
	/*CHECK THE CHANNEL*/
	switch (Copy_u8Channel) {
	case Gpt_enuTimer0:
		/*DISABLE THE INTERRUPT*/
		TIMSK &= TIMSK0_u8INTRPT_CLR;
		break;
	case Gpt_enuTimer1:
		/*DISABLE THE INTERRUPT*/
		TIMSK &= TIMSK1_u8INTRPT_CLR;
		break;
	case Gpt_enuTimer2:
		/*DISABLE THE INTERRUPT*/
		TIMSK &= TIMSK2_u8INTRPT_CLR;
		break;

	}
}


/****************************************************************************   ISR   ***********************************************************************************/
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

