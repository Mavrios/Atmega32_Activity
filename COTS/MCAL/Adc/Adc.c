/*
 * Adc.c
 *
 *  Created on: Mar 25, 2022
 *      Author: Kishk
 */

#include "../../Services/Std_types.h"
#include "../../Services/Bit_utils.h"
#include <avr/io.h>
#include "Adc.h"
#include "Adc_cfg.h"
#include "Adc_prv.h"

static Adc_CallBack_t CallBack = NULL;
void __vector_16(void) __attribute__ ((signal)) ;

/****************************************************************************************************
 * Function:  Adc_vidInit																			*
 * ------------------------------------------------------------------------------------------------ *
 * INITIALIZE THE ADC 						                                                        *
 *                                                                                                  *
 ****************************************************************************************************/
extern void Adc_vidInit(void) {
	/*CONFIGURE ADC REFERENCE*/
#if ADC_u8REFERENCE_SELECTION == ADC_u8REF_SELC_AREF
#define ADC_ADMUX_BIT7 			0
#define ADC_ADMUX_BIT6 			0
#elif ADC_u8REFERENCE_SELECTION == ADC_u8REF_SELC_AVCC
#define ADC_ADMUX_BIT7 			0
#define ADC_ADMUX_BIT6 			1
#elif ADC_u8REFERENCE_SELECTION == ADC_u8REF_SELC_256MV
#define ADC_ADMUX_BIT7 			1
#define ADC_ADMUX_BIT6 			1
#else
#error "ERROR REFRENECE SELCETION!!"
#endif

	/*CONFIGURE ADJUSTMENT*/
#if ADC_u8ADJUSTMENT_RESULT > ADC_u8AJUSTMENT_LEFT
#error "ERROR ADJUSTMENT SELCETION!!"
#else
#define ADC_ADMUX_BIT5 			ADC_u8ADJUSTMENT_RESULT
#endif

	/*LET ADMUX CONFIGURE IN RUNTIME*/
#define ADC_ADMUX_BIT4 			0
#define ADC_ADMUX_BIT3 			0
#define ADC_ADMUX_BIT2 			0
#define ADC_ADMUX_BIT1 			0
#define ADC_ADMUX_BIT0 			0

#define ADC_ADCSRA_BIT7			1
#define ADC_ADCSRA_BIT6 		0
	/*CONFIGURE THE AUTO-TRIGGER OPTION*/
#if ADC_u8AUTO_TRIGGER > ADC_u8AUTO_TRIG_ENABLE
#error "ERROR AUTO TRIGGER SELCETION!!"
#else
#define ADC_ADCSRA_BIT5			ADC_u8AUTO_TRIGGER
#endif

#define ADC_ADCSRA_BIT4			0
	/*CONFIGURE THE INTERRUPT OPTION*/
#if ADC_u8INTERRUPT > ADC_u8INTERRUPT_DISABLE
#error "ERROR ADJUSTMENT SELCETION!!"
#else
#define ADC_ADCSRA_BIT3 			ADC_u8INTERRUPT
#endif

	/*CONFIGURE THE PRESCALLER OPTIONS*/
#if ADC_u8PRESCALLER == ADC_u8PRESCALLER_DIV_BY_2
#define ADC_ADCSRA_BIT0				1
#define ADC_ADCSRA_BIT1				0
#define ADC_ADCSRA_BIT2				0

#elif ADC_u8PRESCALLER == ADC_u8PRESCALLER_DIV_BY_4
#define ADC_ADCSRA_BIT0				0
#define ADC_ADCSRA_BIT1				1
#define ADC_ADCSRA_BIT2				0

#elif ADC_u8PRESCALLER == ADC_u8PRESCALLER_DIV_BY_8
#define ADC_ADCSRA_BIT0				1
#define ADC_ADCSRA_BIT1				1
#define ADC_ADCSRA_BIT2				0

#elif ADC_u8PRESCALLER == ADC_u8PRESCALLER_DIV_BY_16
#define ADC_ADCSRA_BIT0				0
#define ADC_ADCSRA_BIT1				0
#define ADC_ADCSRA_BIT2				1

#elif ADC_u8PRESCALLER == ADC_u8PRESCALLER_DIV_BY_32
#define ADC_ADCSRA_BIT0				1
#define ADC_ADCSRA_BIT1				0
#define ADC_ADCSRA_BIT2				1

#elif ADC_u8PRESCALLER == ADC_u8PRESCALLER_DIV_BY_64
#define ADC_ADCSRA_BIT0				0
#define ADC_ADCSRA_BIT1				1
#define ADC_ADCSRA_BIT2				1

#elif ADC_u8PRESCALLER == ADC_u8PRESCALLER_DIV_BY_128
#define ADC_ADCSRA_BIT0				1
#define ADC_ADCSRA_BIT1				1
#define ADC_ADCSRA_BIT2				1
#endif

	/*ASSIGN CONFIGURATION INTO THE ADC REGISTERS*/
	ADMUX = CONC(ADC_ADMUX_BIT7, ADC_ADMUX_BIT6, ADC_ADMUX_BIT5, ADC_ADMUX_BIT4,
			ADC_ADMUX_BIT3, ADC_ADMUX_BIT2, ADC_ADMUX_BIT1, ADC_ADMUX_BIT0);
	ADCSRA = CONC(ADC_ADCSRA_BIT7, ADC_ADCSRA_BIT6, ADC_ADCSRA_BIT5,
			ADC_ADCSRA_BIT4, ADC_ADCSRA_BIT3, ADC_ADCSRA_BIT2, ADC_ADCSRA_BIT1,
			ADC_ADCSRA_BIT0);
}
/****************************************************************************************************
 * Function:  Adc_enuStartConversion																*
 * ------------------------------------------------------------------------------------------------ *
 * ADC START CONVERSION						                                                        *
 *                                                                                                  *
 *  Copy_u8Channel: DESIRED CHANNEL															        *
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Adc_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
extern Adc_tenuErrorStatus Adc_enuStartConversion(u8 Copy_u8Channel) {
	/*DEFINE RETURN STATUS VARIABLE*/
	Adc_tenuErrorStatus Loc_enuReturnStatus = ADC_enuOk;
	/*VALIDATE CHANNEL*/
	if (Copy_u8Channel > ADC_AnalogGND) {
		/*ASSIGN ERROR*/
		Loc_enuReturnStatus = ADC_enuErrorChannel;
	} else {
		/*START CONVERSION*/
		SET_BIT(ADCSRA, ADSC);
	}
	return Loc_enuReturnStatus;
}

extern Adc_tenuErrorStatus Adc_enuAnalogRead(u8 Copy_u8Channel,
		u16 * Add_pu16AnalogResult) {
	/*DEFINE RETURN STATUS VARIABLE*/
	Adc_tenuErrorStatus Loc_enuReturnStatus = ADC_enuOk;
	/*DEFINE VARIABLE TO MAKE TIMEOUT*/
	u16 Loc_u16TimedOut = TIME_OUT;
	/*VALIDATE THE CHANNEL*/
	if (Copy_u8Channel > ADC_AnalogGND) {
		Loc_enuReturnStatus = ADC_enuErrorChannel;
		/*VALIDATE THE POINTER*/
	} else if (Add_pu16AnalogResult == NULL) {
		Loc_enuReturnStatus = ADC_enuErrorNullPointer;
	} else {
		/*START THE CONVERSION*/
		SET_BIT(ADCSRA, ADSC);
		Loc_enuReturnStatus = ADC_enuErrorTimedOut;
		/*KEEP LOOPING UNTIL TIMEOUT OR THE FLAG BEEN RAISED*/
		while (Loc_u16TimedOut-- && GET_BIT(ADCSRA , ADIF) == 0)
			;
		/*RECHECK THE FLAG*/
		if (GET_BIT(ADCSRA , ADIF) == 1) {
			Loc_enuReturnStatus = ADC_enuOk;
			SET_BIT(ADCSRA, ADIF);
#if ADC_u8ADJUSTMENT_RESULT == ADC_u8AJUSTMENT_LEFT
			*Add_pu16AnalogResult = (ADCH<<2) | (ADCL);
#elif ADC_u8ADJUSTMENT_RESULT == ADC_u8AJUSTMENT_RIGHT
			*Add_pu16AnalogResult = (ADCL | (ADCH << 8));
#endif

		}

	}
	return Loc_enuReturnStatus;
}


/****************************************************************************************************
 * Function:  Adc_enuSetCallback																	*
 * ------------------------------------------------------------------------------------------------ *
 * SET CALL-BACK FUNCTION TO BE USED IN INTERRUPT                                                   *
 *                                                                                                  *
 *  Add_pfCallBack: ADDRESS OF THE FUNCTION													        *
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Adc_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
extern Adc_tenuErrorStatus Adc_enuSetCallback(Adc_CallBack_t Add_pfCallBack)
{
	/*DEFINE RETURN STATUS VARIABLE*/
	Adc_tenuErrorStatus Loc_enuReturnStatus = ADC_enuOk;
	/*VALIDATE THE POINTER*/
	if(Add_pfCallBack == NULL)
	{
		/*ASSIGN THE ERROR*/
		Loc_enuReturnStatus = ADC_enuErrorNullPointer;
	}
	else
	{
		/*ASSIGN THE ADDRESS OF CALLBACK FUNCTION INTO GLOBAL VARIABLE*/
		CallBack = Add_pfCallBack;
	}
	/*RETURN ERROR STATUS*/
	return Loc_enuReturnStatus;
}


/*ISR*/
void __vector_16(void)
{
	if(CallBack)
	{
		CallBack();
	}
}
