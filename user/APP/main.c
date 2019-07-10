/*************** (C) COPYRIGHT  四维拓智 ***************************************
* 文件名  ：main.c
* 描述    ：工程模板    
* 库版本  ：V1.1.0
* 开发人员：Woody QQ：2490006131
* 修改时间：2016-10-14
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/*  Defines -----------------------------------------------------------*/


static void Platfrom_Init(void){
    USART1_Init(9600);          //串口1初始化函数
    LT8920_GPIO_Init();         //LT8920初始化 
    SPI_8920_Init();            //SPI初始化
    LT8900_Init();              //LT8920使能
    LED_Init();                 //led状态灯初始化
    KEY_Init();                 //按键初始化
}

int main(void)
{     
    SystemClock_Init();         //系统时钟初始化 内部RC高速振荡器16Mhz
    delay_init(16);             //延时初始化 系统时钟为16Mhz
    Platfrom_Init();            //硬件初始化
    enableInterrupts();         //开启总中断
    Check_LT8920();             //检测LT8920是否正常工作
#if DEBUG_PRINTF   
    u1_printf("Initialization has been completed.\r\n");
#else
    u1printf("Initialization has been completed.");
#endif
    //ReadEEPROM((uint8_t *)config_lt8920,6);

    //Set_LT8920_MAC(config_lt8920[0],config_lt8920[1],config_lt8920[2],config_lt8920[3],config_lt8920[4],config_lt8920[5]);   //设置组网mac地址
    Set_LT8920_MAC(0,0,0,0,0,0);
#if Mode_control_T //发送模式 
    u1printf("I am in sending mode...");
    
    Key_Scan(LT8920_SEND_FREQUENCY);   //接收mac地址信息，接收到以后设置一遍，然后退出
    
    while(1){
        LT8920_TX_Control(LT8920_SEND_FREQUENCY); //发射频率0x03
    }
#endif  
    
#if Mode_control_R  //接收模式
    u1printf("I am receiving mode...");
    
    Set_LT8920_RX_FREQ(LT8920_SEND_FREQUENCY);     //接收频率0x03
    Key_Scan(LT8920_SEND_FREQUENCY);   //发送mac地址信息 按键按一次发射一次
    while(1){
        LT8920_RX_Control(LT8920_SEND_FREQUENCY); //接收频率0x03
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


/******************* (C) COPYRIGHT EW工作室 *****END OF FILE******************/
