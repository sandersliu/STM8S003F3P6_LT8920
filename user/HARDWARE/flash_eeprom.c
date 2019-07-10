/********************************************************************
*@file        flash_eeprom.c
*@author      Woody      QQ：2490006131
*@version     V1.0
*@date        2016-10-14
*@brief       eeprom初始化
*******************************************************************/
#include "includes.h"


/*******************************************************************************
* 函数名：Init_EEPROM
* 描述  ：配置EEPROM的初始化
* 输入  ：无
* 输出  ：无
* 调用  ：外部调用
* 说明  : 每种型号的EEPROM的大小不一样，调用此函数的时候要注意将要写进的字节数组
的大小是否超过该型号的EEPROM的地址。
大容量的EEPROM的型号是STM8S208, STM8S207, STM8S007, STM8AF52Ax, STM8AF62Ax 
EEPROM的地址是从0x004000到0x0047ff，共2048Byte,每个Block是128Byte,一共16个Block.
BlockNum @ 1~16
中容量的EEPROM的型号是STM8S105, STM8S005, STM8AF626x
EEPROM的地址是从0x004000到0x0043ff，共1024Byte,每个Block是128Byte,一共8个Block.
BlockNum @ 1~8
小容量的EEPROM的型号是STM8S103, STM8S003, STM8S903 
EEPROM的地址是从0x004000到0x00427f，共1024Byte,每个Block是64Byte,一共10个Block.
BlockNum @ 1~10
******************************************************************************/
void Init_EEPROM(void)
{
    FLASH_DeInit();
}

#if EEPROM_UINT8
/*******************************************************************************
* 函数名：ReadEEPROM_Byte
* 描述  ：从FLASH 读取一个U8类型的数据
* 输入  ：无
* 输出  ：u8类型输出
* 调用  ：外部调用
******************************************************************************/
uint8_t ReadEEPROM_Byte(void)
{ 
    uint8_t data;
    
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    data = FLASH_ReadByte(FLASH_DATA_START_PHYSICAL_ADDRESS);
    FLASH_Lock(FLASH_MEMTYPE_DATA);
    return data;
}
/*******************************************************************************
* 函数名：WriteEEPROM_Byte
* 描述  ：WriteEEPROM写一个U8类型的数据到EEPROM
* 输入  ：无
* 输出  ：无
* 调用  ：外部调用
******************************************************************************/
void WriteEEPROM_Byte(uint8_t data)
{ 
    FLASH_Unlock(FLASH_MEMTYPE_DATA); // 解锁EEPROM
    FLASH_ProgramByte(FLASH_DATA_START_PHYSICAL_ADDRESS,data);
    FLASH_Lock(FLASH_MEMTYPE_DATA); 
} 

/*******************************************************************************
* 函数名：ReadEEPROM
* 描述  ：从FLASH 读取一个U8类型的数据
* 输入  ：data uin8_t数组  number 数量
* 输出  ：uint8_t 数组
* 调用  ：外部调用
******************************************************************************/
void ReadEEPROM(uint8_t* data,uint8_t number)
{
    uint8_t i;
    
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    for(i=0;i<number;i++)
    {
        data[i] = *(uint8_t*)(0x4000+i);
    }
    
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}
/*******************************************************************************
* 函数名：WriteEEPROM
* 描述  ：WriteEEPROM写一个U8类型的数组到EEPROM
* 输入  ：无
* 输出  ：无
* 调用  ：外部调用
******************************************************************************/
void WriteEEPROM(uint8_t *data,uint16_t number)
{
    uint16_t i;
    uint8_t  *f;
    
    FLASH_Unlock(FLASH_MEMTYPE_DATA); // 解锁EEPROM
    delay_ms(10);
    for(i=0;i<600;i++)
    {
        f = (uint8_t*)(0X4000+i);
        if(*f!=0) 
        {
            *f=0;
            while(FLASH->IAPSR & 0x40 == 0);
        }
    }
    while(FLASH->IAPSR & 0x40 == 0);
    for(i=0;i<number;i++)
    {
        FLASH_ProgramByte(0X4000+i,data[i]);
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA); 
}


#endif


#if EEPROM_UINT16
/*******************************************************************************
* 函数名：ReadEEPROM
* 描述  ：从FLASH 读取一个U16类型的数据
* 输入  ：无
* 输出  ：
* 调用  ：外部调用
******************************************************************************/
void ReadEEPROM(uint16_t* data,uint16_t number)
{
    uint16_t i;
    
    FLASH_Unlock(FLASH_MEMTYPE_DATA);   
    for(i=0;i<number;i++)
    {
        data[i+1] = *(uint16_t*)(0x4000+2+i*2);
    }
    
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}
/*******************************************************************************
* 函数名：FLASHu16Byte
* 描述  ：从FLASH 存储一个U16类型的数据
* 输入  ：无
* 输出  ：内部
* 调用  ：.C调用
******************************************************************************/
static void FLASHu16Byte(uint16_t Address, uint16_t Data)
{
    if(*((uint8_t*)(&Data)))
    {
        *(( uint8_t*)Address)  = *((uint8_t*)(&Data));
        while(FLASH->IAPSR & 0x40 == 0);
    }
    if(*((uint8_t*)(&Data)+1))
    {
        *(((uint8_t*)Address) + 1) = *((uint8_t*)(&Data)+1);
        while(FLASH->IAPSR & 0x40 == 0);
    }
}
/*******************************************************************************
* 函数名：WriteEEPROM
* 描述  ：WriteEEPROM写一个U16类型的数据到EEPROM
* 输入  ：无
* 输出  ：无
* 调用  ：外部调用
******************************************************************************/
void WriteEEPROM(uint16_t* data,uint16_t number)
{
    uint16_t i;
    uint8_t  *f;
    
    FLASH_Unlock(FLASH_MEMTYPE_DATA); // 解锁EEPROM
    delay_ms(10);
    for(i=0;i<600;i++)
    {
        f = (uint8_t*)(0X4000+i);
        if(*f!=0) 
        {
            *f=0;
            while(FLASH->IAPSR & 0x40 == 0);
        }
    } 
    FLASHu16Byte(0X4000,number);
    while(FLASH->IAPSR & 0x40 == 0);
    for(i=0;i<number;i++)
    {
        FLASHu16Byte((0X4000+2)+(i*2),data[i+1]);
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA); 
} 
#endif
















