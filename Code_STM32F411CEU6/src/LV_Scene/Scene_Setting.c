#include "Scene_Setting.h"
#include "Scene.h"
#include "rtc.h"

static lv_obj_t *Time_label[7];   //时间字体
static lv_obj_t *rect_obj[8];   //选择框

static char index = 0;
void timeshow_task(lv_task_t *t)
{
    if(MenuScene==&Scene_Setting)
    {
        lv_label_set_text_fmt(Time_label[0], "%02d", RTC_TimeStruct.RTC_Hours);
        lv_label_set_text_fmt(Time_label[1], "%02d", RTC_TimeStruct.RTC_Minutes);
        lv_label_set_text_fmt(Time_label[2], "%02d", RTC_TimeStruct.RTC_Seconds);
        lv_label_set_text_fmt(Time_label[3], " %02d",RTC_DateStruct.RTC_Year);
        lv_label_set_text_fmt(Time_label[4], "%s", day_t[RTC_DateStruct.RTC_WeekDay - 1]);
        lv_label_set_text_fmt(Time_label[5], "%02d", RTC_DateStruct.RTC_Month);
        lv_label_set_text_fmt(Time_label[6], "%02d", RTC_DateStruct.RTC_Date);
    }
    
}

void Setting_init(void)
{
    back_ground_init();
    text_label_init();
    rect_init();

    lv_task_create(timeshow_task, 100, LV_TASK_PRIO_MID, NULL);
}

//背景设置
static void back_ground_init(void)
{
    Scene_Setting.obj = lv_obj_create(lv_scr_act(),NULL);
    lv_obj_set_style_local_border_opa(Scene_Setting.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_bg_color(Scene_Setting.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_size(Scene_Setting.obj, LV_HOR_RES_MAX, LV_VER_RES_MAX-30);
    lv_obj_align(Scene_Setting.obj, NULL, LV_ALIGN_CENTER, 0, 25);
}

//label初始化
static void text_label_init()
{
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);

    //字体style
    static lv_style_t font_style;
    lv_style_init(&font_style);
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_22);

    //时间字体
    static lv_obj_t *time_label[3];   
    time_label[0] = lv_label_create(Scene_Setting.obj, NULL); 
    lv_obj_add_style(time_label[0], LV_OBJ_PART_MAIN, &font_style);    

    time_label[1] = lv_label_create(Scene_Setting.obj, time_label[0]); 
    time_label[2] = lv_label_create(Scene_Setting.obj, time_label[0]); 

    lv_label_set_text(time_label[0], ":       :");
    lv_label_set_text(time_label[1], "20");
    lv_label_set_text(time_label[2], "-        OK");

    lv_obj_align(time_label[0], NULL, LV_ALIGN_CENTER, 0, -58);
    lv_obj_align(time_label[1], NULL, LV_ALIGN_IN_LEFT_MID, 0, -10);
    lv_obj_align(time_label[2], NULL, LV_ALIGN_CENTER, 15, 38);

    Time_label[0] = lv_label_create(Scene_Setting.obj, NULL); 
    lv_obj_add_style(Time_label[0], LV_OBJ_PART_MAIN, &font_style);
    for (int i = 1; i < 7; i++) 
        Time_label[i] = lv_label_create(Scene_Setting.obj, Time_label[0]); 

    
    lv_label_set_text_fmt(Time_label[0], "%02d", RTC_TimeStruct.RTC_Hours);
    lv_label_set_text_fmt(Time_label[1], "%02d", RTC_TimeStruct.RTC_Minutes);
    lv_label_set_text_fmt(Time_label[2], "%02d", RTC_TimeStruct.RTC_Seconds);
    lv_label_set_text_fmt(Time_label[3], " %02d",RTC_DateStruct.RTC_Year);
    lv_label_set_text_fmt(Time_label[4], "%s", day_t[RTC_DateStruct.RTC_WeekDay - 1]);
    lv_label_set_text_fmt(Time_label[5], "%02d", RTC_DateStruct.RTC_Month);
    lv_label_set_text_fmt(Time_label[6], "%02d", RTC_DateStruct.RTC_Date);

    lv_obj_align(Time_label[0], NULL, LV_ALIGN_CENTER, -50, -58);
    lv_obj_align(Time_label[1], NULL, LV_ALIGN_CENTER, 2, -58);
    lv_obj_align(Time_label[2], NULL, LV_ALIGN_CENTER, 48, -58);
    lv_obj_align(Time_label[3], NULL, LV_ALIGN_CENTER, -25, -10);
    lv_obj_align(Time_label[4], NULL, LV_ALIGN_CENTER, 38, -10);
    lv_obj_align(Time_label[5], NULL, LV_ALIGN_CENTER, -51, 38);
    lv_obj_align(Time_label[6], NULL, LV_ALIGN_CENTER, 0, 38);
    
}

//选择框初始化
static void rect_init()
{
    rect_obj[0] = lv_obj_create(Scene_Setting.obj, NULL);
    lv_obj_set_size(rect_obj[0], 38, 40);
    lv_obj_set_style_local_border_color(rect_obj[0], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_bg_opa(rect_obj[0], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);

    for (int i = 1; i < 8; i++)
        rect_obj[i] = lv_obj_create(Scene_Setting.obj, rect_obj[0]);
    lv_obj_align(rect_obj[0], NULL, LV_ALIGN_CENTER, -48, -58);
    lv_obj_align(rect_obj[1], NULL, LV_ALIGN_CENTER, -0, -58);
    lv_obj_align(rect_obj[2], NULL, LV_ALIGN_CENTER, 48, -58);
    lv_obj_align(rect_obj[3], NULL, LV_ALIGN_CENTER, -20, -10);
    lv_obj_align(rect_obj[4], NULL, LV_ALIGN_CENTER, 28, -10);
    lv_obj_align(rect_obj[5], NULL, LV_ALIGN_CENTER, -49, 38);
    lv_obj_align(rect_obj[6], NULL, LV_ALIGN_CENTER, 0, 38);
    lv_obj_align(rect_obj[7], NULL, LV_ALIGN_CENTER, 43, 38);
    
    lv_obj_set_size(rect_obj[4], 60, 40);
    lv_obj_set_size(rect_obj[7], 42, 40);
    
    lv_obj_set_style_local_border_color(rect_obj[index], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
    
}

void Setting_KeyFir_Func()
{
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
    // key_mode = true;
    int val;
    switch(index)
    {
        case 0:
            val = RTC_TimeStruct.RTC_Hours;
            val++;
            val %= 24;
            RTC_Set_Time(val, RTC_TimeStruct.RTC_Minutes, RTC_TimeStruct.RTC_Seconds, RTC_H12_AM); //设置时间
            lv_label_set_text_fmt(Time_label[0], "%02d", RTC_TimeStruct.RTC_Hours);
            break;
        case 1:
            val = RTC_TimeStruct.RTC_Minutes;
            val++;
            val %= 60;
            RTC_Set_Time(RTC_TimeStruct.RTC_Hours, val, RTC_TimeStruct.RTC_Seconds, RTC_H12_AM); //设置时间
            lv_label_set_text_fmt(Time_label[1], "%02d", val/*RTC_TimeStruct.RTC_Minutes*/);
            break;
        case 2:
            // val = RTC_TimeStruct.RTC_Seconds;
            // val++;
            // val %= 60;
            RTC_Set_Time(RTC_TimeStruct.RTC_Hours, RTC_TimeStruct.RTC_Minutes, 0, RTC_H12_AM); //设置时间
            lv_label_set_text_fmt(Time_label[2], "%02d", RTC_TimeStruct.RTC_Seconds);
            break;

        case 3:
            val = RTC_DateStruct.RTC_Year;
            val++;
            val %= 100;
            RTC_Set_Date(val, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date, RTC_DateStruct.RTC_WeekDay);
            lv_label_set_text_fmt(Time_label[3], " %02d",RTC_DateStruct.RTC_Year);
            break;
        case 4:
            val = RTC_DateStruct.RTC_WeekDay;            
            val %= 7;
            val++;
            RTC_Set_Date(RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date, val);
            lv_label_set_text_fmt(Time_label[4], "%s", day_t[RTC_DateStruct.RTC_WeekDay - 1]);
            break;
        case 5:
            val = RTC_DateStruct.RTC_Month;
            val++;
            val %= 12;
            RTC_Set_Date(RTC_DateStruct.RTC_Year, val, RTC_DateStruct.RTC_Date, RTC_DateStruct.RTC_WeekDay);
            lv_label_set_text_fmt(Time_label[5], "%02d", RTC_DateStruct.RTC_Month);
            break;
        case 6:
            val = RTC_DateStruct.RTC_Date;
            val++;
            val %= 31+1;
            RTC_Set_Date(RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, val, RTC_DateStruct.RTC_WeekDay);
            lv_label_set_text_fmt(Time_label[6], "%02d", RTC_DateStruct.RTC_Date);
            break;
            // case 7:
    }
}
void Setting_KeySec_Func()
{
    lv_obj_set_style_local_border_color(rect_obj[index++], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    index %= 8;
    lv_obj_set_style_local_border_color(rect_obj[index], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);

} 

void Setting_KeyCancel_Func()
{
    key_mode = false;
    MenuScene = &Scene_Select;
    lv_obj_move_foreground(Scene_Select.obj);

}