/*
 * Gpt.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#ifndef MCAL_GPT_GPT_H_
#define MCAL_GPT_GPT_H_

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




#define GPT_u8TIMER0_CTC_MODE				((u8) 0x40)


#define GPT_u8TIMER0_CTC_INTERRUPT			((u8) 0x02)
#define GPT_u8TIMER0_NO_INTERRUPT			((u8) 0x00)

#define GPT_u8TIMER1_NORMAL_MODE			((u8) 0x00)
#define GPT_u8TIMER1_CTC_MODE				((u8) 0x08)

#define GPT_u8TIMER1_CTC_INTERRUPT			((u8) 0x10)
#define GPT_u8TIMER1_NO_INTERRUPT			((u8) 0x00)


#define GPT_u8TIMER2_CTC_MODE			((u8) 0x40)


#define GPT_u8TIMER2_CTC_INTERRUPT			((u8) 0x80)
#define GPT_u8TIMER2_OVF_INTERRUPT			((u8) 0x40)
#define GPT_u8TIMER2_NO_INTERRUPT			((u8) 0x00)




void Gpt_Init(const Gpt_ConfigType * ConfigPtr);


u16 Gpt_GetTimeElapsed(Gpt_ChannelType Copy_u8Channel);
u16 Gpt_GetTimeRemaining(Gpt_ChannelType Copy_u8Channel);

void Gpt_StartTimer(Gpt_ChannelType Copy_u8Channel , u16 Copy_u16Value );
void Gpt_StopTimer(Gpt_ChannelType Copy_u8Channel);
void Gpt_EnableNotification(Gpt_ChannelType Copy_u8Channel);
void Gpt_DisableNotification(Gpt_ChannelType Copy_u8Channel);



#endif /* MCAL_GPT_GPT_H_ */
