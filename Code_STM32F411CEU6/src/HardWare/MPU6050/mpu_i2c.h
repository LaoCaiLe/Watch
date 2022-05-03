#ifndef __MPU_I2C_H
#define __MPU_I2C_H

#include "stm32f4xx.h"
#include "sys.h"
#define  I2C_WR	     0
#define  I2C_RD	     1

//MPU IIC端口定义
#define  MPU_GPIO_CLK           RCC_AHB1Periph_GPIOB
#define  MPU_SCL_GPIO_PORT      GPIOB                                                                                                                                                                      
#define  MPU_SCL_GPIO_PIN       GPIO_Pin_9

#define  MPU_SDA_GPIO_PORT      GPIOB 
#define  MPU_SDA_GPIO_PIN       GPIO_Pin_8

#define  MPU_SCL_PIN_NUMBER     9
#define  MPU_SDA_PIN_NUMBER     8   //GPIO_Pin_8

//IO 输入输出配置

#define  MPU_SDA_PIN_CRLH_RES     ~(3<<MPU_SDA_PIN_NUMBER*2)

#define  MPU_SDA_IN()  {MPU_SDA_GPIO_PORT->MODER&=~(0x03<<MPU_SDA_PIN_NUMBER*2); MPU_SDA_GPIO_PORT->MODER|=0x00<<MPU_SDA_PIN_NUMBER*2;}
#define  MPU_SDA_OUT() {MPU_SDA_GPIO_PORT->MODER&=~(0x03<<MPU_SDA_PIN_NUMBER*2); MPU_SDA_GPIO_PORT->MODER|=0x01<<MPU_SDA_PIN_NUMBER*2;}


// #define  MPU_IIC_SCL(a)  if(a) GPIO_SetBits(MPU_SCL_GPIO_PORT, MPU_SCL_GPIO_PIN);\
//                          else  GPIO_ResetBits(MPU_SCL_GPIO_PORT, MPU_SCL_GPIO_PIN)	
// #define  MPU_IIC_SDA(a)  if(a) GPIO_SetBits(MPU_SDA_GPIO_PORT, MPU_SDA_GPIO_PIN);\
//                          else  GPIO_ResetBits(MPU_SDA_GPIO_PORT, MPU_SDA_GPIO_PIN)
// #define  MPU_IIC_SDA_READ()  GPIO_ReadInputDataBit(MPU_SDA_GPIO_PORT, MPU_SDA_GPIO_PIN)

#define MPU_IIC_SCL(a)     PBout(MPU_SCL_PIN_NUMBER)=a //SCL
#define MPU_IIC_SDA(a)     PBout(MPU_SDA_PIN_NUMBER)=a //SDA	
#define MPU_READ_SDA   	PBin(MPU_SDA_PIN_NUMBER) //SDA	


void MPU_IIC_Init(void);
void MPU_IIC_Start(void);
void MPU_IIC_Stop(void);
void MPU_IIC_Ack(void);
void MPU_IIC_NAck(void);
void MPU_IIC_Send_Byte(u8 _ucByte);
u8 MPU_IIC_Read_Byte(u8 ack);
u8 MPU_IIC_Wait_Ack(void);

u8 MPU_Write_Byte(u8 reg,u8 data);
u8 MPU_Read_Byte(u8 reg);
// u8 MPU_Write_Len(u8 addr, u8 reg, u8 len, u8 *buf);
// u8 MPU_Read_Len(u8 addr, u8 reg, u8 len, u8 *buf);


#endif  //__MPU_I2C_H
