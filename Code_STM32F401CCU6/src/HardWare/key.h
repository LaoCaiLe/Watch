#ifndef _key_H
#define _key_H


#include "sys.h"
 
#define KEY_LEFT_Pin    GPIO_Pin_13    //����K_LEFT�ܽ�
#define KEY_DOWN_Pin    GPIO_Pin_12    //����K_DOWN�ܽ�
#define KEY_RIGHT_Pin   GPIO_Pin_14   //����K_RIGHT�ܽ�
#define KEY_UP_Pin      GPIO_Pin_15  //����KEY_UP�ܽ�



//ʹ��λ��������
#define K_UP PCin(15)
#define K_DOWN PBin(12)
#define K_LEFT PBin(13)
#define K_RIGHT PCin(14)

//ʹ�ö�ȡ�ܽ�״̬�⺯������ 
//#define K_UP      GPIO_ReadInputDataBit(KEY_UP_Port,KEY_UP_Pin)
//#define K_DOWN    GPIO_ReadInputDataBit(KEY_Port,KEY_DOWN_Pin)
//#define K_LEFT    GPIO_ReadInputDataBit(KEY_Port,KEY_LEFT_Pin)
//#define K_RIGHT   GPIO_ReadInputDataBit(KEY_Port,KEY_RIGHT_Pin)


//�����������ֵ  
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4  



void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
