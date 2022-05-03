#ifndef _SCENE_LIGHTING_H
#define _SCENE_LIGHTING_H

#include "../GUI/lvgl/lvgl.h"
#include "stm32f4xx.h"



extern u16 Bright;

void Lighting_init(void);
void back_ground_init(void);
// void title_init(void);
// void redline_init(void);
void circle_num_init(void);

#endif