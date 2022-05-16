/*
 * Dio.h
 *
 *  Created on: Mar 5, 2022
 *      Author: Kishk
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_
/*MACROS*/

/*CHANNELID*/
	/*PORTA*/
#define DIO_u8CHANNEL00      0
#define DIO_u8CHANNEL01      1
#define DIO_u8CHANNEL02      2
#define DIO_u8CHANNEL03      3
#define DIO_u8CHANNEL04      4
#define DIO_u8CHANNEL05      5
#define DIO_u8CHANNEL06      6
#define DIO_u8CHANNEL07      7
	/*PORTB*/
#define DIO_u8CHANNEL08      8
#define DIO_u8CHANNEL09      9
#define DIO_u8CHANNEL10      10
#define DIO_u8CHANNEL11      11
#define DIO_u8CHANNEL12      12
#define DIO_u8CHANNEL13      13
#define DIO_u8CHANNEL14      14
#define DIO_u8CHANNEL15      15
	/*PORTC*/
#define DIO_u8CHANNEL16      16
#define DIO_u8CHANNEL17      17
#define DIO_u8CHANNEL18      18
#define DIO_u8CHANNEL19      19
#define DIO_u8CHANNEL20      20
#define DIO_u8CHANNEL21      21
#define DIO_u8CHANNEL22      22
#define DIO_u8CHANNEL23      23
	/*PORTD*/
#define DIO_u8CHANNEL24      24
#define DIO_u8CHANNEL25      25
#define DIO_u8CHANNEL26      26
#define DIO_u8CHANNEL27      27
#define DIO_u8CHANNEL28      28
#define DIO_u8CHANNEL29      29
#define DIO_u8CHANNEL30      30
#define DIO_u8CHANNEL31      31

/*LEVEL*/
#define DIO_u8LOW			 0
#define DIO_u8HIGH			 1

#define DIO_u8PORT_LOW		 0x00
#define DIO_u8PORT_HIGH		 0xFF


/*PORT ID*/
#define DIO_u8PORTA			0
#define DIO_u8PORTB			1
#define DIO_u8PORTC			2
#define DIO_u8PORTD			3


/*ENUM*/
typedef enum{
	Dio_enuOk=0,
	Dio_enuChannelError,
	Dio_enuDirectionError,
	Dio_enuNullPointer,
	Dio_enuPortError
}Dio_tenuErrorStatus;
/*********************************************************** PORTOTYPES **********************************************************************/
/****************************************************************************************************
 * Function:  Dio_enuWriteChannel																	*
 * ------------------------------------------------------------------------------------------------ *
 * WRITE ON SPECIFIC CHANNEL				                                                        *
 *                                                                                                  *
 *  Copy_u8ChannelId: DESIRED CHANNEL   --> OPTIONS --> DIO_u8CHANNELxx						        *
 *	Copy_u8Level: DESIRED CHANNEL LEVEL --> OPTIONS --> (DIO_u8LOW - DIO_u8HIGH)					*
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Dio_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
Dio_tenuErrorStatus Dio_enuWriteChannel(u8 Copy_u8ChannelId , u8 Copy_u8Level);
/****************************************************************************************************
 * Function:  Dio_enuReadChannel																	*
 * ------------------------------------------------------------------------------------------------ *
 * READ FROM SPECIFIC CHANNEL				                                                        *
 *                                                                                                  *
 *  Copy_u8ChannelId: DESIRED CHANNEL   --> OPTIONS --> DIO_u8CHANNELxx						        *
 *	Add_pu8Channellevel: ADDRESS OF VARIABLE WITH TYPE (u8) TO STORE THE RESULT IN THIS ADDRESS		*
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Dio_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
Dio_tenuErrorStatus Dio_enuReadChannel(u8 Copy_u8ChannelId , pu8 Add_pu8Channellevel);
/****************************************************************************************************
 * Function:  Dio_enuWritePort																		*
 * ------------------------------------------------------------------------------------------------ *
 * WRITE ON SPECIFIC PORT				                            	                            *
 *                                                                                                  *
 *  Copy_u8PortId: DESIRED PORT   --> OPTIONS --> DIO_u8PORTx								        *
 *	Copy_u8Value: DESIRED VALUE  --> OPTIONS --> (DIO_u8PORT_LOW - DIO_u8PORT_HIGH - (VALUE MAX 255)*
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Dio_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
Dio_tenuErrorStatus Dio_enuWritePort(u8 Copy_u8PortId , u8 Copy_u8Value);
/****************************************************************************************************
 * Function:  Dio_enuReadPort																		*
 * ------------------------------------------------------------------------------------------------ *
 * READ FROM SPECIFIC PORT				                            	                            *
 *                                                                                                  *
 *  Copy_u8PortId: DESIRED PORT   --> OPTIONS --> DIO_u8PORTx								        *
 *	Add_pu8PortValue: ADDRESS OF VARIABLE WITH TYPE (u8) TO STORE THE RESULT IN THIS ADDRESS		*
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Dio_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
Dio_tenuErrorStatus Dio_enuReadPort(u8 Copy_u8PortId , pu8 Add_pu8PortValue);
/****************************************************************************************************
 * Function:  Dio_enuflipChannel																	*
 * ------------------------------------------------------------------------------------------------ *
 * TOGGLE SPECIFIC CHANNEL 	FROM LOW TO HIGH AND FROM HIGH TO LOW									*
 *                                                                                                  *
 *  Copy_u8ChannelId: DESIRED CHANNEL   --> OPTIONS --> DIO_u8CHANNELxx						        *
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK Dio_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
Dio_tenuErrorStatus Dio_enuflipChannel(u8 Copy_u8ChannelId);

#endif /* MCAL_DIO_DIO_H_ */
