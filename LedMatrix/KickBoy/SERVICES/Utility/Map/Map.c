/*
 * Map.c
 *
 *  Created on: Apr 17, 2022
 *      Author: Kishk
 */

#include "../../Std_types.h"
#include "Map.h"


s32 Map (s32 Copy_s32Val, s32 Copy_s32InMin ,s32 Copy_s32InMax , s32 Copy_s32OutMin , s32 Copy_s32OutMax )
{
	return (Copy_s32Val - Copy_s32InMin) * (Copy_s32OutMax - Copy_s32OutMin) / (Copy_s32InMax - Copy_s32InMin) + Copy_s32OutMin;
}


