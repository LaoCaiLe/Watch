#include "Scene_Game.h"
#include "Scene.h"
#include "IMG.h"
#include "sys.h"

bool Game_pause = false;
bool Game_start = false;
struct enemy_plane_t enemy_plane[enemy_plane_num];
struct bullet_t bullet[bullet_num];
lv_obj_t *plane;
static float roll,start_roll;

void game_init(void)
{
    back_ground_init();
    imgPlane_init();
    enemy_plane_init();
    bullet_init();
}

void game_start()
{
    Game_pause = false;

    // get_start_roll();
    lv_task_create(task_plane_move, 100, LV_TASK_PRIO_MID, NULL);
    lv_task_create(task_enemy, 1000, LV_TASK_PRIO_MID, NULL);
    lv_task_create(task_file, 200, LV_TASK_PRIO_HIGH, NULL);
    lv_task_create(plane_crash_check, 20, LV_TASK_PRIO_HIGHEST,NULL);
    lv_task_create(bullet_enemy_crash_check, 20, LV_TASK_PRIO_HIGHEST,NULL);
}

void game_reset()
{
    Game_pause = true;
    Game_start = false;

    //飞机复位
    lv_obj_align(plane, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -10);   // 设置对齐

    //敌机复位
    for (int i = 0; i < enemy_plane_num; i++)
        if(enemy_plane[i].Is_exist)
            enemy_reset(&enemy_plane[i]);

    //子弹复位
    for (int i = 0; i < bullet_num;i++)
    {
        if(bullet[i].Is_exist)
        {
            bullet[i].Is_exist = false;
            lv_obj_set_pos(bullet[i].img_bullet, 135, 240);
        }
    }
}
static void back_ground_init(void)
{
    Scene_Game.obj = lv_obj_create(lv_scr_act(),NULL);
    lv_obj_set_style_local_border_opa(Scene_Game.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_bg_color(Scene_Game.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_size(Scene_Game.obj, LV_HOR_RES_MAX, LV_VER_RES_MAX-30);
    lv_obj_align(Scene_Game.obj, NULL, LV_ALIGN_CENTER, 0, 25);
}

//敌机任务
void enemyPlane_task(lv_task_t *t)
{
    if(Game_pause)
        lv_task_del(t);
    struct enemy_plane_t * task_plane = (struct enemy_plane_t * )t->user_data;
    lv_obj_align(task_plane->img_enemy, NULL, LV_ALIGN_IN_TOP_LEFT, lv_obj_get_x(task_plane->img_enemy), lv_obj_get_y(task_plane->img_enemy) + task_plane->speed);
    if(lv_obj_get_y(task_plane->img_enemy) > 240 ||task_plane->Is_exist == false)
    {       
        enemy_reset(task_plane);
        lv_task_del(t);
    }
}


//子弹任务
void bullet_task(lv_task_t *t)
{
    if(Game_pause)
        lv_task_del(t);
    struct bullet_t * task_bullet = (struct bullet_t * )t->user_data;
    lv_obj_align(task_bullet->img_bullet, NULL, LV_ALIGN_IN_TOP_LEFT, lv_obj_get_x(task_bullet->img_bullet), lv_obj_get_y(task_bullet->img_bullet)-bullet_speed);
    if(lv_obj_get_y(task_bullet->img_bullet)<-10 || task_bullet->Is_exist==false)
    {
        
        lv_obj_align(task_bullet->img_bullet, NULL, LV_ALIGN_OUT_TOP_LEFT, 50, 240);
        task_bullet->Is_exist = false;
        lv_task_del(t);
    }
}

//飞机初始化
void imgPlane_init()
{
    plane = lv_img_create(Scene_Game.obj, NULL);	
    lv_img_set_src(plane, &img_plane);
    lv_obj_align(plane, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -10);   // 设置对齐
}
//敌机初始化
void enemy_plane_init()
{
    
    for (int i = 0; i < enemy_plane_num;i++)
    {
        enemy_plane[i].img_enemy = lv_img_create(Scene_Game.obj, NULL);	
        lv_img_set_src(enemy_plane[i].img_enemy, &img_enemy_1);
        lv_obj_align(enemy_plane[i].img_enemy, NULL, LV_ALIGN_OUT_TOP_LEFT, rand()%100, 1);   // 设置对齐
        enemy_plane[i].Is_exist = false;

        enemy_plane[i].start_x = lv_obj_get_x(enemy_plane[i].img_enemy);   
        enemy_plane[i].start_y = lv_obj_get_y(enemy_plane[i].img_enemy);
        enemy_plane[i].speed = rand() %2+3;
    }
}
//子弹初始化
void bullet_init()
{
    for (int i = 0; i < bullet_num;i++)
    {
        bullet[i].img_bullet = lv_img_create(Scene_Game.obj, NULL);
        lv_img_set_src(bullet[i].img_bullet, &img_bullet);
        // lv_obj_align(bullet[i].img_bullet, NULL, LV_ALIGN_OUT_TOP_LEFT, 50, 240);
        lv_obj_set_pos(bullet[i].img_bullet, 135, 240);


        bullet[i].Is_exist = false;
    }
}

//子弹发射
void task_file(lv_task_t *t)
{
    if(Game_pause)
        lv_task_del(t);

    static int index = 0;
    for (; index < bullet_num; index++)
    {
        if(bullet[index].Is_exist==false)
        {
            bullet[index].Is_exist = true;
            break;
        }   
    }
    index %= bullet_num;
    lv_obj_align(bullet[index].img_bullet, plane, LV_ALIGN_IN_TOP_MID, 0, -3);
    lv_task_create(bullet_task, 50, LV_TASK_PRIO_HIGH, &bullet[index]);
}

//敌机出现
void task_enemy(lv_task_t *t)
{
    static int index = 0;
    if(Game_pause)
        lv_task_del(t);

    for (; index < enemy_plane_num;)
    {
        index++;
        if(enemy_plane[index].Is_exist==false)
        {
            enemy_plane[index].Is_exist = true;
            break;
        }   
    }
    index %= enemy_plane_num;

    lv_task_create(enemyPlane_task, 50, LV_TASK_PRIO_MID, &enemy_plane[index]);
}

void get_start_roll()
{
    float temp[10];
    float all=0.0;
    for (int i = 0; i < 10; i++)
    {
        mpu_dmp_get_data(NULL, &temp[i], NULL);
        all += temp[i];
    }
    start_roll = all / 10.0;
}

//陀螺仪控制飞机
void task_plane_move(lv_task_t *t)
{
    if(Game_pause)
        lv_task_del(t);

    mpu_dmp_get_data(NULL, &roll, NULL);
    // if(roll-start_roll<-10)
    if(roll<176&&roll>0)
    {
        if(lv_obj_get_x(plane)>0)
            lv_obj_set_x(plane, lv_obj_get_x(plane) - 10);  //左移
    }
    // else if(roll-start_roll>10)
    else if(roll>-170&&roll<0)
    {
        if(lv_obj_get_x(plane)<135-lv_obj_get_width(plane))
            lv_obj_set_x(plane, lv_obj_get_x(plane) + 10); //右移
    }
}
//敌机我机碰撞检测
void plane_crash_check(lv_task_t *t)
{
    int val1, val2;

    if(Game_pause)
        lv_task_del(t);
    for (int i = 0; i < enemy_plane_num; i++)
    {
        if(enemy_plane[i].Is_exist)
        {
            val1 = lv_obj_get_x(plane) - lv_obj_get_x(enemy_plane[i].img_enemy);
            val2 = lv_obj_get_y(plane) - lv_obj_get_y(enemy_plane[i].img_enemy);
            if((val1<0&&-val1<lv_obj_get_width(plane))||(val1>=0&&val1<lv_obj_get_width(enemy_plane[i].img_enemy )))
            {
                if(val2<-lv_obj_get_height(plane)/2&&val2>-lv_obj_get_height(plane))
                {
                    Game_pause = true;
                    lv_task_create(task_enemy_die, 80, LV_TASK_PRIO_HIGHEST,&enemy_plane[i]);
                }
            }
        }
    }
}

//子弹敌机碰撞检测
void bullet_enemy_crash_check(lv_task_t *t)
{
    int val1, val2;

    if(Game_pause)
        lv_task_del(t);

    for (int i = 0; i < bullet_num; i++)
    {
        if(bullet[i].Is_exist)
        {
            for (int j = 0; j < enemy_plane_num;j++)
            {
                if(enemy_plane[j].Is_exist)
                {
                    val1 = lv_obj_get_x(bullet[i].img_bullet) - lv_obj_get_x(enemy_plane[j].img_enemy);
                    val2 = lv_obj_get_y(bullet[i].img_bullet) - lv_obj_get_y(enemy_plane[j].img_enemy);
                    if((val1<0&&-val1<lv_obj_get_width(bullet[i].img_bullet))||(val1>=0&&val1<lv_obj_get_width(enemy_plane[j].img_enemy )))
                    {
                        if(lv_obj_get_y(bullet[i].img_bullet)<lv_obj_get_y(enemy_plane[j].img_enemy )/*-lv_obj_get_width(enemy_plane[j].img_enemy )/2*/)
                        {
                            lv_task_create(task_enemy_die, 80, LV_TASK_PRIO_HIGHEST,&enemy_plane[j]);
                            lv_obj_set_pos(bullet[i].img_bullet, 135, 240);

                            bullet[i].Is_exist = false;
                        }
                    }
                }
            }
        }
    }

    
}


void task_enemy_die(lv_task_t *t)
{
    static int i = 0;
    struct enemy_plane_t * task_plane = (struct enemy_plane_t * )t->user_data;
    task_plane->Is_exist = false;
    if(i==0)
        lv_img_set_src(task_plane->img_enemy, &img_enemy_2);
    else if(i==2)
        lv_img_set_src(task_plane->img_enemy, &img_enemy_3);
    else if(i==4)
        lv_img_set_src(task_plane->img_enemy, &img_enemy_4);
    else if(i==6)
        lv_img_set_src(task_plane->img_enemy, &img_enemy_5);
    i++;
    if(i==8)
    {
        i = 0;
        enemy_reset(task_plane);
        lv_task_del(t);
    }  
}


void enemy_reset(struct enemy_plane_t * task_plane)
{
    lv_obj_align(task_plane->img_enemy, NULL, LV_ALIGN_OUT_TOP_LEFT, task_plane->start_x, task_plane->start_y);
    lv_img_set_src(task_plane->img_enemy, &img_enemy_1);
    task_plane->Is_exist = false;
}
void Game_KeyFir_Func()
{
    if(!Game_start)
    {
        game_start();
        Game_start = true;
    }
        
}       
void Game_KeySec_Func()
{
    game_reset();
}
void Game_KeyCancel_Func()
{
    game_reset();

    key_mode = false;
    MenuScene = &Scene_Select;
    lv_obj_move_foreground(Scene_Select.obj);                 
}