#ifndef _SCENE_ALARM_H
#define _SCENE_ALARM_H

#include "lv_port_disp.h"
#include "Scene.h"
#include "stm32f4xx.h"

void Alarm_init(void);
void back_ground_init(void);
void title_init(void);
void redline_init(void);
void roller_init(void);
void switch_init(void);
void text_init(void);
void rect_init(void);

#endif // !_SCENE_ALARM_H