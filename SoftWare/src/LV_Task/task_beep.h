#ifndef _TASK_BEEP_H
#define _TASK_BEEP_H

#include "stm32f4xx.h"
#include "../GUI/lvgl/lvgl.h"
#include "sys.h"

#define Beep_Pin GPIO_Pin_13
#define Beep PCout(13)

extern int beep_duty;
extern bool alarm_stop;
void Beep_init(void);
void Beep_charge_task(lv_task_t *t);    //充电音效
void Beep_alarm1_task(lv_task_t *t);    //闹钟音效
void Beep_alarm2_task(lv_task_t *t);    //闹钟音效
void Beep_alarm3_task(lv_task_t *t);    //闹钟音效
void Beep_hour_task(lv_task_t *t);      //整点音效

#endif