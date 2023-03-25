
#include "Scene.h"
#include "lv_port_disp.h"
#include "rtc.h"
#include "Task.h"

char day_t[][4] = {"Mon", "Tue", "Wen", "Thu", "Fri", "Sat", "Sun"};

static void background_init();
static void battery_show();
static void timeLabel_show();
static void dateLabel_show();
static void stepLabel_show();

lv_obj_t *label_t;  //时间Label
lv_obj_t *label_d;  //日期label
lv_obj_t *label_step;   //步数label
lv_obj_t *label_temp;   //温度label
lv_obj_t *label_bat;    //电量label
lv_obj_t *img_battery;  //电池图标
static int last_hour;
static void tast_time_show(lv_task_t *t)
{
    static bool flag;
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
    // if(last_hour!=RTC_TimeStruct.RTC_Hours)
    // {
    //     TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器3更新中断
    //     lv_task_create(Beep_hour_task, 1, LV_TASK_PRIO_LOW, NULL);    //USB插入充电音效   
    // }
    if(flag) lv_label_set_text_fmt(t->user_data,"#ffffff %02d# #ff0000 :# #ffffff %02d ",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes);
    else lv_label_set_text_fmt(t->user_data,"#ffffff %02d : %02d ",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes);
    last_hour = RTC_TimeStruct.RTC_Hours;
    flag = !flag;
}
static void tast_date_show(lv_task_t *t)
{
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
    lv_label_set_text_fmt(label_d,"#ffffff %02d# #ff0000 /# #ffffff %02d ",RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date);
    lv_label_set_text_fmt(t->user_data, "%s", day_t[RTC_DateStruct.RTC_WeekDay-1]);
}


void mainMenu_init()
{
    background_init();  //背景设置
    battery_show();     //电池显示
    timeLabel_show();   //时间label显示
    dateLabel_show();   //日期label显示
    stepLabel_show();   //步数label显示
    tempLabel_show();   //温度label显示

    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
    lv_label_set_text_fmt(label_d,"#ffffff %02d# #ff0000 /# #ffffff %02d ",RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date);
    lv_label_set_text_fmt(label_t,"#ffffff %02d# #ff0000 :# #ffffff %02d ",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes);
}

static void background_init()
{
    //  设置背景为纯黑
    Scene_MainScence.obj = lv_obj_create(lv_scr_act(),NULL);
    lv_obj_set_style_local_bg_color(Scene_MainScence.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_size(Scene_MainScence.obj,LV_HOR_RES_MAX,LV_VER_RES_MAX);
    lv_obj_set_style_local_border_opa(Scene_MainScence.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
}

void battery_show()
{
    // //设置电池字体style
    // static lv_style_t bat_style;
	// lv_style_init(&bat_style);
    // lv_style_set_text_font(&bat_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
    // lv_style_set_text_color(&bat_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    //  //添加电池字体label
    // label_bat = lv_label_create(Scene_MainScence.obj, NULL);
    // lv_label_set_recolor(label_bat,ENABLE);
    // lv_obj_add_style(label_bat, LV_OBJ_PART_MAIN, &bat_style);
    // lv_label_set_text(label_bat, "100%%");
    // lv_obj_align(label_bat,NULL, LV_ALIGN_IN_TOP_RIGHT, -32 ,0);
    
    LV_IMG_DECLARE(img_battery_4);
    img_battery = lv_img_create(Scene_MainScence.obj, NULL);	
    lv_img_set_src(img_battery, &img_battery_4);
    lv_obj_align(img_battery, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);   // 设置对齐
}
void timeLabel_show()
{
    // 设置字体style
    static lv_style_t font_style;
    lv_style_init(&font_style);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_36);

    //添加时间label
    label_t = lv_label_create(Scene_MainScence.obj, NULL);
    lv_label_set_recolor(label_t, ENABLE);
    lv_obj_add_style(label_t, LV_OBJ_PART_MAIN, &font_style);
    lv_obj_align(label_t, NULL, LV_ALIGN_CENTER, -15, 10);
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
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_22);
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    //添加日期label
    label_d = lv_label_create(Scene_MainScence.obj, NULL);
    lv_label_set_recolor(label_d, ENABLE);
    lv_obj_add_style(label_d, LV_OBJ_PART_MAIN, &font_style);
    lv_obj_align(label_d, NULL, LV_ALIGN_CENTER, -41, -50);
    lv_label_set_align(label_d, LV_LABEL_ALIGN_CENTER);    

    //添加星期label
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
    lv_obj_t *label_w = lv_label_create(Scene_MainScence.obj, NULL);
    lv_obj_add_style(label_w, LV_OBJ_PART_MAIN, &font_style);
    lv_label_set_text_fmt(label_w, "%s", day_t[RTC_DateStruct.RTC_WeekDay-1]);
    lv_obj_align(label_w, NULL, LV_ALIGN_CENTER, 46, -50);        

    //日期显示任务
    lv_task_create(tast_date_show, 1000, LV_TASK_PRIO_HIGH, label_w); 
}

void stepLabel_show()
{
    //跑图标显示
    lv_obj_t * img = lv_img_create(Scene_MainScence.obj, NULL);	
    lv_img_set_src(img, &img_run);
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, -35, 70);   // 设置对齐

    //跑步字体样式style
    static lv_style_t step_style;
    lv_style_init(&step_style);
    lv_style_set_text_font(&step_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    lv_style_set_text_color(&step_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    
    //设置步数字体
    label_step = lv_label_create(Scene_MainScence.obj, NULL);
    lv_obj_add_style(label_step, LV_OBJ_PART_MAIN, &step_style);
    lv_label_set_recolor(label_step, ENABLE);
    lv_label_set_text(label_step, "#ff0000 /# #ffffff 1234");
    
    lv_obj_align(label_step, NULL, LV_ALIGN_CENTER, 15, 70);   // 设置对齐
}


void tempLabel_show()
{
    // 温度显示
    // 设置字体style
    static lv_style_t font_style;
    lv_style_init(&font_style);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    //添加温度label
    label_temp = lv_label_create(Scene_MainScence.obj, NULL);
    lv_label_set_recolor(label_temp, ENABLE);
    lv_obj_add_style(label_temp, LV_OBJ_PART_MAIN, &font_style);
    lv_obj_align(label_temp, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_label_set_text_fmt(label_temp, " 'C");
    // lv_label_set_align(label_temp, LV_LABEL_ALIGN_CENTER);   
}


void Main_KeyFir_Func()
{
    // lv_obj_move_background(MenuScene->current_obj);
    // Last_MenuScene = MenuScene;
    MenuScene = &Scene_Select;
    lv_obj_move_foreground(Scene_Select.obj);
    // MenuScene = MenuScene->next_task;
}
void Main_KeySec_Func()
{
 
}
void Main_KeyCancel_Func()
{
     

}