/********************************************************************
*@file        led.c
*@author      Woody      QQ��2490006131
*@version     V1.0
*@date        2016-10-14
*@brief       led�Ƴ�ʼ��
*******************************************************************/
#include "includes.h"



void LED_Init(void)
{       
    //����LED�Ĺܽ�Ϊ���ģʽ
    GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST );  //LED
    PAout(3,0);
}



