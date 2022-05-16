/*
 * main.c
 *
 *  Created on: May 6, 2022
 *      Author: Kishk
 */

#include "../../SERVICES/Std_types.h"
#include "../../SERVICES/Bit_utils.h"
#include "../../MCAL/Port/Port.h"
#include "../../MCAL/Pwm_Driver/Pwm.h"
#include "../Oscilloscope/Oscilloscope.h"
int main(void)
{
//	Pwm0_2_tstrCfg Pwm0Init={
//			.Pwm_u8CmpOutputMode = PWM_COMPMODE_CLEAR_OC_MATCH,
//			.Pwm_u8Mode= PWM0_2_MODE_FASTPWM_DEF_TOP,
//			.Pwm_u8Prescaller =Pwm_Div_By_8
//	};
//	Pwm_tstrInit PwmInit={
//			.Pwm_Timer0 = &Pwm0Init,
//			.Pwm_Timer1 = NULL,
//			.Pwm_Timer2 = NULL,
//	};
	Port_vidInit();
//	Pwm_enuSetOCR(PWM_enuOCR0,1);
//	Pwm_enuInit(&PwmInit);
	Oscilloscope_vidInit();
	while(1);
	return 0;
}
