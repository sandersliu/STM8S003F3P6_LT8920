/********************************************************************
*@file        lt8920.c
*@author      Woody      QQ：2490006131
*@version     V1.0
*@date        2016-10-14
*@brief       lt8920  2.4G模块初始化
*******************************************************************/
#include "includes.h"

//Used to store the Registor Value which is read.
unsigned char RegH;
unsigned char RegL;  

uint8_t RxBuffer[USART_REC_LEN];//无线接收数组同步串口接收长度

/*******************************************************************************
*函 数 名: SPI_LT8920_Init
*功能说明: 使能LT8920芯片的片选引脚CS--PC4  RST--PA3 PKT--PC3
*形    参：无
*返 回 值: 无
*******************************************************************************/
void LT8920_GPIO_Init(void)
{ 
    GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);        //PKT--PC3
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);   //CS--PC4
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);   //RST--PD3
    
    LT8920_CS_HIGH();        //初始化LT8920芯片片选引脚所接的I/O引脚，并输出高电平
}
/*******************************************************************************
*函 数 名: Set_LT8920_MAC
*功能说明: 设置通讯mac地址 即时修改
*形    参：无
*返 回 值: 无
*******************************************************************************/
void Set_LT8920_MAC(uint8_t a1,uint8_t a2,uint8_t a3,uint8_t a4,uint8_t a5,uint8_t a6)
{
    SPI_WriteReg(36, 0x4d, 0x4d );  
    SPI_WriteReg(37, a1, a2 );
    SPI_WriteReg(38, a3, a4 );
    SPI_WriteReg(39, a5, a6 );
}


/*******************************************************************************
*函 数 名: LT8900_Init
*功能说明: LT8920芯片初始化函数
*形    参：无
*返 回 值: 无
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
    //f = 2402Mhz+RF_PLL_CH_NO[6:0] 设置RF频率 推荐值0x0030
    SPI_WriteReg( 7, 0x00, 0x00 );
    SPI_WriteReg( 8, 0x6c, 0x90 ); 
    //最大输出功率Reg09 = 0X4800
    //通用输出功率Reg09 = 0X1840
    //最小输出功率Reg09 = 0X1FC0
    SPI_WriteReg( 9, 0x48, 0x00 );
    //BIT0 1:开启晶体振荡器    0:关闭晶体振荡器  推荐值0x7ffd
    SPI_WriteReg(10, 0x7f, 0xfd ); 
    //BIT8  1:关闭RSSI   0:开启RSSI   推荐值0x0008    上电复位值0x4008
    SPI_WriteReg(11, 0x00, 0x08 );
    //推荐值0x48bd    上电复位值0x0000
    SPI_WriteReg(12, 0x00, 0x00 );
    //推荐值0x48bd    上电复位值0x4855
    SPI_WriteReg(13, 0x48, 0xbd ); 
    //推荐值0x00ff    上电复位值0xc0ff  
    SPI_WriteReg(22, 0x00, 0xff );
    //在TX/RX开启前重新校准VCO    在TX/RX开启前不校准VCO 
    SPI_WriteReg(23, 0x80, 0x05 );
    //推荐值0x0067    上电复位值0x307b
    SPI_WriteReg(24, 0x00, 0x67 );
    //推荐值0x1659    上电复位值0x1659
    SPI_WriteReg(25, 0x16, 0x59 );
    //推荐值0x19e0    上电复位值0x1833
    SPI_WriteReg(26, 0x19, 0xe0 );
    //推荐值0x1300    上电复位值0x9100
    SPI_WriteReg(27, 0x13, 0x00 );
    //推荐值0x1800    上电复位值0x1800
    SPI_WriteReg(28, 0x18, 0x00 );
    //推荐值0x4800    上电复位值0x1806
    SPI_WriteReg(32, 0x48, 0x00 );      //8920在62.5kbps下同步头只能是32或16bit
    //推荐值0x3fc7    上电复位值0x6307
    SPI_WriteReg(33, 0x3f, 0xc7 );
    //推荐值0x2000   上电复位值0x030b
    SPI_WriteReg(34, 0x20, 0x00 );
    //推荐值0x0300   上电复位值1300 在auto-ack 功能开启时，最多的重发次数设置为3时，为重发2次
    SPI_WriteReg(35, 0x05, 0x00 );	 //重发次数4次
    //为每个无线网络选择唯一的同步字，类似于MAC地址
    /*{
    SPI_WriteReg(36, 0x03, 0x80 );  
    SPI_WriteReg(37, 0x03, 0x80 );
    SPI_WriteReg(38, 0x5a, 0x5a );
    SPI_WriteReg(39, 0x03, 0x80 );
}*/
    Set_LT8920_MAC(0,0,0,0,0,0);
    //Set_LT8920_MAC(0x03,0x80,0x5a,0x5a,0x03,0x80);
    //配置FIFO 标志同步阈值
    SPI_WriteReg(40, 0x44, 0x02 );
    //推荐值0xb000   上电复位值0xb800 CRC校验开关 1：开启  0：关闭  BIT13 表示payload长度  
    //如果要写8个byte有效字节，那第一个字节应写8，总长9 41[13] = 1 ,payload的第一个byte表示包长度，最大长度255
    SPI_WriteReg(41, 0xb8, 0x00 );	/*CRC is ON; scramble is OFF; AUTO_ACK is ON*/
    //推荐值0xfdb0   上电复位值0xfd6b  RSSI 扫描的信道数量，RSSI值将保留在FIFO中
    SPI_WriteReg(42, 0xfd, 0xb0 );	/*等待RX_ACK时间 176us*/
    //推荐值/上电复位值 0x000f  初始化RSSI扫描
    SPI_WriteReg(43, 0x00, 0x0f );
    //推荐值0x1000   上电复位值0x0100   初始化数据传输率 62.5kbps
    SPI_WriteReg(44, 0x10, 0x00 );
    //推荐值0x0552   上电复位值0x0080
    SPI_WriteReg(45, 0x05, 0x52 );//62.5k
    // MCU 读取FIFO数据接口
    SPI_WriteReg(50, 0x00, 0x00 );
    delay_ms(100);
}

/*******************************************************************************
*函 数 名: SPI_WriteReg
*功能说明: SPI写16位寄存器
*形    参：addr地址 H高字节 L低字节
*返 回 值: 无
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
*函 数 名: SPI_ReadReg
*功能说明: SPI读8位寄存器
*形    参：addr要读取的寄存器地址值
*返 回 值: 无
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
*函 数 名: Check_LT8920
*功能说明: 检测LT8920是否在线 常量为不在线 错误，闪烁五次为正常
*形    参：无
*返 回 值: 无
*******************************************************************************/
void Check_LT8920(void)
{
    delay_ms(10);
    SPI_ReadReg(40); //读出无线模块寄存器的值检查硬件读写时序是否正确
    if((RegH==0x44)&&(RegL==0x02))  //判断连接配置无线模块是否正确
    {
        for(uint8_t i=0;i<5;i++)
        {
            PAout(3,1);//为1亮
            delay_ms(40);
            PAout(3,0);
            delay_ms(40); 
        }
    }else{
        PAout(3,1);//为1亮
        while(1);
    }
}
//发送配置
void Set_LT8920_TX_FREQ(uint8_t len,uint8_t* buffer,uint8_t freq)
{
    uint8_t len_t;
    uint16_t n=0;
    
    SPI_WriteReg(7, 0x00, 0x00);      //关闭发射器
    SPI_WriteReg(52, 0x80, 0x80);     //清空接收、发送FIFO数据
    if(buffer){
        SPI_WriteReg(50, len,buffer[0]);    //5表示发送长度包括0,0X55,0X66,0X77,0X88，
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
        SPI_WriteReg(7, 0x01, freq);   //发送 频率0x03
    }
}


//接收配置
void Set_LT8920_RX_FREQ(uint8_t freq)
{
    SPI_WriteReg(7, 0x00, 0x00);  //设定模式
    SPI_WriteReg(52, 0x80, 0x80); //清空 RXTX
    SPI_WriteReg(7, 0x00, (0x80|freq));  //接收模式
    delay_us(20);
}

/*******************************************************************************
*函 数 名: LT8920_TX_Control
*功能说明: 数据发送函数
*形    参：无
*返 回 值: 无
*******************************************************************************/
void LT8920_TX_Control(uint8_t req)
{
    uint16_t j;
    uint8_t len;
    
    if(USART_RX_STA&0x80)
    {
        len = USART_RX_STA&0x3f;//得到此次接收到的数据长度
        Set_LT8920_TX_FREQ(len,(uint8_t *)USART_RX_BUF,req); //发射频率0x03
        USART_RX_STA=0;
        j = 10000; 
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
            delay_us(10);
            PAout(3,0);
        }
    }
}
/*******************************************************************************
*函 数 名: LT8920_RX_Control
*功能说明: 数据接收函数
*形    参：无
*返 回 值: 无
*******************************************************************************/
void LT8920_RX_Control(uint8_t req)
{
    uint8_t i,len,len_t;
    uint16_t m;
    
    if(LT8920_PKT_IN == 1)//检查是否接收到数据
    {
        memset(RxBuffer,0,strlen((char *)RxBuffer));  //清空接收数据
        SPI_ReadReg(50);
        len=RegH;//读取包长度  最大长度0XFF
        if((len&1) == 0) len_t=len>>1;
        else len_t=(len-1)>>1;
        RxBuffer[0] = RegL; 
        m=1;
        for(i=0;i<len_t;i++)
        {            
            SPI_ReadReg(50);  //读取数据
            if((i == (len_t-1))&&((len&1) == 0)){
                RxBuffer[m++]=RegH;
            }else{
                RxBuffer[m++]=RegH;
                RxBuffer[m++]=RegL;
            }
            if(i >= 64)         //最长64个字节
                break;
        }
        RxBuffer[m] = '\0';
        SPI_ReadReg(48);     //Test CRC
        if((RegH&0x80)==0)  //CRC无错误 ，一旦发生错误，寄存器 Reg48 bit15 位 CRC_ERROR 将被自动置 1，在下次开始 RX 或 TX 时它将被清除。
        {   
            PAout(3,1);
#if DEBUG_PRINTF  
            printf("%s\r\n",(char *)RxBuffer);  //串口打印数据
#else
            u1printf((char *)RxBuffer);  //串口打印数据
#endif
            PAout(3,0);
        }else  {
            //printf("Data reception CRC check ERROR!\r\n");  //接收错误提示
            LT8920_RST_LOW();
            delay_ms(2);
            LT8920_RST_HIGH();
            delay_ms(5);
        }
        SPI_WriteReg(52, 0x80, 0x80); //清空 RXTX
        SPI_WriteReg(7, 0x00, (0x80|req));  //接收模式
    }
}




