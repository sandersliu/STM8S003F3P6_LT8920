/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM8S
*                                              with the
*                                   STM38s003F3P6 Evaluation Board
*
* Filename      : includes.h
* Version       : V1.10
* Programmer(s) : BAN
*************************************************************************************************/
#ifndef __INCLUDES_H
#define __INCLUDES_H
/*
*����ͷ�ļ�
*/
#include "stm8s.h"
#include "sysclock.h"
#include "flash_eeprom.h"
#include "delay.h"
#include "sys.h"
/*
*������ͷ�ļ�
*/
#include "spi.h"
#include "uart.h"
#include "led.h"
#include "key.h"
#include "lt8920.h"

/*
*C���Կ�ͷ�ļ�
*/
#include "stdio.h"
#include "string.h"
//#include "stdlib.h"
#include "stdarg.h"
//#include "stdbool.h"

// TX/RXģʽ�����ر�
#define   Mode_control_T  1      //����ģʽ
#define   Mode_control_R  0      //����ģʽ

#define   DEBUG_PRINTF    0      //���ڴ�ӡ����

extern uint8_t config_lt8920[6];






#endif
/**********************************     END     **********************************/


