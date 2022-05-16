/*
 * Switch_cfg.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Kishk
 */

#include "../../Services/Std_types.h"
#include "../../Services/Bit_utils.h"
#include "../../MCAL/Dio/Dio.h"
#include "Switch.h"

const u8 Switch_u8Pin[Number_of_Switchs] = {
		[Start_Btn]= DIO_u8CHANNEL28,
		[Select_Btn]= DIO_u8CHANNEL29,
		[Increment_Btn]= DIO_u8CHANNEL30,
		[Decrement_Btn]= DIO_u8CHANNEL31,
};
