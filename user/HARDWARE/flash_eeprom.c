/********************************************************************
*@file        flash_eeprom.c
*@author      Woody      QQ��2490006131
*@version     V1.0
*@date        2016-10-14
*@brief       eeprom��ʼ��
*******************************************************************/
#include "includes.h"


/*******************************************************************************
* ��������Init_EEPROM
* ����  ������EEPROM�ĳ�ʼ��
* ����  ����
* ���  ����
* ����  ���ⲿ����
* ˵��  : ÿ���ͺŵ�EEPROM�Ĵ�С��һ�������ô˺�����ʱ��Ҫע�⽫Ҫд�����ֽ�����
�Ĵ�С�Ƿ񳬹����ͺŵ�EEPROM�ĵ�ַ��
��������EEPROM���ͺ���STM8S208, STM8S207, STM8S007, STM8AF52Ax, STM8AF62Ax 
EEPROM�ĵ�ַ�Ǵ�0x004000��0x0047ff����2048Byte,ÿ��Block��128Byte,һ��16��Block.
BlockNum @ 1~16
��������EEPROM���ͺ���STM8S105, STM8S005, STM8AF626x
EEPROM�ĵ�ַ�Ǵ�0x004000��0x0043ff����1024Byte,ÿ��Block��128Byte,һ��8��Block.
BlockNum @ 1~8
С������EEPROM���ͺ���STM8S103, STM8S003, STM8S903 
EEPROM�ĵ�ַ�Ǵ�0x004000��0x00427f����1024Byte,ÿ��Block��64Byte,һ��10��Block.
BlockNum @ 1~10
******************************************************************************/
void Init_EEPROM(void)
{
    FLASH_DeInit();
}

#if EEPROM_UINT8
/*******************************************************************************
* ��������ReadEEPROM_Byte
* ����  ����FLASH ��ȡһ��U8���͵�����
* ����  ����
* ���  ��u8�������
* ����  ���ⲿ����
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
* ��������WriteEEPROM_Byte
* ����  ��WriteEEPROMдһ��U8���͵����ݵ�EEPROM
* ����  ����
* ���  ����
* ����  ���ⲿ����
******************************************************************************/
void WriteEEPROM_Byte(uint8_t data)
{ 
    FLASH_Unlock(FLASH_MEMTYPE_DATA); // ����EEPROM
    FLASH_ProgramByte(FLASH_DATA_START_PHYSICAL_ADDRESS,data);
    FLASH_Lock(FLASH_MEMTYPE_DATA); 
} 

/*******************************************************************************
* ��������ReadEEPROM
* ����  ����FLASH ��ȡһ��U8���͵�����
* ����  ��data uin8_t����  number ����
* ���  ��uint8_t ����
* ����  ���ⲿ����
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
* ��������WriteEEPROM
* ����  ��WriteEEPROMдһ��U8���͵����鵽EEPROM
* ����  ����
* ���  ����
* ����  ���ⲿ����
******************************************************************************/
void WriteEEPROM(uint8_t *data,uint16_t number)
{
    uint16_t i;
    uint8_t  *f;
    
    FLASH_Unlock(FLASH_MEMTYPE_DATA); // ����EEPROM
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
* ��������ReadEEPROM
* ����  ����FLASH ��ȡһ��U16���͵�����
* ����  ����
* ���  ��
* ����  ���ⲿ����
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
* ��������FLASHu16Byte
* ����  ����FLASH �洢һ��U16���͵�����
* ����  ����
* ���  ���ڲ�
* ����  ��.C����
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
* ��������WriteEEPROM
* ����  ��WriteEEPROMдһ��U16���͵����ݵ�EEPROM
* ����  ����
* ���  ����
* ����  ���ⲿ����
******************************************************************************/
void WriteEEPROM(uint16_t* data,uint16_t number)
{
    uint16_t i;
    uint8_t  *f;
    
    FLASH_Unlock(FLASH_MEMTYPE_DATA); // ����EEPROM
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
















