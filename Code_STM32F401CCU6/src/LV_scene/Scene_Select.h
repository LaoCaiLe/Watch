#ifndef __SCENE_SELECT_H
#define __SCENE_SELECT_H
#include "../GUI/lvgl/lvgl.h"
#include "stm32f4xx.h"
#ifdef __cplusplus
 extern "C"{
#endif // DEBUG

typedef struct 
{
    const void *img_addr;
    const char *title;
    lv_obj_t *img;
    struct ButtonTask *task_t;

}IMG_t;

extern IMG_t img_array[];

void selection_init(void);
void background_init(void);
void redline_init(void);
void img_init(void);
void objmask_init(void);
void title_init(void);

#ifdef __cplusplus
 }
#endif // DEBUG

#endif // !__APP_SELECT_H
