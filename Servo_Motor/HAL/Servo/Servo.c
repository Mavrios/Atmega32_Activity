/*
 * Servo.c
 *
 *  Created on: Apr 17, 2022
 *      Author: Kishk
 */


#include "../../SERVICES/Std_types.h"
#include "../../SERVICES/Bit_utils.h"
#include "../../SERVICES/Utility/Map/Map.h"
#include "../../MCAL/Pwm_Driver/Pwm.h"

#include "Servo.h"
#include "Servo_cfg.h"
#include "Servo_prv.h"


/****************************************************************************************************
 * Function:  Servo_vidInit																			*
 * ------------------------------------------------------------------------------------------------ *
 * SERVO INITIALIZATION FUNCTION			                                                        *
 *                                                                                                  *
 *  returns: void							                                                        *
 ****************************************************************************************************/
void Servo_vidInit(void)
{
	/*DECALE TIMER1 CONFIGURATION TO USE THE PWM*/
	Pwm1_tstrCfg Loc_strPwm1Cfg={
			/*SET PWM FAST MODE WITH TOP VALUE ICR1*/
			.Pwm_u8Mode =PWM1_ModeFastPwm_TopICR1,
			/*CHECK IF THE CHANNEL A IS ACTIVE*/
#if SERVO_u8CHANNEL_A == SERVO_u8ENABLE
			/*SET THE MODE CLEAR ON COMPARE MATCH*/
			.Pwm_u8CmpOutputModeChA = PWM_COMPMODE_CLEAR_OC_MATCH,
#endif
	/*CHECK IF THE CHANNEL A IS ACTIVE*/
#if SERVO_u8CHANNEL_B == SERVO_u8ENABLE
			/*SET THE MODE CLEAR ON COMPARE MATCH*/
			.Pwm_u8CmpOutputModeChB = PWM_COMPMODE_CLEAR_OC_MATCH,
#endif
			/*SET THE PRESCALLER*/
			.Pwm_u8Prescaller = Pwm_Div_By_8,
	};
	/*DEFINE PWM INIT STRUCT*/
	Pwm_tstrInit Loc_strPwmInit={
			.Pwm_Timer0 = NULL,
			.Pwm_Timer1 = &Loc_strPwm1Cfg,
			.Pwm_Timer2 = NULL,

	};
	/*INIT PWM*/
	Pwm_enuInit(&Loc_strPwmInit);
	/*SET ICR TOP VALUE*/
	Pwm_enuSetICR(ICR_VAL);

}
/****************************************************************************************************
 * Function:  Servo_vidSetAngle																		*
 * ------------------------------------------------------------------------------------------------ *
 * SET DESIRED ANGLE TO THE SERVO MOTOR		                                                        *
 * 																									*
 * Copy_u8Channel: SELECT THE SERVO CHANNEL															*
 * Copy_s8Angle  : SET DESIRED ANGLE FROM RANGE -90 -> +90											*
 *                                                                                                  *
 *  returns: void							                                                        *
 ****************************************************************************************************/
void Servo_vidSetAngle(u8 Copy_u8Channel,s8 Copy_s8Angle)
{
	/*CALCULATE THE REQUIRED VALUE TO GET DESIRED ANGLE*/
	s32 Loc_s32EncodedAngle = Map(Copy_s8Angle , SERVO_s8MIN_ANGLE , SERVO_s8MAX_ANGLE , SERVO_u16MIN_OCR1_VAL , SERVO_u16MAX_OCR1_VAL);
	if(Copy_s8Angle >= SERVO_s8MIN_ANGLE && Copy_s8Angle <= SERVO_s8MAX_ANGLE )
	{
		/*APPLY THE PWM TO GET DESIRED ANGLE*/
		Pwm_enuSetOCR(Copy_u8Channel,Loc_s32EncodedAngle);
	}
}

