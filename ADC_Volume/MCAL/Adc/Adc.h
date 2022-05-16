/*
 * Adc.h
 *
 *  Created on: Mar 25, 2022
 *      Author: Kishk
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_


#define ADC_u8REF_SELC_AREF			        (0)
#define ADC_u8REF_SELC_AVCC			        (1)
#define ADC_u8REF_SELC_256MV		        (2)


#define ADC_u8AJUSTMENT_RIGHT		         0
#define ADC_u8AJUSTMENT_LEFT		         1


#define ADC_u8INTERRUPT_DISABLE				 0
#define ADC_u8INTERRUPT_ENABLE				 1

#define ADC_u8AUTO_TRIG_DISABLE				 0
#define ADC_u8AUTO_TRIG_ENABLE				 1


#define ADC_u8PRESCALLER_DIV_BY_2			(1)
#define ADC_u8PRESCALLER_DIV_BY_4			(2)
#define ADC_u8PRESCALLER_DIV_BY_8			(3)
#define ADC_u8PRESCALLER_DIV_BY_16			(4)
#define ADC_u8PRESCALLER_DIV_BY_32			(5)
#define ADC_u8PRESCALLER_DIV_BY_64			(6)
#define ADC_u8PRESCALLER_DIV_BY_128			(7)

#define ADC_u8TRIG_SRC_FREE_RUNNING_MODE	((u8) 0)
#define ADC_u8TRIG_SRC_ANALOG_COMPARATOR	((u8) 1)
#define ADC_u8TRIG_SRC_EXTERNAL_IRQ0		((u8) 2)
#define ADC_u8TRIG_SRC_TIMER0_CMPRMATCH		((u8) 3)
#define ADC_u8TRIG_SRC_TIMER0_OVRFLW		((u8) 4)
#define ADC_u8TRIG_SRC_TIMER_CMPRMATCHB		((u8) 5)
#define ADC_u8TRIG_SRC_TIMER1_OVRFLW		((u8) 6)
#define ADC_u8TRIG_SRC_TIMER1_CAPEVENT		((u8) 7)




typedef enum{
	ADC_AnalogChannelAdc0,
	ADC_AnalogChannelAdc1,
	ADC_AnalogChannelAdc2,
	ADC_AnalogChannelAdc3,
	ADC_AnalogChannelAdc4,
	ADC_AnalogChannelAdc5,
	ADC_AnalogChannelAdc6,
	ADC_AnalogChannelAdc7,
	ADC_AnalogChannelAdc0Adc0Gainx10,
	ADC_AnalogChannelAdc1Adc0Gainx10,
	ADC_AnalogChannelAdc0Adc0Gainx200,
	ADC_AnalogChannelAdc1Adc0Gainx200,
	ADC_AnalogChannelAdc2Adc2Gainx10,
	ADC_AnalogChannelAdc3Adc2Gainx10,
	ADC_AnalogChannelAdc2Adc2Gainx200,
	ADC_AnalogChannelAdc3Adc2Gainx200,
	ADC_AnalogChannelAdc0Adc1Gainx1,
	ADC_AnalogChannelAdc1Adc1Gainx1,
	ADC_AnalogChannelAdc2Adc1Gainx1,
	ADC_AnalogChannelAdc3Adc1Gainx1,
	ADC_AnalogChannelAdc4Adc1Gainx1,
	ADC_AnalogChannelAdc5Adc1Gainx1,
	ADC_AnalogChannelAdc6Adc1Gainx1,
	ADC_AnalogChannelAdc7Adc1Gainx1,
	ADC_AnalogChannelAdc0Adc2Gainx1,
	ADC_AnalogChannelAdc1Adc2Gainx1,
	ADC_AnalogChannelAdc2Adc2Gainx1,
	ADC_AnalogChannelAdc3Adc2Gainx1,
	ADC_AnalogChannelAdc4Adc2Gainx1,
	ADC_AnalogChannelAdc5Adc2Gainx1,
	ADC_AnalogVBG,
	ADC_AnalogGND,
}ADC_tenuAnalogChannel;

typedef enum{
	ADC_enuOk,
	ADC_enuErrorChannel,
	ADC_enuErrorNullPointer,
	ADC_enuErrorTimedOut,
}Adc_tenuErrorStatus;


typedef void (* Adc_CallBack_t) (void);

/*********************************************************** PORTOTYPES **********************************************************************/
/****************************************************************************************************
 * Function:  Adc_vidInit																			*
 * ------------------------------------------------------------------------------------------------ *
 * INITIALIZE THE ADC 						                                                        *
 *                                                                                                  *
 ****************************************************************************************************/
extern void Adc_vidInit(void);
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
extern Adc_tenuErrorStatus Adc_enuStartConversion(u8 Copy_u8Channel);
/****************************************************************************************************
 * Function:  Adc_enuAnalogRead																		*
 * ------------------------------------------------------------------------------------------------ *
 * READ FROM SPECIFIC CHANNEL				                                                        *
 *                                                                                                  *
 *  Copy_u8Channel: DESIRED CHANNEL															        *
 *	Add_pu16AnalogResult: ADDRESS TO VARIABLE TO STORE THE RESULT									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Adc_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
extern Adc_tenuErrorStatus Adc_enuAnalogRead(u8 Copy_u8Channel , u16 * Add_pu16AnalogResult);

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
extern Adc_tenuErrorStatus Adc_enuSetCallback(Adc_CallBack_t Add_pfCallBack);


#endif /* MCAL_ADC_ADC_H_ */
