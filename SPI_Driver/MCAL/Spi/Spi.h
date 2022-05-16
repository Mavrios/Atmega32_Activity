/*
 * Spi.h
 *
 *  Created on: May 12, 2022
 *      Author: Kishk
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_


#define SPI_u8INTERRUPT_ON					0x01
#define SPI_u8INTERRUPT_OFF					0x00
#define SPI_u8DATA_ORDER_LSB				0x01
#define SPI_u8DATA_ORDER_MSB				0x00
#define SPI_u8MASTER						0x01
#define SPI_u8SLAVE							0x00
#define SPI_u8CPOL_LEAD_F_TRAIL_R			0x01
#define SPI_u8CPOL_LEAD_R_TRAIL_F			0x00
#define SPI_u8CPHA_LEAD_SETUP_TRAIL_SAMP	0x01
#define SPI_u8CPHA_LEAD_SAMP_TRAIL_SETUP	0x00

#define SPI_u8FREQ_DIV_BY_2					0x04
#define SPI_u8FREQ_DIV_BY_4					0x00
#define SPI_u8FREQ_DIV_BY_8					0x05
#define SPI_u8FREQ_DIV_BY_16				0x01
#define SPI_u8FREQ_DIV_BY_32				0x06
#define SPI_u8FREQ_DIV_BY_64				0x02
#define SPI_u8FREQ_DIV_BY_128				0x03

void Spi_vidInit(void);

u8	 Spi_u8Transfer(u8 Data);
#endif /* MCAL_SPI_SPI_H_ */
