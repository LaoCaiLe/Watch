#ifndef _SCENE_GAME_H
#define _SCENE_GAME_H

#include "../GUI/lvgl/lvgl.h"
#include "stm32f4xx.h"

#define enemy_plane_num 25
#define bullet_num 20
#define bullet_speed 5
// typedef struct {
//     lv_obj_t *img_enemy;
//     bool Is_exist;
//     int start_x;
//     int start_y;
//     int speed;
// }enemy_plane_t;

// typedef struct enemy_plane_t *ENEMY;

struct bullet_t
{
    lv_obj_t *img_bullet;
    bool Is_exist;
};

struct enemy_plane_t{
    lv_obj_t *img_enemy;
    bool Is_exist;
    int start_x;
    int start_y;
    int speed;
};

void game_init(void);
void back_ground_init(void);
void imgPlane_init(void);
void enemy_plane_init(void);
void bullet_init(void);

void game_start(void);
void game_reset(void);
void get_start_roll(void);

void enemy_reset(struct enemy_plane_t *task_plane);
void task_enemy_die(lv_task_t *t);
void enemyPlane_task(lv_task_t *t);
void bullet_task(lv_task_t *t);
void task_enemy(lv_task_t *t);
void task_file(lv_task_t *t);
void task_plane_move(lv_task_t *t);
void bullet_enemy_crash_check(lv_task_t *t);
void plane_crash_check(lv_task_t *t);
#endif