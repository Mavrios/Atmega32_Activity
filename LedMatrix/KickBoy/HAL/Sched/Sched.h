/*
 * Sched.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#ifndef HAL_SCHED_SCHED_H_
#define HAL_SCHED_SCHED_H_

typedef void (* SchedCbf) (void);

typedef struct{
	u16 first_delay;
	u16 Periodicity;
	u8	State;
	u16 Periority;
	SchedCbf	CallbckFcn;
}Sched_tstrConfigurations;

typedef enum{
	Sched_enuOk,
	Sched_enuErrorNullPointer,
	Sched_enuErrorPeriority,
}Sched_tenuErrorStatus;

#define SCHED_u8ACTIVE	1
#define SCHED_u8DISABLE	0

void Sched_vidInit(void);
Sched_tenuErrorStatus Sched_enuRegisterTask(Sched_tstrConfigurations * Add_pstrCfg);
void Sched_vidStart(void);

#endif /* HAL_SCHED_SCHED_H_ */
