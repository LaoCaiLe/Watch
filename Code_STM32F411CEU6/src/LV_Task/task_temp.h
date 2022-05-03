#ifndef _TASK_TEMP_H
#define _TASK_TEMP_H

#include "stm32f4xx.h"
#include "sys.h"
#include "../GUI/lvgl/lvgl.h"

float get_temprature(void);
void temp_task(lv_task_t *t);

#endif // !_TASK_TEMP_H

