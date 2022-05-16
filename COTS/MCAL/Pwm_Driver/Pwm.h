/*
 * Pwm.h
 *
 *  Created on: Apr 16, 2022
 *      Author: Kishk
 */

#ifndef MCAL_PWM_DRIVER_PWM_H_
#define MCAL_PWM_DRIVER_PWM_H_


typedef struct
{
	u8 Pwm_u8Mode;
	u8 Pwm_u8CmpOutputMode;
	u8 Pwm_u8Prescaller;
}Pwm0_2_tstrCfg;
typedef struct
{
	u8 Pwm_u8Mode;
	u8 Pwm_u8CmpOutputModeChA;
	u8 Pwm_u8CmpOutputModeChB;
	u8 Pwm_u8Prescaller;
}Pwm1_tstrCfg;


typedef struct{
	Pwm0_2_tstrCfg 	* Pwm_Timer0;
	Pwm1_tstrCfg 	* Pwm_Timer1;
	Pwm0_2_tstrCfg 	* Pwm_Timer2;
}Pwm_tstrInit;

typedef enum{
	Pwm_Stopped,
	Pwm_Div_By_1,
	Pwm_Div_By_8,
	Pwm_Div_By_64,
	Pwm_Div_By_256,
	Pwm_Div_By_1024,
	Pwm_Div_By_Ext_FE,
	Pwm_Div_By_Ext_RE,
}Pwm_tenuPrescaller;

typedef enum{
	PWM1_ModePhaseCorrect_8Bit=1,
	PWM1_ModePhaseCorrect_9Bit,
	PWM1_ModePhaseCorrect_10Bit,
	PWM1_ModeFastPwm_8Bit = 5,
	PWM1_ModeFastPwm_9Bit,
	PWM1_ModeFastPwm_10Bit,
	PWM1_ModePwmPhaseAndFreqCorrect_TopICR1,
	PWM1_ModePwmPhaseAndFreqCorrect_TopOCR1A,
	PWM1_ModePwmPhaseCorrect_TopICR1,
	PWM1_ModePwmPhaseCorrect_TopOCR1A,
	PWM1_ModeFastPwm_TopICR1=14,
	PWM1_ModeFastPwm_TopOCR1A,
}Pwm1_tenuMode_Cfg_t;

typedef enum{
	Pwm_enuOk,
	Pwm_enuErrorNullPointer,
	Pwm_enuErrorOCRChannel,
}Pwm_tenuErrorStatus;


typedef enum{
	PWM_enuOCR0,
	PWM_enuOCR1A,
	PWM_enuOCR1B,
	PWM_enuOCR2,
}Pwm_tenuOCR_Channel;

#define PWM0_2_MODE_PHASECORRET_DEF_TOP			((u8) 0x08)
#define PWM0_2_MODE_FASTPWM_DEF_TOP				((u8) 0x48)


#define PWM_COMPMODE_CLEAR_OC_MATCH				((u8) 0x02)
#define PWM_COMPMODE_SET_OC_MATCH				((u8) 0x03)


extern Pwm_tenuErrorStatus Pwm_enuInit(Pwm_tstrInit * Add_pfCfg);
extern Pwm_tenuErrorStatus Pwm_enuSetOCR(Pwm_tenuOCR_Channel Copy_enuOcrChannel , u16 Copy_u16Value);
extern void Pwm_enuSetICR(u16 Copy_u16Value);

#endif /* MCAL_PWM_DRIVER_PWM_H_ */
