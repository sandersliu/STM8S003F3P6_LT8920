/********************************************************************
*@file        lt8920.c
*@author      Woody      QQ��2490006131
*@version     V1.0
*@date        2016-10-14
*@brief       lt8920  2.4Gģ���ʼ��
*******************************************************************/
#include "includes.h"

//Used to store the Registor Value which is read.
unsigned char RegH;
unsigned char RegL;  

uint8_t RxBuffer[USART_REC_LEN];//���߽�������ͬ�����ڽ��ճ���

/*******************************************************************************
*�� �� ��: SPI_LT8920_Init
*����˵��: ʹ��LT8920оƬ��Ƭѡ����CS--PC4  RST--PA3 PKT--PC3
*��    �Σ���
*�� �� ֵ: ��
*******************************************************************************/
void LT8920_GPIO_Init(void)
{ 
    GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);        //PKT--PC3
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);   //CS--PC4
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);   //RST--PD3
    
    LT8920_CS_HIGH();        //��ʼ��LT8920оƬƬѡ�������ӵ�I/O���ţ�������ߵ�ƽ
}
/*******************************************************************************
*�� �� ��: Set_LT8920_MAC
*����˵��: ����ͨѶmac��ַ ��ʱ�޸�
*��    �Σ���
*�� �� ֵ: ��
*******************************************************************************/
void Set_LT8920_MAC(uint8_t a1,uint8_t a2,uint8_t a3,uint8_t a4,uint8_t a5,uint8_t a6)
{
    SPI_WriteReg(36, 0x4d, 0x4d );  
    SPI_WriteReg(37, a1, a2 );
    SPI_WriteReg(38, a3, a4 );
    SPI_WriteReg(39, a5, a6 );
}


/*******************************************************************************
*�� �� ��: LT8900_Init
*����˵��: LT8920оƬ��ʼ������
*��    �Σ���
*�� �� ֵ: ��
*******************************************************************************/
void LT8900_Init(void)
{
    LT8920_RST_LOW();
    delay_ms(2);
    LT8920_RST_HIGH();
    delay_ms(5);
    //  LT8920_PKT_OUT =1;
    SPI_WriteReg( 0, 0x6f, 0xef );  
    SPI_WriteReg( 1, 0x56, 0x81 );
    SPI_WriteReg( 2, 0x66, 0x17 );
    SPI_WriteReg( 4, 0x9c, 0xc9 );
    SPI_WriteReg( 5, 0x66, 0x37 );
    //f = 2402Mhz+RF_PLL_CH_NO[6:0] ����RFƵ�� �Ƽ�ֵ0x0030
    SPI_WriteReg( 7, 0x00, 0x00 );
    SPI_WriteReg( 8, 0x6c, 0x90 ); 
    //����������Reg09 = 0X4800
    //ͨ���������Reg09 = 0X1840
    //��С�������Reg09 = 0X1FC0
    SPI_WriteReg( 9, 0x48, 0x00 );
    //BIT0 1:������������    0:�رվ�������  �Ƽ�ֵ0x7ffd
    SPI_WriteReg(10, 0x7f, 0xfd ); 
    //BIT8  1:�ر�RSSI   0:����RSSI   �Ƽ�ֵ0x0008    �ϵ縴λֵ0x4008
    SPI_WriteReg(11, 0x00, 0x08 );
    //�Ƽ�ֵ0x48bd    �ϵ縴λֵ0x0000
    SPI_WriteReg(12, 0x00, 0x00 );
    //�Ƽ�ֵ0x48bd    �ϵ縴λֵ0x4855
    SPI_WriteReg(13, 0x48, 0xbd ); 
    //�Ƽ�ֵ0x00ff    �ϵ縴λֵ0xc0ff  
    SPI_WriteReg(22, 0x00, 0xff );
    //��TX/RX����ǰ����У׼VCO    ��TX/RX����ǰ��У׼VCO 
    SPI_WriteReg(23, 0x80, 0x05 );
    //�Ƽ�ֵ0x0067    �ϵ縴λֵ0x307b
    SPI_WriteReg(24, 0x00, 0x67 );
    //�Ƽ�ֵ0x1659    �ϵ縴λֵ0x1659
    SPI_WriteReg(25, 0x16, 0x59 );
    //�Ƽ�ֵ0x19e0    �ϵ縴λֵ0x1833
    SPI_WriteReg(26, 0x19, 0xe0 );
    //�Ƽ�ֵ0x1300    �ϵ縴λֵ0x9100
    SPI_WriteReg(27, 0x13, 0x00 );
    //�Ƽ�ֵ0x1800    �ϵ縴λֵ0x1800
    SPI_WriteReg(28, 0x18, 0x00 );
    //�Ƽ�ֵ0x4800    �ϵ縴λֵ0x1806
    SPI_WriteReg(32, 0x48, 0x00 );      //8920��62.5kbps��ͬ��ͷֻ����32��16bit
    //�Ƽ�ֵ0x3fc7    �ϵ縴λֵ0x6307
    SPI_WriteReg(33, 0x3f, 0xc7 );
    //�Ƽ�ֵ0x2000   �ϵ縴λֵ0x030b
    SPI_WriteReg(34, 0x20, 0x00 );
    //�Ƽ�ֵ0x0300   �ϵ縴λֵ1300 ��auto-ack ���ܿ���ʱ�������ط���������Ϊ3ʱ��Ϊ�ط�2��
    SPI_WriteReg(35, 0x05, 0x00 );	 //�ط�����4��
    //Ϊÿ����������ѡ��Ψһ��ͬ���֣�������MAC��ַ
    /*{
    SPI_WriteReg(36, 0x03, 0x80 );  
    SPI_WriteReg(37, 0x03, 0x80 );
    SPI_WriteReg(38, 0x5a, 0x5a );
    SPI_WriteReg(39, 0x03, 0x80 );
}*/
    Set_LT8920_MAC(0,0,0,0,0,0);
    //Set_LT8920_MAC(0x03,0x80,0x5a,0x5a,0x03,0x80);
    //����FIFO ��־ͬ����ֵ
    SPI_WriteReg(40, 0x44, 0x02 );
    //�Ƽ�ֵ0xb000   �ϵ縴λֵ0xb800 CRCУ�鿪�� 1������  0���ر�  BIT13 ��ʾpayload����  
    //���Ҫд8��byte��Ч�ֽڣ��ǵ�һ���ֽ�Ӧд8���ܳ�9 41[13] = 1 ,payload�ĵ�һ��byte��ʾ�����ȣ���󳤶�255
    SPI_WriteReg(41, 0xb8, 0x00 );	/*CRC is ON; scramble is OFF; AUTO_ACK is ON*/
    //�Ƽ�ֵ0xfdb0   �ϵ縴λֵ0xfd6b  RSSI ɨ����ŵ�������RSSIֵ��������FIFO��
    SPI_WriteReg(42, 0xfd, 0xb0 );	/*�ȴ�RX_ACKʱ�� 176us*/
    //�Ƽ�ֵ/�ϵ縴λֵ 0x000f  ��ʼ��RSSIɨ��
    SPI_WriteReg(43, 0x00, 0x0f );
    //�Ƽ�ֵ0x1000   �ϵ縴λֵ0x0100   ��ʼ�����ݴ����� 62.5kbps
    SPI_WriteReg(44, 0x10, 0x00 );
    //�Ƽ�ֵ0x0552   �ϵ縴λֵ0x0080
    SPI_WriteReg(45, 0x05, 0x52 );//62.5k
    // MCU ��ȡFIFO���ݽӿ�
    SPI_WriteReg(50, 0x00, 0x00 );
    delay_ms(100);
}

/*******************************************************************************
*�� �� ��: SPI_WriteReg
*����˵��: SPIд16λ�Ĵ���
*��    �Σ�addr��ַ H���ֽ� L���ֽ�
*�� �� ֵ: ��
*******************************************************************************/
void SPI_WriteReg(unsigned char addr, unsigned char H, unsigned char L)
{
    LT8920_CS_LOW();
    delay_us(1);
    SPI_SendByte(addr);
    delay_us(1);
    SPI_SendByte(H);
    delay_us(1);
    SPI_SendByte(L);
    delay_us(1);
    LT8920_CS_HIGH();
    delay_us(1);
}
/*******************************************************************************
*�� �� ��: SPI_ReadReg
*����˵��: SPI��8λ�Ĵ���
*��    �Σ�addrҪ��ȡ�ļĴ�����ֵַ
*�� �� ֵ: ��
*******************************************************************************/
void SPI_ReadReg(unsigned char addr)
{	
    LT8920_CS_LOW();
    delay_us(1);
    addr |= 0x80;                    //when reading a Register,the Address should be added with 0x80.
    SPI_SendByte(addr);
    delay_us(1);
    RegH = SPI_SendByte(Dummy_Byte);
    delay_us(1);
    RegL = SPI_SendByte(Dummy_Byte);
    delay_us(1);
    LT8920_CS_HIGH();
    delay_us(1);
}
/*******************************************************************************
*�� �� ��: Check_LT8920
*����˵��: ���LT8920�Ƿ����� ����Ϊ������ ������˸���Ϊ����
*��    �Σ���
*�� �� ֵ: ��
*******************************************************************************/
void Check_LT8920(void)
{
    delay_ms(10);
    SPI_ReadReg(40); //��������ģ��Ĵ�����ֵ���Ӳ����дʱ���Ƿ���ȷ
    if((RegH==0x44)&&(RegL==0x02))  //�ж�������������ģ���Ƿ���ȷ
    {
        for(uint8_t i=0;i<5;i++)
        {
            PAout(3,1);//Ϊ1��
            delay_ms(40);
            PAout(3,0);
            delay_ms(40); 
        }
    }else{
        PAout(3,1);//Ϊ1��
        while(1);
    }
}
//��������
void Set_LT8920_TX_FREQ(uint8_t len,uint8_t* buffer,uint8_t freq)
{
    uint8_t len_t;
    uint16_t n=0;
    
    SPI_WriteReg(7, 0x00, 0x00);      //�رշ�����
    SPI_WriteReg(52, 0x80, 0x80);     //��ս��ա�����FIFO����
    if(buffer){
        SPI_WriteReg(50, len,buffer[0]);    //5��ʾ���ͳ��Ȱ���0,0X55,0X66,0X77,0X88��
        if((len&1) == 0) len_t = len>>1;
        else len_t = (len-1)>>1;
        for(uint8_t i = 0;i < len_t;i++){
            if((i == (len_t-1))&&((len&1) == 0)){
                SPI_WriteReg(50,buffer[n+1],0);
            }else{
                SPI_WriteReg(50,buffer[n+1],buffer[n+2]);
                n+=2;
            }
        }
        SPI_WriteReg(7, 0x01, freq);   //���� Ƶ��0x03
    }
}


//��������
void Set_LT8920_RX_FREQ(uint8_t freq)
{
    SPI_WriteReg(7, 0x00, 0x00);  //�趨ģʽ
    SPI_WriteReg(52, 0x80, 0x80); //��� RXTX
    SPI_WriteReg(7, 0x00, (0x80|freq));  //����ģʽ
    delay_us(20);
}

/*******************************************************************************
*�� �� ��: LT8920_TX_Control
*����˵��: ���ݷ��ͺ���
*��    �Σ���
*�� �� ֵ: ��
*******************************************************************************/
void LT8920_TX_Control(uint8_t req)
{
    uint16_t j;
    uint8_t len;
    
    if(USART_RX_STA&0x80)
    {
        len = USART_RX_STA&0x3f;//�õ��˴ν��յ������ݳ���
        Set_LT8920_TX_FREQ(len,(uint8_t *)USART_RX_BUF,req); //����Ƶ��0x03
        USART_RX_STA=0;
        j = 10000; 
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
            delay_us(10);
            PAout(3,0);
        }
    }
}
/*******************************************************************************
*�� �� ��: LT8920_RX_Control
*����˵��: ���ݽ��պ���
*��    �Σ���
*�� �� ֵ: ��
*******************************************************************************/
void LT8920_RX_Control(uint8_t req)
{
    uint8_t i,len,len_t;
    uint16_t m;
    
    if(LT8920_PKT_IN == 1)//����Ƿ���յ�����
    {
        memset(RxBuffer,0,strlen((char *)RxBuffer));  //��ս�������
        SPI_ReadReg(50);
        len=RegH;//��ȡ������  ��󳤶�0XFF
        if((len&1) == 0) len_t=len>>1;
        else len_t=(len-1)>>1;
        RxBuffer[0] = RegL; 
        m=1;
        for(i=0;i<len_t;i++)
        {            
            SPI_ReadReg(50);  //��ȡ����
            if((i == (len_t-1))&&((len&1) == 0)){
                RxBuffer[m++]=RegH;
            }else{
                RxBuffer[m++]=RegH;
                RxBuffer[m++]=RegL;
            }
            if(i >= 64)         //�64���ֽ�
                break;
        }
        RxBuffer[m] = '\0';
        SPI_ReadReg(48);     //Test CRC
        if((RegH&0x80)==0)  //CRC�޴��� ��һ���������󣬼Ĵ��� Reg48 bit15 λ CRC_ERROR �����Զ��� 1�����´ο�ʼ RX �� TX ʱ�����������
        {   
            PAout(3,1);
#if DEBUG_PRINTF  
            printf("%s\r\n",(char *)RxBuffer);  //���ڴ�ӡ����
#else
            u1printf((char *)RxBuffer);  //���ڴ�ӡ����
#endif
            PAout(3,0);
        }else  {
            //printf("Data reception CRC check ERROR!\r\n");  //���մ�����ʾ
            LT8920_RST_LOW();
            delay_ms(2);
            LT8920_RST_HIGH();
            delay_ms(5);
        }
        SPI_WriteReg(52, 0x80, 0x80); //��� RXTX
        SPI_WriteReg(7, 0x00, (0x80|req));  //����ģʽ
    }
}




