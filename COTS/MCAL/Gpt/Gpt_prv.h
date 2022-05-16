/*
 * Gpt_prv.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#ifndef MCAL_GPT_GPT_PRV_H_
#define MCAL_GPT_GPT_PRV_H_


#define TCCR0_u8WVG_CLR		((u8) 0xB7)
#define TIMSK0_u8INTRPT_CLR	((u8) 0xFC)
#define TIMSK1_u8INTRPT_CLR	((u8) 0xE3)
#define TIMSK2_u8INTRPT_CLR	((u8) 0x3F)
#define TCCR0_u8PRESCL_CLR	((u8) 0xF8)
#define TCCR1B_u8PRESCL_CLR	((u8) 0xF8)

#define TCCR1A_WGM_CLR_MSK	((u8) 0xFC)
#define TCCR1B_WGM_CLR_MSK	((u8) 0xE7)

#define GPT_u8NUMBERS		((u8) 0x3)
#define TIMER0				0
#define TIMER1				1
#define TIMER2				2


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
#endif /* MCAL_GPT_GPT_PRV_H_ */
