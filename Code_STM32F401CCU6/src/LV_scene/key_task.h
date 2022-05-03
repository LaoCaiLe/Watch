#ifndef KEY_TASK_H
#define KEY_TASK_H
#include "../GUI/lvgl/lvgl.h"

typedef void (*tKeyFunc)(void);

struct ButtonTask
{    
    tKeyFunc KeyFir_Func;       //按键一函数
    tKeyFunc KeySec_Func;       //按键二函数
    tKeyFunc KeyCancel_Func;    //按键三函数
    lv_obj_t *obj;              //当前任务obj
};

extern struct ButtonTask *MenuTask;

extern struct ButtonTask Task_Select;
extern struct ButtonTask Task_MainScence;
extern struct ButtonTask Task_Timer;
extern struct ButtonTask Task_Lighting;
extern struct ButtonTask Task_Alarm;
extern struct ButtonTask Task_Setting;

extern bool key_mode;
void key_thread(lv_task_t *t);

#endif