/*
 * Spi_cfg.h
 *
 *  Created on: May 12, 2022
 *      Author: Kishk
 */

#ifndef MCAL_SPI_SPI_CFG_H_
#define MCAL_SPI_SPI_CFG_H_

/*
 * OPTIONS:-
 * 1-SPI_u8INTERRUPT_OFF
 * 2-SPI_u8INTERRUPT_ON
 * */
#define SPI_u8INTERRUPT_CTRL		SPI_u8INTERRUPT_OFF

/*
 * OPTIONS:-
 * 1-SPI_u8DATA_ORDER_MSB
 * 2-SPI_u8DATA_ORDER_LSB
 * */
#define SPI_u8DATA_ORDER			SPI_u8DATA_ORDER_MSB

/*
 * OPTIONS:-
 * 1-SPI_u8MASTER
 * 2-SPI_u8SLAVE
 * */
#define SPI_u8MASTER_SLAVE_SELECT			SPI_u8MASTER

/*
 * OPTIONS:-
 * 1-SPI_u8CPOL_LEAD_F_TRAIL_R
 * 2-SPI_u8CPOL_LEAD_R_TRAIL_F
 * */
#define SPI_u8CLOCK_POLARITY			SPI_u8CPOL_LEAD_R_TRAIL_F

/*
 * OPTIONS:-
 * 1-SPI_u8CPHA_LEAD_SETUP_TRAIL_SAMP
 * 2-SPI_u8CPHA_LEAD_SAMP_TRAIL_SETUP
 * */
#define SPI_u8CLOCK_PHASE			SPI_u8CPHA_LEAD_SAMP_TRAIL_SETUP

/*
 * OPTIONS:-
 * 1-SPI_u8FREQ_DIV_BY_2
 * 2-SPI_u8FREQ_DIV_BY_4
 * 3-SPI_u8FREQ_DIV_BY_8
 * 4-SPI_u8FREQ_DIV_BY_16
 * 5-SPI_u8FREQ_DIV_BY_32
 * 6-SPI_u8FREQ_DIV_BY_64
 * 7-SPI_u8FREQ_DIV_BY_128
 * */
#define SPI_u8SCK_CLOCK				SPI_u8FREQ_DIV_BY_128

#endif /* MCAL_SPI_SPI_CFG_H_ */
