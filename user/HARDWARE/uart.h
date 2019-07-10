/*************** (C) COPYRIGHT  EW������ ***************************************
 * �ļ���  ��uart.h
 * ����    �����ڵ����ļ�   
 * ʵ��ƽ̨��EW STM8���Ű� V1.0
 * ��汾  ��V2.1.0
 * QQȺ	   ��261825684
 * �޸�ʱ�䣺2013-08-20
*******************************************************************************/
#ifndef __UART_H
#define	__UART_H

#include "stm8s.h"
#include "stm8s_clk.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#define USART_REC_LEN  	   64  	        //�����������ֽ��� 64

extern uint8_t USART_RX_STA;         		//����״̬���	
extern uint8_t USART_RX_BUF[USART_REC_LEN];        //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 

void USART1_Init(uint32_t bound);
void UART1_SendByte(uint8_t data);
void u1printf(char *buf);

#endif /* __UART_H */
