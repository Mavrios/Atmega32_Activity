/*
 * Gpt.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#ifndef MCAL_GPT_GPT_H_
#define MCAL_GPT_GPT_H_
/******************************************** TYPEDEF ********************************************/
typedef void (*Gpt_Cbf) (void);


typedef enum{
	Timer_Stopped,
	Timer_Div_By_1,
	Timer_Div_By_8,
	Timer_Div_By_64,
	Timer_Div_By_256,
	Timer_Div_By_1024,
	Timer_Div_By_Ext_FE,
	Timer_Div_By_Ext_RE,
}Timer_tenuPrescaller;

typedef enum{
	Gpt_enuTimer0,
	Gpt_enuTimer1,
	Gpt_enuTimer2,
}Gpt_ChannelType;

typedef struct{
	Timer_tenuPrescaller Prescaller;
	Gpt_Cbf Callbackfn;
}Gpt_ChannelCfg;

typedef struct{
	Gpt_ChannelCfg *TIMER0_Cfg;
	Gpt_ChannelCfg *TIMER1_Cfg;
	Gpt_ChannelCfg *TIMER2_Cfg;
}Gpt_ConfigType;





/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  Gpt_Init
 * --------------------
 * INITIALIZE GENRAL PURPUSS TIMERS 0 , 1 , 2
 *
 * ConfigPtr: CONFIGURATION OF TIMER0 , TIMER1, TIMER2 "ZCOPY"
 *
 */
void Gpt_Init(const Gpt_ConfigType * ConfigPtr);

/*
 * Function:  Gpt_GetTimeElapsed
 * --------------------
 * GET THE ELAPSED TIME
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 * return: ELAPSED TIME
 */
u16 Gpt_GetTimeElapsed(Gpt_ChannelType Copy_u8Channel);
/*
 * Function:  Gpt_GetTimeRemaining
 * --------------------
 * GET THE REMAINING TIME TO REACH THE DESIRED VALUE
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 * return: REMAINING TIME
 */
u16 Gpt_GetTimeRemaining(Gpt_ChannelType Copy_u8Channel);

/*
 * Function:  Gpt_StartTimer
 * --------------------
 * START TIMER FOR COUNTING
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 * Copy_u16Value: DESIRED VALUE TO REACH
 *
 */
void Gpt_StartTimer(Gpt_ChannelType Copy_u8Channel , u16 Copy_u16Value );
/*
 * Function:  Gpt_StopTimer
 * --------------------
 * STOP TIMER COUNTING
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 */

void Gpt_StopTimer(Gpt_ChannelType Copy_u8Channel);
/*
 * Function:  Gpt_EnableNotification
 * --------------------
 * ENABLE INTERRUPT WHEN REACH DESIRED VALUE
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 */
void Gpt_EnableNotification(Gpt_ChannelType Copy_u8Channel);
/*
 * Function:  Gpt_EnableNotification
 * --------------------
 * DISABLE INTERRUPT WHEN REACH DESIRED VALUE
 *
 * Copy_u8Channel: DESIRED CHANNEL FROM ENUM Gpt_ChannelType
 *
 */
void Gpt_DisableNotification(Gpt_ChannelType Copy_u8Channel);



#endif /* MCAL_GPT_GPT_H_ */
