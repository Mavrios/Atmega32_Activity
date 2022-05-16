/*
 * Servo.h
 *
 *  Created on: Apr 17, 2022
 *      Author: Kishk
 */

#ifndef HAL_SERVO_SERVO_H_
#define HAL_SERVO_SERVO_H_

/*********************************************************** TYPEDEF **********************************************************************/

typedef enum{
	Servo_ChA=1,
	Servo_ChB,
}Servo_tenuChannel;

/*********************************************************** MACROS **********************************************************************/

#define SERVO_u8ENABLE		1
#define SERVO_u8DISABLE		0


/*********************************************************** PORTOTYPES **********************************************************************/
/****************************************************************************************************
 * Function:  Servo_vidInit																			*
 * ------------------------------------------------------------------------------------------------ *
 * SERVO INITIALIZATION FUNCTION			                                                        *
 *                                                                                                  *
 *  returns: void							                                                        *
 ****************************************************************************************************/
void Servo_vidInit(void);
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
void Servo_vidSetAngle(Servo_tenuChannel Copy_u8Channel,s8 Copy_s8Angle);
#endif /* HAL_SERVO_SERVO_H_ */