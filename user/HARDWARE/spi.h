/********************************************************************
 *@file        spi.h
 *@author      Woody      QQ：2490006131
 *@version     V1.0
 *@date        2016-10-14
 *@brief       常用函数库
 *******************************************************************/
#ifndef __SPI_H
#define __SPI_H
#include "stm8s.h"



void SPI_8920_Init(void);      //SPI初始化函数
uint8_t SPI_SendByte(uint8_t byte); //SPI总线读写一个字节

#endif