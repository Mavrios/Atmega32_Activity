/*
 * Switch.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#ifndef HAL_SWITCH_SWITCH_H_
#define HAL_SWITCH_SWITCH_H_

#include "Switch_cfg.h"


/********************************************* MACROS *********************************************/

#define SWITCH_u8_STATE_PRESSED		((u8) 1)
#define SWITCH_u8_STATE_NOT_PRESSED	((u8) 0)

/******************************************** TYPEDEF ********************************************/
typedef enum{
	Switch_Ok,
	Switch_Nok
}Switch_tenuErrorStatus;

typedef enum{
	Switch_enuNotPressed,
	Switch_enuPressed,
	Switch_enuPreNotPressed,
	Switch_enuPrePressed,
}Switch_tenuStatus;

/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  Switch_readState
 * --------------------
 * READ SWITCH CURRENT STATE
 *
 * Copy_u16SwitchNum: SWITCH NUMBER TO READ IT'S STATE
 * Copy_u8SwitchState: POINTER TO RETURN THE SWITCH STATE.
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Switch_tenuErrorStatus ERROR ENUM.
 */
extern Switch_tenuErrorStatus Switch_readState(u16 Copy_u16SwitchNum , u8 *Copy_u8SwitchState);
/*
 * Function:  Switch_Task
 * --------------------
 * SWITCH TASK TO BE CHECKED EVERY 5MS I.E
 *
 */
extern void Switch_Task(void);
/************************************ EXTERN USED VARIABLES *******************************************/

extern const u8 Switch_u8Pin[Number_of_Switchs];

#endif /* HAL_SWITCH_SWITCH_H_ */
