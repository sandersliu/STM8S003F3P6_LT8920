/********************************************************************
 *@file        flash_eeprom.h
 *@author      Woody      QQ：2490006131
 *@version     V1.0
 *@date        2016-10-14
 *@brief       EEPROM初始化以及读取/写入数据
 *******************************************************************/
#ifndef __FLASH_EEPROM_H
#define __FLASH_EEPROM_H

#include "stm8s.h"



#define EEPROM_UINT8    1
#define EEPROM_UINT16   0


void Init_EEPROM(void);  // 初始化

#if EEPROM_UINT8
uint8_t ReadEEPROM_Byte(void);
void WriteEEPROM_Byte(uint8_t data);
void ReadEEPROM(uint8_t* data,uint8_t number);
void WriteEEPROM(uint8_t *data,uint16_t number);
#endif

#if EEPROM_UINT16
void ReadEEPROM(uint16_t* data,uint16_t number);
void WriteEEPROM(uint16_t* data,uint16_t number);
#endif

#endif


