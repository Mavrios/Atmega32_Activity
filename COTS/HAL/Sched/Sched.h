/*
 * Sched.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#ifndef HAL_SCHED_SCHED_H_
#define HAL_SCHED_SCHED_H_
/******************************************** TYPEDEF ********************************************/
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

/********************************************* MACROS *********************************************/
#define SCHED_u8ACTIVE	1
#define SCHED_u8DISABLE	0
/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  Sched_vidInit
 * --------------------
 * INITIALIZE THE SCHED WITH TICK TIME 1 MS
 *
 */
void Sched_vidInit(void);
/*
 * Function:  Sched_enuRegisterTask
 * --------------------
 * REGISTER DESIRED TASKS TO BE CALLED WITH IT'S DESIRED PERIODIC TIME
 *
 * Add_pstrCfg: ADDRESS OF CONFIGIRATION OF THE TASK "ZCOPY"
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Sched_tenuErrorStatus ERROR ENUM.
 */
Sched_tenuErrorStatus Sched_enuRegisterTask(Sched_tstrConfigurations * Add_pstrCfg);
/*
 * Function:  Sched_vidInit
 * --------------------
 * START SCHEDULER
 *
 */
void Sched_vidStart(void);

#endif /* HAL_SCHED_SCHED_H_ */
