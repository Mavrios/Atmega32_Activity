/*
 * ICU.h
 *
 *  Created on: May 6, 2022
 *      Author: Kishk
 */

#ifndef MCAL_ICU_ICU_H_
#define MCAL_ICU_ICU_H_

typedef void (* ICU_Cbf) (void);
typedef enum{
	ICU_enuOk,
	ICU_enuNullPointer
}ICU_tenuErrorStatus;

typedef enum{
	ICU_Stopped,
	ICU_Div_By_1,
	ICU_Div_By_8,
	ICU_Div_By_64,
	ICU_Div_By_256,
	ICU_Div_By_1024,
	ICU_Div_By_Ext_FE,
	ICU_Div_By_Ext_RE,
}ICU_tenuPrescaller;

typedef struct{
	u8 ICU_u8NoiseCanceler;
	u8 ICU_u8EdgeSelect;
	u8 ICU_u8InterruptCtrl;
	ICU_tenuPrescaller ICU_u8Prescaller;
	ICU_Cbf ICU_pfCbf;
	ICU_Cbf OVF_pfCbf;
}ICU_tstrConfig;

#define ICU_u8NOISE_CANCELER_N_ACT			0x00
#define ICU_u8NOISE_CANCELER_ACT			0x80

#define ICU_u8FALLING_EDGE					0x00
#define ICU_u8RISING_EDGE					0x40

#define ICU_u8INTERRUPT_ON					0x20
#define ICU_u8INTERRUPT_OFF					0x00

ICU_tenuErrorStatus ICU_enuInitStart(ICU_tstrConfig * Add_pstrConfigurations);

void ICU_vidStop(void);

u16 ICU_u16ReadICR(void);


#endif /* MCAL_ICU_ICU_H_ */
