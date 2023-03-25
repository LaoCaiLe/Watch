#include "task_key.h"
#include "Scene.h"
#include "led.h"
#include "delay.h"

uint8_t Key;
bool key_mode=false;

struct ButtonTask *MenuScene = NULL;
struct ButtonTask Scene_Select = { Select_KeyFir_Func,     Select_KeySec_Func,     Select_KeyCancel_Func};
struct ButtonTask Scene_MainScence = { Main_KeyFir_Func,       Main_KeySec_Func,       Main_KeyCancel_Func};
struct ButtonTask Scene_Alarm = { Alarm_KeyFir_Func,      Alarm_KeySec_Func,      Alarm_KeyCancel_Func};
struct ButtonTask Scene_Lighting = { Lighting_KeyFir_Func,   Lighting_KeySec_Func,   Lighting_KeyCancel_Func};
struct ButtonTask Scene_Game = {  Game_KeyFir_Func,       Game_KeySec_Func,       Game_KeyCancel_Func};
struct ButtonTask Scene_Timer = { Timer_KeyFir_Func,      Timer_KeySec_Func,      Timer_KeyCancel_Func};
struct ButtonTask Scene_Setting = { Setting_KeyFir_Func,    Setting_KeySec_Func,    Setting_KeyCancel_Func};

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=KEY_DOWN_Pin|KEY_LEFT_Pin|KEY_RIGHT_Pin|KEY_UP_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;	//上拉输入
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/*******************************************************************************
* 函 数 名         : KEY_Scan
* 函数功能		   : 按键扫描检测
* 输    入         : mode=0:单次按下按键
					 mode=1：连续按下按键
* 输    出         : 0：未有按键按下
					 KEY_UP：K_UP键按下
					 KEY_DOWN：K_DOWN键按下
					 KEY_LEFT：K_LEFT键按下
					 KEY_RIGHT：K_RIGHT键按下
*******************************************************************************/

u8 KEY_Scan(u8 mode)
{
	static u8 k=1;
	if(k==1&&(K_UP==0||K_DOWN==0||K_LEFT==0||K_RIGHT==0)) //任意一个按键按下
	{
		delay_ms(12);  //消抖
	
		k=0;
		if(K_UP==0)
		{
			return KEY_UP; 
		}
		else if(K_DOWN==0)
		{
			return KEY_DOWN; 
		}
		else if(K_LEFT==0)
		{
			return KEY_LEFT; 
		}
		else if(K_RIGHT==0)
		{
			return KEY_RIGHT;
		}
	}
	else if(K_UP==1&&K_DOWN==1&&K_LEFT==1&&K_RIGHT==1)    //无按键按下
	{
		k=1;
	}
	if(mode==1) //连续按键按下
	{
		k=1;
	}
	return 0;
}


void key_task(lv_task_t *t)
{
    Key = KEY_Scan(key_mode);
    
    switch (Key)
    {
        case KEY_LEFT:
            MenuScene->KeyFir_Func();
            break;
        case KEY_DOWN:
            MenuScene->KeySec_Func();
            break;
        case KEY_RIGHT:
            MenuScene->KeyCancel_Func();
            break;
    }
}

