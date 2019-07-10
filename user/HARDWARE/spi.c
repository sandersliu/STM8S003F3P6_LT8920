/********************************************************************
*@file        SPI.c
*@author      
*@version     V1.0
*@date        2016-10-14
*@brief       常用函数库
*******************************************************************/
#include "includes.h"

/*******************************************************************************
* 函数名：SPI_FLASH_Init
* 描述  ：SPI函数初始化
* 输入  ：无
* 输出  ：无
* 调用  ：外部调用
* 说明  ：
******************************************************************************/
void SPI_8920_Init(void)
{
    SPI_DeInit();
    // 初始化SPI,先发送MSB，fMASTER/2，主模式，空闲状态时SCK保持低电平，
    // 数据采样从第一个时钟边沿开始，双线单向数据模式，禁止软件从设备管理，CRC多项式0x07
    //SPI_Cmd(DISABLE);
    SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER,\
        SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_2EDGE, \
            SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);
    SPI_Cmd(ENABLE);	//使能SPI
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : 发送一个数据从SPI总线，从SPI总线读取一个数据.
* Input          : 要写入的字节
* Return         : 读取到的字节
*******************************************************************************/
uint8_t SPI_SendByte(uint8_t byte)
{
    /* Loop while DR register in not emplty */
    while (SPI_GetFlagStatus( SPI_FLAG_TXE) == RESET);
    
    /* Send byte through the SPI1 peripheral */
    SPI_SendData(byte);
    
    /* Wait to receive a byte */
    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
    
    /* Return the byte read from the SPI bus */
    return SPI_ReceiveData();	 
}











