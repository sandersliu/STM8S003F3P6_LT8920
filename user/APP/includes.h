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
*常用头文件
*/
#include "stm8s.h"
#include "sysclock.h"
#include "flash_eeprom.h"
#include "delay.h"
#include "sys.h"
/*
*驱动库头文件
*/
#include "spi.h"
#include "uart.h"
#include "led.h"
#include "key.h"
#include "lt8920.h"

/*
*C语言库头文件
*/
#include "stdio.h"
#include "string.h"
//#include "stdlib.h"
#include "stdarg.h"
//#include "stdbool.h"

// TX/RX模式开启关闭
#define   Mode_control_T  1      //发送模式
#define   Mode_control_R  0      //接收模式

#define   DEBUG_PRINTF    0      //串口打印调试

extern uint8_t config_lt8920[6];






#endif
/**********************************     END     **********************************/


