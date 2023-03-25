#ifndef _TASK_BAT_H
#define _TASK_BAT_H

#include "stm32f4xx.h"
#include "sys.h"
#include "../GUI/lvgl/lvgl.h"
#include "Scene.h"

// #define Is_charging PAin(0)   //充电检测
// LV_IMG_DECLARE(img_battery_0);
// LV_IMG_DECLARE(img_battery_1);
// LV_IMG_DECLARE(img_battery_2);
// LV_IMG_DECLARE(img_battery_3);
// LV_IMG_DECLARE(img_battery_4);

void Bat_init(void);
void bat_task(lv_task_t *t);
int Get_power(int ch);
u16 Get_Adc_Average(u8 ch, u8 times);

#endif // DEBUG