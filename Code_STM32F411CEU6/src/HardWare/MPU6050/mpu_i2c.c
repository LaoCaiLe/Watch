#include "mpu_i2c.h"
#include "mpu6050.h"
#include "delay.h"

// static void MPU_SDA_IN()
// {
//     GPIO_InitTypeDef GPIO_InitStructure;
// 	GPIO_InitStructure.GPIO_Pin = MPU_SDA_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	
// 	GPIO_Init(MPU_SDA_GPIO_PORT, &GPIO_InitStructure);
// }
// static void MPU_SDA_OUT()
// {
//     GPIO_InitTypeDef GPIO_InitStructure;
// 	GPIO_InitStructure.GPIO_Pin = MPU_SDA_GPIO_PIN;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_Init(MPU_SDA_GPIO_PORT, &GPIO_InitStructure);
// }
// static void MPU_IIC_Delay(void)
// {
// 	delay_us(2);
// }

// void MPU_Config(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	RCC_APB2PeriphClockCmd(MPU_GPIO_CLK, ENABLE);	

// 	GPIO_InitStructure.GPIO_Pin = MPU_SCL_GPIO_PIN|MPU_SDA_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
// 	GPIO_Init(MPU_SCL_GPIO_PORT, &GPIO_InitStructure);
// 	// GPIO_SetBits(MPU_SCL_GPIO_PORT, MPU_SCL_GPIO_PIN);

// 	// GPIO_InitStructure.GPIO_Pin = MPU_SDA_GPIO_PIN;
// 	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
// 	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
// 	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
// 	// GPIO_Init(MPU_SDA_GPIO_PORT, &GPIO_InitStructure);
// 	// GPIO_SetBits(MPU_SDA_GPIO_PORT, MPU_SDA_GPIO_PIN);
// }

// void MPU_IIC_Start(void)
// {
// 	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
// 	MPU_SDA_OUT();
// 	MPU_IIC_SDA(1);
// 	MPU_IIC_SCL(1);
// 	MPU_IIC_Delay();
// 	MPU_IIC_SDA(0);
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(0);
// 	MPU_IIC_Delay();
// }

// void MPU_IIC_Stop(void)
// {
// 	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
// 	MPU_SDA_OUT();
// 	MPU_IIC_SCL(0);
// 	MPU_IIC_SDA(0);
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(1);
// 	MPU_IIC_SDA(1);
// 	MPU_IIC_Delay();
// }

// void MPU_IIC_Ack(void)
// {
// 	MPU_IIC_SCL(0);
// 	MPU_SDA_OUT();
// 	MPU_IIC_SDA(0);	/* CPU驱动SDA = 0 */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(1);	/* CPU产生1个时钟 */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(0);
// 	MPU_IIC_Delay();
// }

// void MPU_IIC_NAck(void)
// {
// 	MPU_IIC_SCL(0);
// 	MPU_SDA_OUT();
// 	MPU_IIC_SDA(1);	/* CPU驱动SDA = 1 */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(1);	/* CPU产生1个时钟 */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(0);
// 	MPU_IIC_Delay();	
// }

// void MPU_IIC_SendByte(u8 _ucByte)
// {
// 	u8 i;

// 	MPU_SDA_OUT();
// 	MPU_IIC_SCL(0);

// 	/* 先发送字节的高位bit7 */
// 	for (i = 0; i < 8; i++)
// 	{		
// 		if (_ucByte & 0x80)
// 		{
// 			MPU_IIC_SDA(1);
// 		}
// 		else
// 		{
// 			MPU_IIC_SDA(0);
// 		}
// 		MPU_IIC_Delay();
// 		MPU_IIC_SCL(1);
// 		MPU_IIC_Delay();	
// 		MPU_IIC_SCL(0);
// 		if (i == 7)
// 		{
// 			 MPU_IIC_SDA(1); // 释放总线
// 		}
// 		_ucByte <<= 1;	/* 左移一个bit */
// 		MPU_IIC_Delay();
// 	}
// }

// u8 MPU_IIC_ReadByte(u8 ack)
// {
// 	u8 i;
// 	u8 value = 0;

// 	MPU_SDA_IN();

// 	/* 读到第1个bit为数据的bit7 */
// 	for (i = 0; i < 8; i++)
// 	{
// 		value <<= 1;
// 		MPU_IIC_SCL(0);
// 		MPU_IIC_Delay();
// 		MPU_IIC_SCL(1);
// 		MPU_IIC_Delay();
// 		if (MPU_IIC_SDA_READ())
// 		{
// 			value++;
// 		}
// 		MPU_IIC_SCL(0);
// 		MPU_IIC_Delay();
// 	}
// 	if(ack==0)
// 		MPU_IIC_NAck();
// 	else
// 		MPU_IIC_Ack();
// 	return value;
// }

// u8 MPU_IIC_WaitAck(void)
// {
// 	u8 re;

// 	MPU_SDA_IN();

// 	MPU_IIC_SDA(1);	/* CPU释放SDA总线 */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(1);	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
// 	MPU_IIC_Delay();
// 	if (MPU_IIC_SDA_READ())	/* CPU读取SDA口线状态 */
// 	{
// 		re = 1;
// 	}
// 	else
// 	{
// 		re = 0;
// 	}
// 	MPU_IIC_SCL(0);
// 	MPU_IIC_Delay();
// 	return re;
// }


// //IIC写一个字节 
// //reg:寄存器地址 data:数据 返回值:0,正常 其他,错误
// u8 MPU_Write_Byte(u8 reg,u8 data) 				 
// { 
//     MPU_IIC_Start(); 
// 	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
// 	if(MPU_IIC_WaitAck())	//等待应答
// 	{
// 		MPU_IIC_Stop();		 
// 		return 1;		
// 	}
//     MPU_IIC_SendByte(reg);	//写寄存器地址
//     MPU_IIC_WaitAck();		//等待应答 
// 	MPU_IIC_SendByte(data);//发送数据
// 	if(MPU_IIC_WaitAck())	//等待ACK
// 	{
// 		MPU_IIC_Stop();	 
// 		return 1;		 
// 	}		 
//     MPU_IIC_Stop();	 
// 	return 0;
// }
// //IIC读一个字节 
// //reg:寄存器地址 返回值:读到的数据
// u8 MPU_Read_Byte(u8 reg)
// {
// 	u8 res;
//     MPU_IIC_Start(); 
// 	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
// 	MPU_IIC_WaitAck();		//等待应答 
//     MPU_IIC_SendByte(reg);	//写寄存器地址
//     MPU_IIC_WaitAck();		//等待应答
//     MPU_IIC_Start();
// 	MPU_IIC_SendByte((MPU_ADDR<<1)|1);//发送器件地址+读命令	
//     MPU_IIC_WaitAck();		//等待应答 
// 	res=MPU_IIC_ReadByte(0);//读取数据,发送nACK 
//     MPU_IIC_Stop();			//产生一个停止条件 
// 	return res;		
// }
// //IIC连续写
// //addr:器件地址 reg:寄存器地址 len:写入长度 buf:数据区 返回值:0,正常 其他,错误
// u8 MPU_Write_Len(u8 addr, u8 reg, u8 len, u8 *buf)
// {
// 	u8 i; 
//     MPU_IIC_Start(); 
// 	MPU_IIC_SendByte((addr<<1)|0);//发送器件地址+写命令	
// 	if(MPU_IIC_WaitAck())	//等待应答
// 	{
// 		MPU_IIC_Stop();		 
// 		return 1;		
// 	}
//     MPU_IIC_SendByte(reg);	//写寄存器地址
//     MPU_IIC_WaitAck();		//等待应答
// 	for(i=0;i<len;i++)
// 	{
// 		MPU_IIC_SendByte(buf[i]);	//发送数据
// 		if(MPU_IIC_WaitAck())		//等待ACK
// 		{
// 			MPU_IIC_Stop();	 
// 			return 1;		 
// 		}		
// 	}    
//     MPU_IIC_Stop();	 
// 	return 0;	
// } 
// //IIC连续读
// //addr:器件地址 reg:寄存器地址 len:读取长度 buf:数据区 返回值:0,正常 其他,错误
// u8 MPU_Read_Len(u8 addr, u8 reg, u8 len, u8 *buf)
// { 
//  	MPU_IIC_Start(); 
// 	MPU_IIC_SendByte((addr<<1)|0);//发送器件地址+写命令	
// 	if(MPU_IIC_WaitAck())	//等待应答
// 	{
// 		MPU_IIC_Stop();		 
// 		return 1;		
// 	}
//     MPU_IIC_SendByte(reg);	//写寄存器地址
//     MPU_IIC_WaitAck();		//等待应答
//     MPU_IIC_Start();
// 	MPU_IIC_SendByte((addr<<1)|1);//发送器件地址+读命令	
//     MPU_IIC_WaitAck();		//等待应答 
// 	while(len)
// 	{
// 		if(len==1)
// 		*buf=MPU_IIC_ReadByte(0);   //读数据,发送nACK 
// 		else 
// 		*buf=MPU_IIC_ReadByte(1);   //读数据,发送ACK  
// 		len--;
// 		buf++; 
// 	}    
//     MPU_IIC_Stop();	//产生一个停止条件 
// 	return 0;	
// }





  //MPU IIC 延时函数
void MPU_IIC_Delay(void)
{
	delay_us(2);
}

//初始化IIC
void MPU_IIC_Init(void)
{			
//   GPIO_InitTypeDef GPIO_InitStructure;
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	//端口配置
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
//   GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(MPU_GPIO_CLK, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = MPU_SCL_GPIO_PIN|MPU_SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(MPU_SCL_GPIO_PORT, &GPIO_InitStructure);
}
//产生IIC起始信号
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda线输出
	MPU_IIC_SDA(1);	  	  
	MPU_IIC_SCL(1);
	MPU_IIC_Delay();
 	MPU_IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda线输出
	MPU_IIC_SCL(0);
	MPU_IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	MPU_IIC_SCL(1);  
	MPU_IIC_SDA(1);//发送I2C总线结束信号
	MPU_IIC_Delay();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU_SDA_IN();      //SDA设置为输入  
	MPU_IIC_SDA(1);MPU_IIC_Delay();	   
	MPU_IIC_SCL(1);MPU_IIC_Delay();	 
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	MPU_IIC_SCL(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL(0);
	MPU_SDA_OUT();
	MPU_IIC_SDA(0);
	MPU_IIC_Delay();
	MPU_IIC_SCL(1);
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);
}
//不产生ACK应答		    
void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL(0);
	MPU_SDA_OUT();
	MPU_IIC_SDA(1);
	MPU_IIC_Delay();
	MPU_IIC_SCL(1);
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void MPU_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	MPU_SDA_OUT(); 	    
    MPU_IIC_SCL(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        // MPU_IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			MPU_IIC_SDA(1);
		else
			MPU_IIC_SDA(0);
		txd<<=1; 	  
		MPU_IIC_SCL(1);
		MPU_IIC_Delay(); 
		MPU_IIC_SCL(0);	
		MPU_IIC_Delay();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        MPU_IIC_SCL(0); 
        MPU_IIC_Delay();
		MPU_IIC_SCL(1);
        receive<<=1;
        if(MPU_READ_SDA)receive++;   
		MPU_IIC_Delay(); 
    }					 
    if (!ack)
        MPU_IIC_NAck();//发送nACK
    else
        MPU_IIC_Ack(); //发送ACK   
    return receive;
}



















