/********************************************************************
*@file        uart.c
*@author      
*@version     V1.0
*@date        2016-10-14
*@brief       ���ú�����
*******************************************************************/
#include "uart.h"


//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
uint8_t USART_RX_STA=0;       //����״̬���	  
uint8_t USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

//ʹ��printf������Ҫ������FLASH
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
//���ڳ�ʼ������
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
 * ����: UART1_SendByte
 * ����: UART1����һ���ֽ�
 * �β�: data -> Ҫ���͵��ֽ�
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void UART1_SendByte(uint8_t data)
{
	UART1_SendData8((unsigned char)data);
	
	/* �ȴ�������� */
	while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}
#if DEBUG_PRINTF
PUTCHAR_PROTOTYPE ////����һ���ַ�Э��
{
    /* ��Printf���ݷ������� */
    UART1_SendData8((unsigned char) ch);
    while (!(UART1->SR & UART1_FLAG_TXE));//�������δ��ɣ� //��־λδ��λ����ѭ���ȴ�
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
    i=strlen((const char*)USART1_TX_BUF);  //�˴η������ݵĳ���
    for(j=0;j<i;j++){
        UART1_SendData8(USART1_TX_BUF[j]);
        while (!(UART1->SR & UART1_FLAG_TXE));//�������δ��ɣ� //��־λδ��λ����ѭ���ȴ�
    }
}*/
#endif
//�����жϽ��շ�����
INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
    uint8_t Rec; 
    
    UART1_ClearFlag(UART1_FLAG_RXNE);
    Rec = UART1_ReceiveData8();
    if((USART_RX_STA&0x80)==0)//����δ���
    {
        if(USART_RX_STA&0x40)//���յ���0x0d
        {
            if(Rec!=0x0a)  USART_RX_STA=0;//���մ���,���¿�ʼ
            else  USART_RX_STA|=0x80;	//��������� 
        }
        else //��û�յ�0X0D
        {	
            if(Rec==0x0d)  USART_RX_STA|=0x40;
            else
            {
                USART_RX_BUF[USART_RX_STA&0X3F]=Rec ;
                USART_RX_STA++;
                if(USART_RX_STA>(USART_REC_LEN-1))  USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
            }		 
        }
    }
}


