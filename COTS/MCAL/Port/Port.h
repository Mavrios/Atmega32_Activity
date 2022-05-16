/*
 * PORT.h
 *
 *  Created on: Mar 4, 2022
 *      Author: Kishk
 */

#ifndef PORT_H_
#define PORT_H_

/*MACROS*/
/*DIRECTIONS*/
#define	PORT_u8INPUT	0
#define	PORT_u8OUTPUT	1
/*MODES*/
#define PORT_u8INPUT_FLOATING	0
#define PORT_u8INPUT_PULLUP		1
#define PORT_u8OUTPUT_LOW		2
#define PORT_u8OUTPUT_HIGH		3

/*PINS*/
	/*PORTA*/
#define PORT_u8PIN00      0
#define PORT_u8PIN01      1
#define PORT_u8PIN02      2
#define PORT_u8PIN03      3
#define PORT_u8PIN04      4
#define PORT_u8PIN05      5
#define PORT_u8PIN06      6
#define PORT_u8PIN07      7
	/*PORTB*/
#define PORT_u8PIN08      8
#define PORT_u8PIN09      9
#define PORT_u8PIN10      10
#define PORT_u8PIN11      11
#define PORT_u8PIN12      12
#define PORT_u8PIN13      13
#define PORT_u8PIN14      14
#define PORT_u8PIN15      15
	/*PORTC*/
#define PORT_u8PIN16      16
#define PORT_u8PIN17      17
#define PORT_u8PIN18      18
#define PORT_u8PIN19      19
#define PORT_u8PIN20      20
#define PORT_u8PIN21      21
#define PORT_u8PIN22      22
#define PORT_u8PIN23      23
	/*PORTD*/
#define PORT_u8PIN24      24
#define PORT_u8PIN25      25
#define PORT_u8PIN26      26
#define PORT_u8PIN27      27
#define PORT_u8PIN28      28
#define PORT_u8PIN29      29
#define PORT_u8PIN30      30
#define PORT_u8PIN31      31



/*ENUM*/
typedef enum{
	Port_enuOk=0,
	Port_enuPinError,
	Port_enuDirectionError,
	Port_enuModeError,
}Port_tenuErrorStatus;

/*PORTOTYPES*/
void				 Port_vidInit(void);
Port_tenuErrorStatus Port_enuSetPinDirection(u8 Copy_u8PinNum , u8 Copy_u8PinDirection);
Port_tenuErrorStatus Port_enuSetPinMode(u8 Copy_u8PinNum , u8 Copy_u8PinMode);



#endif /* PORT_H_ */
