/*
 * Dio.c
 *
 *  Created on: Mar 5, 2022
 *      Author: Kishk
 */

#ifndef MCAL_DIO_DIO_C_
#define MCAL_DIO_DIO_C_

#include "../../Services/Bit_utils.h"
#include "../../Services/Std_types.h"
#include "Dio.h"
#include "Dio_prv.h"
#include "Dio_cfg.h"
#include <avr/io.h>

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
Dio_tenuErrorStatus Dio_enuWriteChannel(u8 Copy_u8ChannelId, u8 Copy_u8Level) {
	/*DIFINE RETURN STATUS*/
	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;
	/*DIFINE VARIABLE TO STORE PIN AND PORT NUMBER*/
	u8 LOC_u8PinNum;
	u8 LOC_u8PortNum;
	/*CHECK IF CHANNEL IS INVALID*/
	if (Copy_u8ChannelId > DIO_u8MAX_CHANNELS) {
		/*ASSIGN ERROR ID IN RETURN STATUS*/
		LOC_enuReturnStatus = Dio_enuChannelError;
	}
	/*CHECK IF THE LEVEL IS INVALID*/
	else if (Copy_u8Level > DIO_u8HIGH) {
		/*ASSIGN ERROR ID IN RETURN STATUS*/
		LOC_enuReturnStatus = Dio_enuChannelError;
	} else {
		/*CALCULATE PIN NUMBER*/
		LOC_u8PinNum = Copy_u8ChannelId % DIO_u8REG_SIZE;
		/*CALCULATE PORT NUMBER*/
		LOC_u8PortNum = Copy_u8ChannelId / DIO_u8REG_SIZE;
		/*SWITCH CASE TO CHECK PORT NUMBER*/
		switch (LOC_u8PortNum) {
		/*CHECK IF PORTA*/
		case DIO_u8PORTA: {
			/*CHECK IF PIN DIRECTION IS OUTPUT*/
			if (GET_BIT(DDRA,LOC_u8PinNum) == DIO_u8OUTPUT) {
				/*SWITCH CASE TO CHECK THE LEVEL*/
				switch (Copy_u8Level) {
				/*CASE HIGHT*/
				case DIO_u8HIGH:
					/*SET CHANNEL WITH HIGH*/
					SET_BIT(PORTA, LOC_u8PinNum);
					break;
					/*CASE LOW*/
				case DIO_u8LOW: {
					/*SET CHANNEL WITH LOW*/
					CLR_BIT(PORTA, LOC_u8PinNum);
					break;
				}
				}
			}
			/*CHECK IF THE DIRECTION OF THE PIN IS INPUT*/
			else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
			/*CHECK IF PORTB*/
		case DIO_u8PORTB: {
			/*CHECK IF PIN DIRECTION IS OUTPUT*/
			if (GET_BIT(DDRB,LOC_u8PinNum) == DIO_u8OUTPUT) {
				/*SWITCH CASE TO CHECK THE LEVEL*/
				switch (Copy_u8Level) {
				/*CASE HIGHT*/
				case DIO_u8HIGH:
					/*SET CHANNEL WITH HIGH*/
					SET_BIT(PORTB, LOC_u8PinNum);
					break;
					/*CASE LOW*/
				case DIO_u8LOW: {
					/*SET CHANNEL WITH LOW*/
					CLR_BIT(PORTB, LOC_u8PinNum);
					break;
				}
				}
			}
			/*CHECK IF THE DIRECTION OF THE PIN IS INPUT*/
			else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
			/*CHECK IF PORTC*/
		case DIO_u8PORTC: {
			/*CHECK IF PIN DIRECTION IS OUTPUT*/
			if (GET_BIT(DDRC,LOC_u8PinNum) == DIO_u8OUTPUT) {
				/*SWITCH CASE TO CHECK THE LEVEL*/
				switch (Copy_u8Level) {
				/*CASE HIGHT*/
				case DIO_u8HIGH:
					/*SET CHANNEL WITH HIGH*/
					SET_BIT(PORTC, LOC_u8PinNum);
					break;
					/*CASE LOW*/
				case DIO_u8LOW: {
					/*SET CHANNEL WITH LOW*/
					CLR_BIT(PORTC, LOC_u8PinNum);
					break;
				}
				}
			}
			/*CHECK IF THE DIRECTION OF THE PIN IS INPUT*/
			else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
			/*CHECK IF PORTD*/
		case DIO_u8PORTD: {
			/*CHECK IF PIN DIRECTION IS OUTPUT*/
			if (GET_BIT(DDRD,LOC_u8PinNum) == DIO_u8OUTPUT) {
				/*SWITCH CASE TO CHECK THE LEVEL*/
				switch (Copy_u8Level) {
				/*CASE HIGHT*/
				case DIO_u8HIGH:
					/*SET CHANNEL WITH HIGH*/
					SET_BIT(PORTD, LOC_u8PinNum);
					break;
					/*CASE LOW*/
				case DIO_u8LOW: {
					/*SET CHANNEL WITH LOW*/
					CLR_BIT(PORTD, LOC_u8PinNum);
					break;
				}
				}
			}
			/*CHECK IF THE DIRECTION OF THE PIN IS INPUT*/
			else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
		}
	}

	return LOC_enuReturnStatus;
}
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
Dio_tenuErrorStatus Dio_enuReadChannel(u8 Copy_u8ChannelId,
		pu8 Add_pu8Channellevel) {
	/*DIFINE RETURN STATUS*/
	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;
	/*DIFINE VARIABLE TO STORE PIN AND PORT NUMBER*/
	u8 LOC_u8PinNum;
	u8 LOC_u8PortNum;
	/*CHECK IF CHANNEL IS INVALID*/
	if (Copy_u8ChannelId > DIO_u8MAX_CHANNELS) {
		/*ASSIGN ERROR ID IN RETURN STATUS*/
		LOC_enuReturnStatus = Dio_enuChannelError;
	}
	/*CHECK IF THE POINTER IS NULL*/
	else if (Add_pu8Channellevel == NULL) {
		/*ASSIGN ERROR ID IN RETURN STATUS*/
		LOC_enuReturnStatus = Dio_enuNullPointer;
	} else {
		/*CALCULATE PIN NUMBER*/
		LOC_u8PinNum = Copy_u8ChannelId % DIO_u8REG_SIZE;
		/*CALCULATE PORT NUMBER*/
		LOC_u8PortNum = Copy_u8ChannelId / DIO_u8REG_SIZE;
		/*SWITCH CASE TO CHECK PORT NUMBER*/
		switch (LOC_u8PortNum) {
		/*CHECK IF PORTA*/
		case DIO_u8PORTA: {
			/*CHECK IF PIN DIRECTION IS INPUT*/
			if (GET_BIT(DDRA,LOC_u8PinNum) == DIO_u8INPUT) {
				/*GET THE PIN LEVEL*/
				*Add_pu8Channellevel = GET_BIT(PINA, LOC_u8PinNum);
			} else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			/*CHECK IF THE DIRECTION OF THE PIN IS INPUT*/
			break;
		}
			/*CHECK IF PORTB*/
		case DIO_u8PORTB: {
			/*CHECK IF PIN DIRECTION IS OUTPUT*/
			if (GET_BIT(DDRB,LOC_u8PinNum) == DIO_u8INPUT) {
				/*GET THE PIN LEVEL*/
				*Add_pu8Channellevel = GET_BIT(PINB, LOC_u8PinNum);
			} else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
			/*CHECK IF PORTC*/
		case DIO_u8PORTC: {
			/*CHECK IF PIN DIRECTION IS INPUT*/
			if (GET_BIT(DDRC,LOC_u8PinNum) == DIO_u8INPUT) {
				/*GET THE PIN LEVEL*/
				*Add_pu8Channellevel = GET_BIT(PINC, LOC_u8PinNum);
			} else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
		case DIO_u8PORTD: {
			/*CHECK IF PIN DIRECTION IS INPUT*/
			if (GET_BIT(DDRD,LOC_u8PinNum) == DIO_u8INPUT) {
				/*GET THE PIN LEVEL*/
				*Add_pu8Channellevel = GET_BIT(PIND, LOC_u8PinNum);
			} else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
		}
	}

	return LOC_enuReturnStatus;
}
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
Dio_tenuErrorStatus Dio_enuWritePort(u8 Copy_u8PortId, u8 Copy_u8Value) {
	/*DEFINE RETURN STATUS VARIABLE*/
	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;
	/*CHECK IF THE INPUT PORT WITHIN THE RANGE*/
	if (Copy_u8PortId > DIO_u8PORTD) {
		/*ASSIGN ERROR ID IN RETURN STATUS*/
		LOC_enuReturnStatus = Dio_enuPortError;
	} else {
		/*SWITCH CASE TO CHECK PORT*/
		switch (Copy_u8PortId) {
		/*CASE PORT A*/
		case DIO_u8PORTA: {
			/*ASSIGN REQUIRED VALUE INTO PORT A*/
			ASSIGN_REG(PORTA, Copy_u8Value);
			break;
		}
		case DIO_u8PORTB: {
			/*ASSIGN REQUIRED VALUE INTO PORT B*/
			ASSIGN_REG(PORTB, Copy_u8Value);
			break;
		}
		case DIO_u8PORTC: {
			/*ASSIGN REQUIRED VALUE INTO PORT C*/
			ASSIGN_REG(PORTC, Copy_u8Value);
			break;
		}
		case DIO_u8PORTD: {
			/*ASSIGN REQUIRED VALUE INTO PORT D*/
			ASSIGN_REG(PORTD, Copy_u8Value);
			break;
		}

		}
	}
	return LOC_enuReturnStatus;
}
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
Dio_tenuErrorStatus Dio_enuReadPort(u8 Copy_u8PortId, pu8 Add_pu8PortValue) {
	/*DEFINE RETURN STATUS VARIABLE*/
	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;
	/*CHECK IF THE INPUT PORT WITHIN THE RANGE*/
	if (Copy_u8PortId > DIO_u8PORTD) {
		/*ASSIGN ERROR ID IN RETURN STATUS*/
		LOC_enuReturnStatus = Dio_enuPortError;
	} else if (Add_pu8PortValue == NULL) {
		LOC_enuReturnStatus = Dio_enuNullPointer;
	} else {
		/*SWITCH CASE TO CHECK PORT*/
		switch (Copy_u8PortId) {
		/*CASE PORT A*/
		case DIO_u8PORTA: {
			/*GET REQUIRED VALUE FROM PORT A*/
			*Add_pu8PortValue = PINA;
			break;
		}
		case DIO_u8PORTB: {
			/*GET REQUIRED VALUE FROM PORT B*/
			*Add_pu8PortValue = PINB;
			break;
		}
		case DIO_u8PORTC: {
			/*GET REQUIRED VALUE FROM PORT C*/
			*Add_pu8PortValue = PINC;
			break;
		}
		case DIO_u8PORTD: {
			/*GET REQUIRED VALUE FROM PORT D*/
			*Add_pu8PortValue = PIND;
			break;
		}

		}
	}
	return LOC_enuReturnStatus;
}

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
Dio_tenuErrorStatus Dio_enuflipChannel(u8 Copy_u8ChannelId) {
	/*DIFINE RETURN STATUS*/
	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;
	/*DIFINE VARIABLE TO STORE PIN AND PORT NUMBER*/
	u8 LOC_u8PinNum;
	u8 LOC_u8PortNum;
	/*CHECK IF CHANNEL IS INVALID*/
	if (Copy_u8ChannelId > DIO_u8MAX_CHANNELS) {
		/*ASSIGN ERROR ID IN RETURN STATUS*/
		LOC_enuReturnStatus = Dio_enuChannelError;
	} else {
		/*CALCULATE PIN NUMBER*/
		LOC_u8PinNum = Copy_u8ChannelId % DIO_u8REG_SIZE;
		/*CALCULATE PORT NUMBER*/
		LOC_u8PortNum = Copy_u8ChannelId / DIO_u8REG_SIZE;
		/*SWITCH CASE TO CHECK PORT NUMBER*/
		switch (LOC_u8PortNum) {
		/*CHECK IF PORTA*/
		case DIO_u8PORTA: {
			/*CHECK IF PIN DIRECTION IS OUTPUT*/
			if (GET_BIT(DDRA,LOC_u8PinNum) == DIO_u8OUTPUT) {
				/*FLIP PORTA STATUS*/
				TGL_BIT(PORTA,LOC_u8PinNum);
			}
			/*CHECK IF THE DIRECTION OF THE PIN IS INPUT*/
			else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
			/*CHECK IF PORTB*/
		case DIO_u8PORTB: {
			/*CHECK IF PIN DIRECTION IS OUTPUT*/
			if (GET_BIT(DDRB,LOC_u8PinNum) == DIO_u8OUTPUT) {
				/*FLIP PORTB STATUS*/
				TGL_BIT(PORTB,LOC_u8PinNum);
			}
			/*CHECK IF THE DIRECTION OF THE PIN IS INPUT*/
			else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
			/*CHECK IF PORTC*/
		case DIO_u8PORTC: {
			/*CHECK IF PIN DIRECTION IS OUTPUT*/
			if (GET_BIT(DDRC,LOC_u8PinNum) == DIO_u8OUTPUT) {
				/*FLIP PORTA STATUS*/
				TGL_BIT(PORTC,LOC_u8PinNum);
			}
			/*CHECK IF THE DIRECTION OF THE PIN IS INPUT*/
			else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
			/*CHECK IF PORTD*/
		case DIO_u8PORTD: {
			/*CHECK IF PIN DIRECTION IS OUTPUT*/
			if (GET_BIT(DDRD,LOC_u8PinNum) == DIO_u8OUTPUT) {
				/*FLIP PORTA STATUS*/
				TGL_BIT(PORTD,LOC_u8PinNum);
			}
			/*CHECK IF THE DIRECTION OF THE PIN IS INPUT*/
			else {
				/*ASSIGN ERROR ID IN RETURN STATUS*/
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;
		}
		}
	}

	return LOC_enuReturnStatus;
}

#endif /* MCAL_DIO_DIO_C_ */
