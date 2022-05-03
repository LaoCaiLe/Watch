
#include "Scene.h"
#include "Scene_Select.h"
#include "Task.h"
/*
闹钟
秒表
时间调整
背光
游戏
设置
*/

uint8_t Index=0;//当前下标
uint8_t img_interval = 70;//图片间隔

static lv_obj_t *img_cont;  //图片容器
static lv_anim_t a;         //动画对象
static lv_obj_t *title_label;   //标题标题
static lv_obj_t *om;        //蒙版


LV_IMG_DECLARE(img_alarm);
LV_IMG_DECLARE(img_lighting);
LV_IMG_DECLARE(img_setting);
LV_IMG_DECLARE(img_timer);
LV_IMG_DECLARE(img_game);
LV_IMG_DECLARE(img_run);

IMG_t img_array[] =
{
        
    {.img_addr = &img_alarm,    .title = "Alarm",     .task_t = &Scene_Alarm },
    {.img_addr = &img_lighting, .title = "Lighting",  .task_t = &Scene_Lighting},
    {.img_addr = &img_game,     .title = "Game",      .task_t = &Scene_Game },
    {.img_addr = &img_timer,    .title = "Timer",     .task_t = &Scene_Timer },
    {.img_addr = &img_setting,  .title = "Setting",   .task_t = &Scene_Setting }
};
#define Selection_Num sizeof(img_array)/sizeof(img_array[0])



void selection_init(void)
{
    background_init();
    title_init();
    redline_init();
    objmask_init();
    img_init();
}

//背景设置
static void background_init()
{
    Scene_Select.obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_style_local_border_opa(Scene_Select.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_bg_color(Scene_Select.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_size(Scene_Select.obj, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_obj_align(Scene_Select.obj, NULL, LV_ALIGN_CENTER, 0, 0);
}

//添加标题label
static void title_init()
{    
    //顶部字体style
    static lv_style_t font_style;
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    //添加字体
    title_label = lv_label_create(Scene_Select.obj, NULL);
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(title_label, 135, 50);
    lv_obj_add_style(title_label, LV_OBJ_PART_MAIN, &font_style);   
    lv_label_set_align(title_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(title_label, Scene_Select.obj, LV_ALIGN_IN_TOP_MID, 0, 5);
    lv_label_set_text_fmt(title_label, "%s", img_array[Index].title);
}

//设置红线
void redline_init()
{
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 4);
    lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, ENABLE);

    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {5, 5}, {120, 5} };
    lv_obj_t* line1 = lv_line_create(Scene_Select.obj, NULL);
    lv_obj_add_style(line1, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
    lv_line_set_points(line1, line_points, sizeof(line_points)/sizeof(lv_point_t));     /*Set the points*/
    lv_obj_align(line1, NULL, LV_ALIGN_IN_TOP_MID, 0, 30);
}

//创建蒙版
void objmask_init()
{    
    om = lv_objmask_create(Scene_Select.obj, NULL);
	lv_obj_set_size(om, 135, 200);
    lv_obj_align(om, NULL, LV_ALIGN_CENTER, 0, 20);

    //创建顶部渐变区域
    lv_area_t r;
	lv_draw_mask_fade_param_t f1;
	r.x1 = 0;
	r.y1 = 0;
	r.x2 = 135;
	r.y2 = 80;	//渐变区域
	lv_draw_mask_fade_init(&f1, &r, LV_OPA_TRANSP, 10, LV_OPA_COVER, 50);
	lv_objmask_add_mask(om, &f1);	

    //创建底部渐变区域
	r.x1 = 0;
	r.y1 = 120;
	r.x2 = 135;
	r.y2 = 240;
	lv_draw_mask_fade_init(&f1, &r, LV_OPA_COVER, 130, LV_OPA_TRANSP, 220);
    lv_objmask_add_mask(om, &f1);
}

//图标滚动任务
void task_rolling(lv_task_t *t)
{
    Index++;    
    Index %= Selection_Num;

    lv_anim_set_values(&a, img_cont->coords.y1 - om->coords.y1, -(Index * img_interval)); // 设置开始和结束值

    lv_anim_start(&a);
    lv_label_set_text_fmt(title_label, "%s", img_array[Index].title);
}

//图标设置
void img_init()
{
    //图标背景
    // img_obj = lv_obj_create(lv_scr_act(), NULL);
    // lv_obj_set_style_local_bg_color(img_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_obj_set_style_local_border_opa(img_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    // lv_obj_set_size(img_obj, 240, 230);
    // lv_obj_align(img_obj, Scene_Select.obj, LV_ALIGN_CENTER, 0, 30); 
  

    //图标容器
    img_cont = lv_cont_create(om, NULL);
    lv_obj_set_style_local_bg_opa(img_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    
    lv_obj_set_style_local_border_opa(img_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_size(img_cont, 135, img_interval*(Selection_Num+1));

    for(int i = 0; i < Selection_Num; i++)
    {
        img_array[i].img = lv_img_create(img_cont, NULL);
        lv_img_set_src(img_array[i].img, img_array[i].img_addr);
        // lv_img_set_zoom(img_array[i].img, 300);
        lv_obj_align(img_array[i].img, img_cont, LV_ALIGN_IN_TOP_MID, 0, (i+1)*img_interval);   //设置对齐
    }

        
    //动画路径
    lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_ease_in);	

	//创建动画对象	
	lv_anim_set_path(&a, &path);
	lv_anim_set_var(&a, img_cont); 		//设置变量到动画对象
	lv_anim_set_exec_cb(&a,(lv_anim_exec_xcb_t)lv_obj_set_y);	/* 设置“动画制作”功能 */		
	lv_anim_set_time(&a, 400); 		//设置动画时长 ms
	lv_anim_set_repeat_count(&a, 1); 	//设置动画重复时间

    // lv_task_create(task_rolling, 1800, LV_TASK_PRIO_HIGH, NULL);
}

void Select_KeyFir_Func()
{
    if(img_array[Index].task_t!=NULL)
    {
       
        MenuScene = img_array[Index].task_t;
        lv_obj_move_foreground(img_array[Index].task_t->obj);
    }
}
void Select_KeySec_Func()
{
    Index++;    
    Index %= Selection_Num;

    lv_anim_set_values(&a, img_cont->coords.y1 - om->coords.y1, -(Index * img_interval)); // 设置开始和结束值

    lv_anim_start(&a);
    lv_label_set_text_fmt(title_label, "%s", img_array[Index].title);
}
void Select_KeyCancel_Func()
{
    // lv_obj_move_background(MainScence_Task.current_obj);
    Index = 0;
    lv_anim_set_values(&a, img_cont->coords.y1 - om->coords.y1, -(Index * img_interval)); // 设置开始和结束值

    lv_anim_start(&a);
    lv_label_set_text_fmt(title_label, "%s", img_array[0].title);
    MenuScene = &Scene_MainScence;
    lv_obj_move_foreground(Scene_MainScence.obj);

}