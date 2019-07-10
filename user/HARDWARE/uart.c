/********************************************************************
*@file        uart.c
*@author      
*@version     V1.0
*@date        2016-10-14
*@brief       常用函数库
*******************************************************************/
#include "uart.h"


//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
uint8_t USART_RX_STA=0;       //接收状态标记	  
uint8_t USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

//使用printf函数需要大量的FLASH
#if DEBUG_PRINTF
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
#endif
/* Private functions ---------------------------------------------------------*/
//串口初始化函数
void USART1_Init(uint32_t bound) 
{  
    //PD5->UART1 TXD    PD6->UART1 RXD
    UART1_DeInit();
    UART1_Init(bound, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, \
        UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , UART1_MODE_TXRX_ENABLE);
    
    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
    UART1_Cmd(ENABLE );
}

/*******************************************************************************
 * 名称: UART1_SendByte
 * 功能: UART1发送一个字节
 * 形参: data -> 要发送的字节
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void UART1_SendByte(uint8_t data)
{
	UART1_SendData8((unsigned char)data);
	
	/* 等待传输结束 */
	while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}
#if DEBUG_PRINTF
PUTCHAR_PROTOTYPE ////发送一个字符协议
{
    /* 将Printf内容发往串口 */
    UART1_SendData8((unsigned char) ch);
    while (!(UART1->SR & UART1_FLAG_TXE));//如果发送未完成， //标志位未置位，则循环等待
    return (ch);
    
}
#else
void u1printf(char *buf)
{
    uint16_t j,i;
    
    i = strlen((char *)buf);
    for(j=0;j<i;j++){
        UART1_SendByte((uint8_t)buf[j]);
    }
    UART1_SendByte(0X0D);
    UART1_SendByte(0X0A);
}
/* 
void u1_printf(char *fmt,...)
{
    uint16_t i,j;
    va_list ap;
    va_start(ap,fmt);
    vsprintf((char*)USART1_TX_BUF,fmt,ap);
    va_end(ap);
    i=strlen((const char*)USART1_TX_BUF);  //此次发送数据的长度
    for(j=0;j<i;j++){
        UART1_SendData8(USART1_TX_BUF[j]);
        while (!(UART1->SR & UART1_FLAG_TXE));//如果发送未完成， //标志位未置位，则循环等待
    }
}*/
#endif
//串口中断接收服务函数
INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
    uint8_t Rec; 
    
    UART1_ClearFlag(UART1_FLAG_RXNE);
    Rec = UART1_ReceiveData8();
    if((USART_RX_STA&0x80)==0)//接收未完成
    {
        if(USART_RX_STA&0x40)//接收到了0x0d
        {
            if(Rec!=0x0a)  USART_RX_STA=0;//接收错误,重新开始
            else  USART_RX_STA|=0x80;	//接收完成了 
        }
        else //还没收到0X0D
        {	
            if(Rec==0x0d)  USART_RX_STA|=0x40;
            else
            {
                USART_RX_BUF[USART_RX_STA&0X3F]=Rec ;
                USART_RX_STA++;
                if(USART_RX_STA>(USART_REC_LEN-1))  USART_RX_STA=0;//接收数据错误,重新开始接收	  
            }		 
        }
    }
}


