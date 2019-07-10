/*************** (C) COPYRIGHT  EW工作室 ***************************************
 * 文件名  ：uart.h
 * 描述    ：串口调试文件   
 * 实验平台：EW STM8入门板 V1.0
 * 库版本  ：V2.1.0
 * QQ群	   ：261825684
 * 修改时间：2013-08-20
*******************************************************************************/
#ifndef __UART_H
#define	__UART_H

#include "stm8s.h"
#include "stm8s_clk.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#define USART_REC_LEN  	   64  	        //定义最大接收字节数 64

extern uint8_t USART_RX_STA;         		//接收状态标记	
extern uint8_t USART_RX_BUF[USART_REC_LEN];        //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 

void USART1_Init(uint32_t bound);
void UART1_SendByte(uint8_t data);
void u1printf(char *buf);

#endif /* __UART_H */
