#ifndef SCENE_SETTING_H
#define SCENE_SETTING_H

#include "lv_port_disp.h"
#include "Scene.h"
#include "stm32f4xx.h"

void Setting_init(void);
void back_ground_init(void);
void text_label_init(void);
void rect_init(void);
void timeshow_task(lv_task_t *t);

#endif
