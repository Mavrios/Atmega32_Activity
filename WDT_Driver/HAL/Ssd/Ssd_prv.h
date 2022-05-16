/*
 * Ssd_prv.h
 *
 *  Created on: Mar 21, 2022
 *      Author: Kishk
 */

#ifndef HAL_SSD_SSD_PRV_H_
#define HAL_SSD_SSD_PRV_H_

#define SSD_u8ONE_SSD_MAXIMUM_NUMBER	9
#define SSD_u8TWO_SSD_MAXIMUM_NUMBER	99
#define SSD_u8THREE_SSD_MAXIMUM_NUMBER	999
#define SSD_u8FOUR_SSD_MAXIMUM_NUMBER	9999

#define SSD_u8TWO_DIGITS				2
#define SSD_u8THREE_DIGITS				3
#define SSD_u8FOUR_DIGITS				4
#define SSD_u8NUMBER_OF_PINS			7

#define SSD_u8INITZERO					0

#define SSD_u8TEN						10
#define SSD_u8HUNDRED					100
#define SSD_u8THOUSEND					1000

#define SSD_DisableSSD0()				Dio_enuWriteChannel(SSD0_u8PINA , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD0_u8PINB , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD0_u8PINC , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD0_u8PIND , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD0_u8PINE , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD0_u8PINF , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD0_u8PING , DIO_u8LOW);

#define SSD_DisableSSD1()				Dio_enuWriteChannel(SSD1_u8PINA , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD1_u8PINB , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD1_u8PINC , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD1_u8PIND , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD1_u8PINE , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD1_u8PINF , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD1_u8PING , DIO_u8LOW);

#define SSD_DisableSSD2()				Dio_enuWriteChannel(SSD2_u8PINA , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD2_u8PINB , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD2_u8PINC , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD2_u8PIND , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD2_u8PINE , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD2_u8PINF , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD2_u8PING , DIO_u8LOW);

#define SSD_DisableSSD3()				Dio_enuWriteChannel(SSD3_u8PINA , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD3_u8PINB , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD3_u8PINC , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD3_u8PIND , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD3_u8PINE , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD3_u8PINF , DIO_u8LOW);\
										Dio_enuWriteChannel(SSD3_u8PING , DIO_u8LOW);



static u8 Ssd_u8NumbersPattern[] = {0x3F ,0x06 , 0x5B , 0x4F, 0x66 , 0x6D , 0x7D , 0x07 , 0x7F , 0x6F};
#endif /* HAL_SSD_SSD_PRV_H_ */
