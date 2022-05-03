#include "Scene.h"
#include "Scene_Main.h"
#include "key_task.h"
#include "key.h"
#include "lv_port_disp.h"
#include "stm32f4xx.h"
#include "rtc.h"

char day_t[7][4] = {"Mon", "Tue", "Wen", "Thu", "Fri", "Sat", "Sun"};

static void background_init();
static void battery_show();
static void timeLabel_show();
static void dateLabel_show();
static void stepLabel_show();

// lv_obj_t *Task_MainScence.obj = NULL;

static void tast_time_show(lv_task_t *t)
{
    static bool flag;
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
    if(flag) lv_label_set_text_fmt(t->user_data,"#ffffff %02d# #ff0000 :# #ffffff %02d ",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes);
    else lv_label_set_text_fmt(t->user_data,"#ffffff %02d : %02d ",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes);

    flag = !flag;
}
static void tast_date_show(lv_task_t *t)
{
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
    lv_label_set_text_fmt(t->user_data,"#ffffff %02d# #ff0000 /# #ffffff %02d ",RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date);
}


void mainMenu_init()
{
    background_init();
    battery_show();
    timeLabel_show();
    dateLabel_show();
    stepLabel_show();
    
}

void background_init()
{
    //  设置背景为纯黑
    Task_MainScence.obj = lv_obj_create(lv_scr_act(),NULL);
    lv_obj_set_style_local_bg_color(Task_MainScence.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_size(Task_MainScence.obj,LV_HOR_RES_MAX,LV_VER_RES_MAX);
    lv_obj_set_style_local_border_opa(Task_MainScence.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
}

void battery_show()
{
    //设置电池style
    static lv_style_t bat_style;
	lv_style_init(&bat_style);
    lv_style_set_text_font(&bat_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
    lv_style_set_text_color(&bat_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

     //添加电池label
    lv_obj_t * label_bat = lv_label_create(Task_MainScence.obj, NULL);
    lv_label_set_recolor(label_bat,ENABLE);
    lv_obj_add_style(label_bat, LV_OBJ_PART_MAIN, &bat_style);
    lv_label_set_text(label_bat, LV_SYMBOL_BATTERY_3);
    lv_obj_align(label_bat,NULL, LV_ALIGN_IN_TOP_RIGHT, -10 ,0);
}
void timeLabel_show()
{
    // 设置字体style
    static lv_style_t font_style;
    lv_style_init(&font_style);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_30);

    //添加时间label
    lv_obj_t *label_t = lv_label_create(Task_MainScence.obj, NULL);
    lv_label_set_recolor(label_t, ENABLE);
    lv_obj_add_style(label_t, LV_OBJ_PART_MAIN, &font_style);
    lv_obj_align(label_t, NULL, LV_ALIGN_CENTER, -15, 0);
    // lv_obj_set_style_local_transform_zoom(label_t, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 512);
    
    lv_label_set_align(label_t, LV_LABEL_ALIGN_RIGHT);


    //时间显示任务
    lv_task_create(tast_time_show, 1000, LV_TASK_PRIO_HIGH, label_t);

}
void dateLabel_show()
{    
    // 设置字体style
    static lv_style_t font_style;
    lv_style_init(&font_style);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    //添加日期label
    lv_obj_t *label_d = lv_label_create(Task_MainScence.obj, NULL);
    lv_label_set_recolor(label_d, ENABLE);
    lv_obj_add_style(label_d, LV_OBJ_PART_MAIN, &font_style);
    lv_obj_align(label_d, NULL, LV_ALIGN_CENTER, -35, -50);
    lv_label_set_align(label_d, LV_LABEL_ALIGN_CENTER);    

    //添加星期label
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
    lv_obj_t *label_w = lv_label_create(Task_MainScence.obj, NULL);
    lv_obj_add_style(label_w, LV_OBJ_PART_MAIN, &font_style);
    lv_label_set_text_fmt(label_w, "%s", day_t[RTC_DateStruct.RTC_WeekDay-1]);
    lv_obj_align(label_w, NULL, LV_ALIGN_CENTER, 38, -50);        

    //日期显示任务
    lv_task_create(tast_date_show, 1000, LV_TASK_PRIO_HIGH, label_d); 
}
void stepLabel_show()
{
    //跑图标显示
    LV_IMG_DECLARE(img_run);
    lv_obj_t * img = lv_img_create(Task_MainScence.obj, NULL);	
    lv_img_set_src(img, &img_run);
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, -35, 45);   // 设置对齐

    //跑步字体样式style
    static lv_style_t step_style;
    lv_style_init(&step_style);
    lv_style_set_text_font(&step_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
    lv_style_set_text_color(&step_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    
    //设置步数字体
    lv_obj_t *step_label = lv_label_create(Task_MainScence.obj, NULL);
    lv_obj_add_style(step_label, LV_OBJ_PART_MAIN, &step_style);
    lv_label_set_recolor(step_label, ENABLE);
    lv_label_set_text(step_label, "#00ffff /# #ffffff 1234");

    lv_obj_align(step_label, NULL, LV_ALIGN_CENTER, 15, 45);   // 设置对齐
}

void Main_KeyFir_Func()
{
    // lv_obj_move_background(MenuTask->current_obj);
    // Last_MenuTask = MenuTask;
    MenuTask = &Task_Select;
    lv_obj_move_foreground(Task_Select.obj);
    // MenuTask = MenuTask->next_task;
}
void Main_KeySec_Func()
{

    
}
void Main_KeyCancel_Func()
{

}