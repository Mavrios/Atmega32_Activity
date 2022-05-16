/*
 * Oscilloscope_prv.h
 *
 *  Created on: May 7, 2022
 *      Author: Kishk
 */

#ifndef APP_OSCILLOSCOPE_OSCILLOSCOPE_PRV_H_
#define APP_OSCILLOSCOPE_OSCILLOSCOPE_PRV_H_




typedef enum{
	OSC_enuStart,
	OSC_enuF1,
	OSC_enuEND,
}OSC_tenuStates;



#define OSC_S_T_NS				((u32) 16000000)

#define OSC_MHZ					((u32) 1000000)
#define OSC_KHZ					((u32) 1000)

#endif /* APP_OSCILLOSCOPE_OSCILLOSCOPE_PRV_H_ */
