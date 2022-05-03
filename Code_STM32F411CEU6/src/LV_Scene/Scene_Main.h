#ifndef _MAIN_SCENE_H
#define _MAIN_SCENE_H

#include "../GUI/lvgl/lvgl.h"

extern char day_t[7][4];
extern lv_obj_t *img_battery;
extern lv_obj_t *label_step;
extern lv_obj_t *label_temp;
extern lv_obj_t *label_bat; 

void mainMenu_init();
void background_init();
void battery_show();
void timeLabel_show();
void dateLabel_show();
void stepLabel_show();
void tempLabel_show();

#endif
