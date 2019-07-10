/*************** (C) COPYRIGHT  ��ά���� ***************************************
* �ļ���  ��main.c
* ����    ������ģ��    
* ��汾  ��V1.1.0
* ������Ա��Woody QQ��2490006131
* �޸�ʱ�䣺2016-10-14
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/*  Defines -----------------------------------------------------------*/


static void Platfrom_Init(void){
    USART1_Init(9600);          //����1��ʼ������
    LT8920_GPIO_Init();         //LT8920��ʼ�� 
    SPI_8920_Init();            //SPI��ʼ��
    LT8900_Init();              //LT8920ʹ��
    LED_Init();                 //led״̬�Ƴ�ʼ��
    KEY_Init();                 //������ʼ��
}

int main(void)
{     
    SystemClock_Init();         //ϵͳʱ�ӳ�ʼ�� �ڲ�RC��������16Mhz
    delay_init(16);             //��ʱ��ʼ�� ϵͳʱ��Ϊ16Mhz
    Platfrom_Init();            //Ӳ����ʼ��
    enableInterrupts();         //�������ж�
    Check_LT8920();             //���LT8920�Ƿ���������
#if DEBUG_PRINTF   
    u1_printf("Initialization has been completed.\r\n");
#else
    u1printf("Initialization has been completed.");
#endif
    //ReadEEPROM((uint8_t *)config_lt8920,6);

    //Set_LT8920_MAC(config_lt8920[0],config_lt8920[1],config_lt8920[2],config_lt8920[3],config_lt8920[4],config_lt8920[5]);   //��������mac��ַ
    Set_LT8920_MAC(0,0,0,0,0,0);
#if Mode_control_T //����ģʽ 
    u1printf("I am in sending mode...");
    
    Key_Scan(LT8920_SEND_FREQUENCY);   //����mac��ַ��Ϣ�����յ��Ժ�����һ�飬Ȼ���˳�
    
    while(1){
        LT8920_TX_Control(LT8920_SEND_FREQUENCY); //����Ƶ��0x03
    }
#endif  
    
#if Mode_control_R  //����ģʽ
    u1printf("I am receiving mode...");
    
    Set_LT8920_RX_FREQ(LT8920_SEND_FREQUENCY);     //����Ƶ��0x03
    Key_Scan(LT8920_SEND_FREQUENCY);   //����mac��ַ��Ϣ ������һ�η���һ��
    while(1){
        LT8920_RX_Control(LT8920_SEND_FREQUENCY); //����Ƶ��0x03
    }
#endif
}

#ifdef USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval : None
*/
void assert_failed(u8* file, u32 line)
{ 
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    
    /* Infinite loop */
    while (1)
    {
    }
}
#endif


/******************* (C) COPYRIGHT EW������ *****END OF FILE******************/
