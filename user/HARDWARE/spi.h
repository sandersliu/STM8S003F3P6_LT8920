/********************************************************************
 *@file        spi.h
 *@author      Woody      QQ��2490006131
 *@version     V1.0
 *@date        2016-10-14
 *@brief       ���ú�����
 *******************************************************************/
#ifndef __SPI_H
#define __SPI_H
#include "stm8s.h"



void SPI_8920_Init(void);      //SPI��ʼ������
uint8_t SPI_SendByte(uint8_t byte); //SPI���߶�дһ���ֽ�

#endif