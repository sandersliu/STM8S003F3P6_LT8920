/********************************************************************
 *@file        changyong.h
 *@author      Woody      QQ��2490006131
 *@version     V1.0
 *@date        2016-10-14
 *@brief       ���ú�����
 *******************************************************************/
#ifndef __DELAY_H
#define __DELAY_H
#include "stm8s.h"

#define BIT(x) (1 << (x))

#define INTEN   asm("rim");    //open interrupt
#define INTOFF  asm("sim");    //closs interrupt
#define MCUSLEEP asm("halt");  //sleep

//******************************************************************************
//֧�ֲ�ͬʱ��Ƶ��
//�ṩdelay_us,delay_ms������ʱ����. 
//******************************************************************************
void delay_init(u8 clk); //��ʱ������ʼ��
void delay_us(u16 nus);  //us����ʱ����,���65536us.
void delay_ms(u32 nms);  //ms����ʱ����

#endif