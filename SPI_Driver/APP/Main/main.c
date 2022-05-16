/*
 * main.c
 *
 *  Created on: May 6, 2022
 *      Author: Kishk
 */

#include "../../SERVICES/Std_types.h"
#include "../../SERVICES/Bit_utils.h"
#include <util/delay.h>
#include "../../MCAL/Dio/Dio.h"
#include "../../MCAL/Port/Port.h"
#include "../../MCAL/Spi/Spi.h"
int main(void)
{
	Port_vidInit();
	Spi_vidInit();
	while(1)
	{
		Dio_enuWriteChannel(DIO_u8CHANNEL08,DIO_u8LOW);
		Spi_u8Transfer('a');
		Dio_enuWriteChannel(DIO_u8CHANNEL08,DIO_u8HIGH);
		_delay_ms(1000);
		Dio_enuWriteChannel(DIO_u8CHANNEL08,DIO_u8LOW);
		Spi_u8Transfer('b');
		Dio_enuWriteChannel(DIO_u8CHANNEL08,DIO_u8HIGH);
		_delay_ms(1000);
	}
	return 0;
}
