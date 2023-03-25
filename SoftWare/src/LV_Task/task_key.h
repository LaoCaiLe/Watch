#ifndef _TASKKEY_H
#define _TASKKEY_H

#include "../GUI/lvgl/lvgl.h"
#include "sys.h"

#define KEY_LEFT_Pin    GPIO_Pin_14    //定义K_LEFT管脚
#define KEY_DOWN_Pin    GPIO_Pin_13    //定义K_DOWN管脚
#define KEY_RIGHT_Pin   GPIO_Pin_12 //定义K_RIGHT管脚
#define KEY_UP_Pin      GPIO_Pin_6  //定义KEY_UP管脚
// #define KEY_LEFT_Pin    GPIO_Pin_13    //定义K_LEFT管脚
// #define KEY_DOWN_Pin    GPIO_Pin_12    //定义K_DOWN管脚
// #define KEY_RIGHT_Pin   GPIO_Pin_7  //定义K_RIGHT管脚


//使用位操作定义
#define K_UP PBin(6)
#define K_DOWN PBin(13)
#define K_LEFT PBin(14)
#define K_RIGHT PBin(12)

// #define K_DOWN PBin(12)
// #define K_LEFT PBin(13)
// #define K_RIGHT PBin(7)


//定义各个按键值  
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4  


typedef void (*tKeyFunc)(void);
struct ButtonTask
{    
    tKeyFunc KeyFir_Func;       //按键一函数
    tKeyFunc KeySec_Func;       //按键二函数
    tKeyFunc KeyCancel_Func;    //按键三函数
    lv_obj_t *obj;              //当前任务obj
};

extern struct ButtonTask *MenuScene;

extern struct ButtonTask Scene_Select;
extern struct ButtonTask Scene_MainScence;
extern struct ButtonTask Scene_Timer;
extern struct ButtonTask Scene_Lighting;
extern struct ButtonTask Scene_Alarm;
extern struct ButtonTask Scene_Setting;
extern struct ButtonTask Scene_Game;
extern bool key_mode;

void key_task(lv_task_t *t);
void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif