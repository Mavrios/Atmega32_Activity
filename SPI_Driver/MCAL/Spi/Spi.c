/*
 * Spi.c
 *
 *  Created on: May 12, 2022
 *      Author: Kishk
 */

#include "../../SERVICES/Std_types.h"
#include "../../SERVICES/Bit_utils.h"
#include "../../SERVICES/Atmega32_Registers.h"
#include "Spi.h"
#include "Spi_cfg.h"
#include "Spi_prv.h"


void Spi_vidInit(void) {
#if SPI_u8INTERRUPT_CTRL == SPI_u8INTERRUPT_OFF
#define SPCR_BIT07				0
#elif SPI_u8INTERRUPT_CTRL == SPI_u8INTERRUPT_ON
#define SPCR_BIT07				1
#else
#error "Error SPI INTERRUPT Configurations"
#endif

#define SPCR_BIT06				1

#if SPI_u8DATA_ORDER == SPI_u8DATA_ORDER_MSB
#define SPCR_BIT05				0
#elif SPI_u8DATA_ORDER == SPI_u8DATA_ORDER_LSB
#define SPCR_BIT05				1
#else
#error "Error SPI Data Order Configurations"
#endif

#if SPI_u8MASTER_SLAVE_SELECT == SPI_u8MASTER
#define SPCR_BIT04				1
#elif SPI_u8MASTER_SLAVE_SELECT == SPI_u8SLAVE
#define SPCR_BIT04				0
#else
#error "Error SPI Master Slave Select Configurations"
#endif

#if SPI_u8CLOCK_POLARITY == SPI_u8CPOL_LEAD_F_TRAIL_R
#define SPCR_BIT03				1
#elif SPI_u8CLOCK_POLARITY == SPI_u8CPOL_LEAD_R_TRAIL_F
#define SPCR_BIT03				0
#else
#error "Error SPI Clock Polarity Configurations"
#endif

#if SPI_u8CLOCK_PHASE == SPI_u8CPHA_LEAD_SETUP_TRAIL_SAMP
#define SPCR_BIT02				1
#elif SPI_u8CLOCK_PHASE == SPI_u8CPHA_LEAD_SAMP_TRAIL_SETUP
#define SPCR_BIT02				0
#else
#error "Error SPI Clock Polarity Configurations"
#endif

#if SPI_u8SCK_CLOCK == SPI_u8FREQ_DIV_BY_2
#define SPCR_BIT01			0
#define SPCR_BIT00			0
#define SPSR_BIT00			1
#elif SPI_u8SCK_CLOCK == SPI_u8FREQ_DIV_BY_4
#define SPCR_BIT01			0
#define SPCR_BIT00			0
#define SPSR_BIT00			0
#elif SPI_u8SCK_CLOCK == SPI_u8FREQ_DIV_BY_8
#define SPCR_BIT00			1
#define SPCR_BIT01			0
#define SPSR_BIT00			1
#elif SPI_u8SCK_CLOCK == SPI_u8FREQ_DIV_BY_16
#define SPCR_BIT00			1
#define SPCR_BIT01			0
#define SPSR_BIT00			0
#elif SPI_u8SCK_CLOCK == SPI_u8FREQ_DIV_BY_32
#define SPCR_BIT00			0
#define SPCR_BIT01			1
#define SPSR_BIT00			1
#elif SPI_u8SCK_CLOCK == SPI_u8FREQ_DIV_BY_64
#define SPCR_BIT00			0
#define SPCR_BIT01			1
#define SPSR_BIT00			0
#elif SPI_u8SCK_CLOCK == SPI_u8FREQ_DIV_BY_128
#define SPCR_BIT00			1
#define SPCR_BIT01			1
#define SPSR_BIT00			0
#endif

#define SPSR_BIT01			0
#define SPSR_BIT02			0
#define SPSR_BIT03			0
#define SPSR_BIT04			0
#define SPSR_BIT05			0
#define SPSR_BIT06			0
#define SPSR_BIT07			0
	SPCR = CONC(SPCR_BIT07,SPCR_BIT06,SPCR_BIT05,SPCR_BIT04,SPCR_BIT03,SPCR_BIT02,SPCR_BIT01,SPCR_BIT00);
	SPSR = CONC(SPSR_BIT07,SPSR_BIT06,SPSR_BIT05,SPSR_BIT04,SPSR_BIT03,SPSR_BIT02,SPSR_BIT01,SPSR_BIT00);
}


u8	 Spi_u8Transfer(u8 Data)
{
	u8 Loc_u8RecievedData = 0;
	SPDR = Data;
	while(!(SPSR & (1 << SPIF)));
	Loc_u8RecievedData = SPDR;
	return Loc_u8RecievedData;
}
