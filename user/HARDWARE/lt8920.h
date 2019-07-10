/*************** (C) COPYRIGHT  EW������ ***************************************
 * �ļ���  ��uart.h
 * ����    �����ڵ����ļ�   
 * ʵ��ƽ̨��EW STM8���Ű� V1.0
 * ��汾  ��V2.1.0
 * QQȺ	   ��261825684
 * �޸�ʱ�䣺2013-08-20
*******************************************************************************/
#ifndef __LT8920_H
#define	__LT8920_H

#include "stm8s.h"
#include "stdio.h"
#include "stdbool.h"
#include "sys.h"
/* ѡ��LT8920оƬ */
#define LT8920_CS_LOW()       PC_ODR_ODR4 = 0 
#define LT8920_RST_LOW()      PD_ODR_ODR3 = 0 

/* ��ѡ��LT8920оƬ */
#define LT8920_CS_HIGH()      PC_ODR_ODR4 = 1 
#define LT8920_RST_HIGH()     PD_ODR_ODR3 = 1

#define LT8920_PKT_IN         PC_IDR_IDR3
#define LT8920_PKT_OUT        PC_ODR_ODR3

#define Dummy_Byte 0xFF       /* д����ֽڲ��� */ 

#define LT8920_SEND_FREQUENCY  0x03      

#define RESET          0
#define SET            1

extern unsigned char RegH;
extern unsigned char RegL;              //Used to store the Registor Value which is read.

void LT8900_Init(void);
void LT8920_GPIO_Init(void);
void SPI_ReadReg(unsigned char addr);
void SPI_WriteReg(unsigned char addr, unsigned char H, unsigned char L);

void Check_LT8920(void);
void LT8920_TX_Control(uint8_t req);
void LT8920_RX_Control(uint8_t req);
void Set_LT8920_RX_FREQ(uint8_t freq);
void Set_LT8920_TX_FREQ(uint8_t len,uint8_t* buffer,uint8_t freq);
void Set_LT8920_MAC(uint8_t a1,uint8_t a2,uint8_t a3,uint8_t a4,uint8_t a5,uint8_t a6);
#endif /* __UART_H */



