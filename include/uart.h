/*
 * File	: uart.h
 * Copyright (C) 2013 - 2016, Espressif Systems
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef UART_APP_H
#define UART_APP_H

#include "uart_register.h"
#include "eagle_soc.h"
#include "c_types.h"

#define UART0   0
#define UART1   1


typedef enum {
	FIVE_BITS                = 0x0,
	SIX_BITS                 = 0x1,
	SEVEN_BITS               = 0x2,
	EIGHT_BITS               = 0x3
} UartBitsNum4Char;

typedef enum {
	ONE_STOP_BIT             = 0x1,
	ONE_HALF_STOP_BIT        = 0x2,
	TWO_STOP_BIT             = 0x3
} UartStopBitsNum;

typedef enum {
	NONE_BITS = 0x2,
	ODD_BITS   = 1,
	EVEN_BITS = 0
} UartParityMode;

typedef enum {
	STICK_PARITY_DIS   = 0,
	STICK_PARITY_EN    = 1
} UartExistParity;

typedef enum {
	UART_None_Inverse = 0x0,
	UART_Rxd_Inverse = UART_RXD_INV,
	UART_CTS_Inverse = UART_CTS_INV,
	UART_Txd_Inverse = UART_TXD_INV,
	UART_RTS_Inverse = UART_RTS_INV,
} UART_LineLevelInverse;


typedef enum {
	BIT_RATE_300 = 300,
	BIT_RATE_600 = 600,
	BIT_RATE_1200 = 1200,
	BIT_RATE_2400 = 2400,
	BIT_RATE_4800 = 4800,
	BIT_RATE_9600   = 9600,
	BIT_RATE_19200  = 19200,
	BIT_RATE_38400  = 38400,
	BIT_RATE_57600  = 57600,
	BIT_RATE_74880  = 74880,
	BIT_RATE_115200 = 115200,
	BIT_RATE_230400 = 230400,
	BIT_RATE_460800 = 460800,
	BIT_RATE_921600 = 921600,
	BIT_RATE_1843200 = 1843200,
	BIT_RATE_3686400 = 3686400,
} UartBautRate;

typedef enum {
	NONE_CTRL,
	HARDWARE_CTRL,
	XON_XOFF_CTRL
} UartFlowCtrl;

typedef enum {
	USART_HardwareFlowControl_None = 0x0,
	USART_HardwareFlowControl_RTS = 0x1,
	USART_HardwareFlowControl_CTS = 0x2,
	USART_HardwareFlowControl_CTS_RTS = 0x3
} UART_HwFlowCtrl;


//==============================================
#define FUNC_UART0_CTS 4
#define FUNC_U0CTS                      4
#define FUNC_U1TXD_BK                   2
#define UART_LINE_INV_MASK  (0x3f << 19)

//==============================================

#endif
