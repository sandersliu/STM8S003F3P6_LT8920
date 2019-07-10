/********************************************************************
*@file        key.c
*@author      Woody      QQ��2490006131
*@version     V1.0
*@date        2016-10-14
*@brief       �������ܳ�ʼ��
*******************************************************************/
#include "includes.h"

uint8_t config_lt8920[6]={0x03,0x80,0x5a,0x5a,0x20,0x82};

void KEY_Init(void)
{       
    GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);
}

//����ģ�鷢������
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
                config_lt8920[4]=0x20;config_lt8920[5]=0x82;   //��������mac��ַ
                Set_LT8920_TX_FREQ(6,(uint8_t *)config_lt8920,req); //����Ƶ��0x03
                j = 10000; //
                while(LT8920_PKT_IN == 0) //�ȴ��������
                {
                    j --;
                    delay_us(10);
                    if(j == 0)
                        break;
                }
                SPI_ReadReg(52);    //�ж��Ƿ��յ��Է��Զ�Ӧ���ź�,REG52<13:8>ӦΪ0
                if((RegH& 0x3F)==0)//����յ�Ӧ���źŵ������ض�Ӧ��LED
                {
                    PAout(3,1);//Ϊ1��
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

//����ģ�����MAC��ַ��Ϣ
#if Mode_control_T
void Key_Scan(uint8_t req)
{
    uint8_t len;
    
    if(Read_GPIOD_PIN4 == 0){
        delay_ms(20);
        if(Read_GPIOD_PIN4 == 0){
            //Set_LT8920_MAC(0,0,0,0,0,0);
            //delay_ms(20);
            Set_LT8920_RX_FREQ(LT8920_SEND_FREQUENCY);     //����Ƶ��0x03
            while(1){
                PAout(3,1);
                if(LT8920_PKT_IN == 1)//����Ƿ���յ�����
                {
                    SPI_ReadReg(50);
                    len=RegH;//��ȡ������  ��󳤶�0XFF
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
                    if((RegH&0x80)==0)  //CRC�޴��� ��һ���������󣬼Ĵ��� Reg48 bit15 λ CRC_ERROR �����Զ��� 1�����´ο�ʼ RX �� TX ʱ�����������
                    {   
                        PAout(3,1);
                        //Set_LT8920_MAC(config_lt8920[0],config_lt8920[1],config_lt8920[2],config_lt8920[3],config_lt8920[4],config_lt8920[5]);
                        //���浽EEPROM
                        WriteEEPROM((uint8_t *)config_lt8920,len);
                        PAout(3,0);
                        break;
                    }
                    SPI_WriteReg(52, 0x80, 0x80); //��� RXTX
                    SPI_WriteReg(7, 0x00, (0x80|req));  //����ģʽ
                }
            }
        }
    }
}
#endif







