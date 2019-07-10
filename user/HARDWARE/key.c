/********************************************************************
*@file        key.c
*@author      Woody      QQ：2490006131
*@version     V1.0
*@date        2016-10-14
*@brief       按键功能初始化
*******************************************************************/
#include "includes.h"

uint8_t config_lt8920[6]={0x03,0x80,0x5a,0x5a,0x20,0x82};

void KEY_Init(void)
{       
    GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);
}

//接收模块发送数据
#if Mode_control_R
void Key_Scan(uint8_t req)
{
    uint16_t j;
    if(Read_GPIOD_PIN4 == 0){
        delay_ms(20);
        if(Read_GPIOD_PIN4 == 0){
            while(1){
                config_lt8920[0]=0x03;config_lt8920[1]=0x80;
                config_lt8920[2]=0x5a;config_lt8920[3]=0x5a;
                config_lt8920[4]=0x20;config_lt8920[5]=0x82;   //设置组网mac地址
                Set_LT8920_TX_FREQ(6,(uint8_t *)config_lt8920,req); //发射频率0x03
                j = 10000; //
                while(LT8920_PKT_IN == 0) //等待发送完成
                {
                    j --;
                    delay_us(10);
                    if(j == 0)
                        break;
                }
                SPI_ReadReg(52);    //判断是否收到对方自动应答信号,REG52<13:8>应为0
                if((RegH& 0x3F)==0)//如果收到应答信号点亮本地对应的LED
                {
                    PAout(3,1);//为1亮
                    delay_ms(1000);
                    PAout(3,0);
                    break;
                }
                //Set_LT8920_MAC(config_lt8920[0],config_lt8920[1],config_lt8920[2],config_lt8920[3],config_lt8920[4],config_lt8920[5]);
                delay_ms(20);
            }
        }
    }
}
#endif

//发送模块接收MAC地址信息
#if Mode_control_T
void Key_Scan(uint8_t req)
{
    uint8_t len;
    
    if(Read_GPIOD_PIN4 == 0){
        delay_ms(20);
        if(Read_GPIOD_PIN4 == 0){
            //Set_LT8920_MAC(0,0,0,0,0,0);
            //delay_ms(20);
            Set_LT8920_RX_FREQ(LT8920_SEND_FREQUENCY);     //接收频率0x03
            while(1){
                PAout(3,1);
                if(LT8920_PKT_IN == 1)//检查是否接收到数据
                {
                    SPI_ReadReg(50);
                    len=RegH;//读取包长度  最大长度0XFF
                    if(len == 6){
                        config_lt8920[0]=RegL;  
                        SPI_ReadReg(50);
                        config_lt8920[1]=RegH;
                        config_lt8920[2]=RegL;
                        SPI_ReadReg(50);
                        config_lt8920[3]=RegH;
                        config_lt8920[4]=RegL;
                        SPI_ReadReg(50);
                        config_lt8920[5]=RegH;
                    }
                    SPI_ReadReg(48);     //Test CRC
                    if((RegH&0x80)==0)  //CRC无错误 ，一旦发生错误，寄存器 Reg48 bit15 位 CRC_ERROR 将被自动置 1，在下次开始 RX 或 TX 时它将被清除。
                    {   
                        PAout(3,1);
                        //Set_LT8920_MAC(config_lt8920[0],config_lt8920[1],config_lt8920[2],config_lt8920[3],config_lt8920[4],config_lt8920[5]);
                        //保存到EEPROM
                        WriteEEPROM((uint8_t *)config_lt8920,len);
                        PAout(3,0);
                        break;
                    }
                    SPI_WriteReg(52, 0x80, 0x80); //清空 RXTX
                    SPI_WriteReg(7, 0x00, (0x80|req));  //接收模式
                }
            }
        }
    }
}
#endif







