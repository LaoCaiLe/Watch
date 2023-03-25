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
// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
// 	GPIO_Init(MPU_SCL_GPIO_PORT, &GPIO_InitStructure);
// 	// GPIO_SetBits(MPU_SCL_GPIO_PORT, MPU_SCL_GPIO_PIN);

// 	// GPIO_InitStructure.GPIO_Pin = MPU_SDA_GPIO_PIN;
// 	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
// 	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
// 	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
// 	// GPIO_Init(MPU_SDA_GPIO_PORT, &GPIO_InitStructure);
// 	// GPIO_SetBits(MPU_SDA_GPIO_PORT, MPU_SDA_GPIO_PIN);
// }

// void MPU_IIC_Start(void)
// {
// 	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
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
// 	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
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
// 	MPU_IIC_SDA(0);	/* CPU����SDA = 0 */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(1);	/* CPU����1��ʱ�� */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(0);
// 	MPU_IIC_Delay();
// }

// void MPU_IIC_NAck(void)
// {
// 	MPU_IIC_SCL(0);
// 	MPU_SDA_OUT();
// 	MPU_IIC_SDA(1);	/* CPU����SDA = 1 */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(1);	/* CPU����1��ʱ�� */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(0);
// 	MPU_IIC_Delay();	
// }

// void MPU_IIC_SendByte(u8 _ucByte)
// {
// 	u8 i;

// 	MPU_SDA_OUT();
// 	MPU_IIC_SCL(0);

// 	/* �ȷ����ֽڵĸ�λbit7 */
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
// 			 MPU_IIC_SDA(1); // �ͷ�����
// 		}
// 		_ucByte <<= 1;	/* ����һ��bit */
// 		MPU_IIC_Delay();
// 	}
// }

// u8 MPU_IIC_ReadByte(u8 ack)
// {
// 	u8 i;
// 	u8 value = 0;

// 	MPU_SDA_IN();

// 	/* ������1��bitΪ���ݵ�bit7 */
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

// 	MPU_IIC_SDA(1);	/* CPU�ͷ�SDA���� */
// 	MPU_IIC_Delay();
// 	MPU_IIC_SCL(1);	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
// 	MPU_IIC_Delay();
// 	if (MPU_IIC_SDA_READ())	/* CPU��ȡSDA����״̬ */
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


// //IICдһ���ֽ� 
// //reg:�Ĵ�����ַ data:���� ����ֵ:0,���� ����,����
// u8 MPU_Write_Byte(u8 reg,u8 data) 				 
// { 
//     MPU_IIC_Start(); 
// 	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//����������ַ+д����	
// 	if(MPU_IIC_WaitAck())	//�ȴ�Ӧ��
// 	{
// 		MPU_IIC_Stop();		 
// 		return 1;		
// 	}
//     MPU_IIC_SendByte(reg);	//д�Ĵ�����ַ
//     MPU_IIC_WaitAck();		//�ȴ�Ӧ�� 
// 	MPU_IIC_SendByte(data);//��������
// 	if(MPU_IIC_WaitAck())	//�ȴ�ACK
// 	{
// 		MPU_IIC_Stop();	 
// 		return 1;		 
// 	}		 
//     MPU_IIC_Stop();	 
// 	return 0;
// }
// //IIC��һ���ֽ� 
// //reg:�Ĵ�����ַ ����ֵ:����������
// u8 MPU_Read_Byte(u8 reg)
// {
// 	u8 res;
//     MPU_IIC_Start(); 
// 	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//����������ַ+д����	
// 	MPU_IIC_WaitAck();		//�ȴ�Ӧ�� 
//     MPU_IIC_SendByte(reg);	//д�Ĵ�����ַ
//     MPU_IIC_WaitAck();		//�ȴ�Ӧ��
//     MPU_IIC_Start();
// 	MPU_IIC_SendByte((MPU_ADDR<<1)|1);//����������ַ+������	
//     MPU_IIC_WaitAck();		//�ȴ�Ӧ�� 
// 	res=MPU_IIC_ReadByte(0);//��ȡ����,����nACK 
//     MPU_IIC_Stop();			//����һ��ֹͣ���� 
// 	return res;		
// }
// //IIC����д
// //addr:������ַ reg:�Ĵ�����ַ len:д�볤�� buf:������ ����ֵ:0,���� ����,����
// u8 MPU_Write_Len(u8 addr, u8 reg, u8 len, u8 *buf)
// {
// 	u8 i; 
//     MPU_IIC_Start(); 
// 	MPU_IIC_SendByte((addr<<1)|0);//����������ַ+д����	
// 	if(MPU_IIC_WaitAck())	//�ȴ�Ӧ��
// 	{
// 		MPU_IIC_Stop();		 
// 		return 1;		
// 	}
//     MPU_IIC_SendByte(reg);	//д�Ĵ�����ַ
//     MPU_IIC_WaitAck();		//�ȴ�Ӧ��
// 	for(i=0;i<len;i++)
// 	{
// 		MPU_IIC_SendByte(buf[i]);	//��������
// 		if(MPU_IIC_WaitAck())		//�ȴ�ACK
// 		{
// 			MPU_IIC_Stop();	 
// 			return 1;		 
// 		}		
// 	}    
//     MPU_IIC_Stop();	 
// 	return 0;	
// } 
// //IIC������
// //addr:������ַ reg:�Ĵ�����ַ len:��ȡ���� buf:������ ����ֵ:0,���� ����,����
// u8 MPU_Read_Len(u8 addr, u8 reg, u8 len, u8 *buf)
// { 
//  	MPU_IIC_Start(); 
// 	MPU_IIC_SendByte((addr<<1)|0);//����������ַ+д����	
// 	if(MPU_IIC_WaitAck())	//�ȴ�Ӧ��
// 	{
// 		MPU_IIC_Stop();		 
// 		return 1;		
// 	}
//     MPU_IIC_SendByte(reg);	//д�Ĵ�����ַ
//     MPU_IIC_WaitAck();		//�ȴ�Ӧ��
//     MPU_IIC_Start();
// 	MPU_IIC_SendByte((addr<<1)|1);//����������ַ+������	
//     MPU_IIC_WaitAck();		//�ȴ�Ӧ�� 
// 	while(len)
// 	{
// 		if(len==1)
// 		*buf=MPU_IIC_ReadByte(0);   //������,����nACK 
// 		else 
// 		*buf=MPU_IIC_ReadByte(1);   //������,����ACK  
// 		len--;
// 		buf++; 
// 	}    
//     MPU_IIC_Stop();	//����һ��ֹͣ���� 
// 	return 0;	
// }





  //MPU IIC ��ʱ����
void MPU_IIC_Delay(void)
{
	delay_us(2);
}

//��ʼ��IIC
void MPU_IIC_Init(void)
{			
//   GPIO_InitTypeDef GPIO_InitStructure;
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��PB�˿�ʱ��
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	//�˿�����
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
//   GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(MPU_GPIO_CLK, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = MPU_SCL_GPIO_PIN|MPU_SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(MPU_SCL_GPIO_PORT, &GPIO_InitStructure);
}
//����IIC��ʼ�ź�
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda�����
	MPU_IIC_SDA(1);	  	  
	MPU_IIC_SCL(1);
	MPU_IIC_Delay();
 	MPU_IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda�����
	MPU_IIC_SCL(0);
	MPU_IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	MPU_IIC_SCL(1);  
	MPU_IIC_SDA(1);//����I2C���߽����ź�
	MPU_IIC_Delay();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU_SDA_IN();      //SDA����Ϊ����  
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
	MPU_IIC_SCL(0);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MPU_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	MPU_SDA_OUT(); 	    
    MPU_IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
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
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA����Ϊ����
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
        MPU_IIC_NAck();//����nACK
    else
        MPU_IIC_Ack(); //����ACK   
    return receive;
}



















