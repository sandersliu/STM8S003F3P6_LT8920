/********************************************************************
*@file        SPI.c
*@author      
*@version     V1.0
*@date        2016-10-14
*@brief       ���ú�����
*******************************************************************/
#include "includes.h"

/*******************************************************************************
* ��������SPI_FLASH_Init
* ����  ��SPI������ʼ��
* ����  ����
* ���  ����
* ����  ���ⲿ����
* ˵��  ��
******************************************************************************/
void SPI_8920_Init(void)
{
    SPI_DeInit();
    // ��ʼ��SPI,�ȷ���MSB��fMASTER/2����ģʽ������״̬ʱSCK���ֵ͵�ƽ��
    // ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ��˫�ߵ�������ģʽ����ֹ������豸����CRC����ʽ0x07
    //SPI_Cmd(DISABLE);
    SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER,\
        SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_2EDGE, \
            SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);
    SPI_Cmd(ENABLE);	//ʹ��SPI
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : ����һ�����ݴ�SPI���ߣ���SPI���߶�ȡһ������.
* Input          : Ҫд����ֽ�
* Return         : ��ȡ�����ֽ�
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











