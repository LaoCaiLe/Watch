#include "Scene_Alarm.h"
#include "Scene.h"
#include "led.h"
#include "rtc.h"

static lv_obj_t *title_label;
static lv_obj_t *week_label;
static lv_obj_t *hour_label;
static lv_obj_t *min_label;
// static lv_obj_t *time_label;
static lv_obj_t *music_label;

static lv_obj_t *week_roller;
static lv_obj_t *hour_roller;
static lv_obj_t *min_roller;
static lv_obj_t *music_roller;

static lv_obj_t *alarm_switch;

static lv_obj_t *rect_obj[4];

static char index = 0;
int music_index = 0;

void Alarm_init(void)
{
    back_ground_init();
    // title_init();
    // redline_init();
    rect_init();
    // switch_init();
    roller_init();
    text_init();
}

//背景设置
static void back_ground_init()
{
    Scene_Alarm.obj = lv_obj_create(lv_scr_act(),NULL);
    lv_obj_set_style_local_border_opa(Scene_Alarm.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_bg_color(Scene_Alarm.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_size(Scene_Alarm.obj, LV_HOR_RES_MAX, LV_VER_RES_MAX-30);
    lv_obj_align(Scene_Alarm.obj, NULL, LV_ALIGN_CENTER, 0, 25);
    // lv_obj_set_size(Scene_Alarm.obj, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    // lv_obj_align(Scene_Alarm.obj, NULL, LV_ALIGN_CENTER, 0, 0);
}


//添加标题label
static void title_init()
{
    //顶部字体style
    static lv_style_t font_style;
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    //添加字体
    title_label = lv_label_create(Scene_Alarm.obj, NULL);
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(title_label, 135, 50);
    lv_obj_add_style(title_label, LV_OBJ_PART_MAIN, &font_style);   
    lv_label_set_align(title_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(title_label, Scene_Alarm.obj, LV_ALIGN_IN_TOP_MID, 0, 5);
    lv_label_set_text_fmt(title_label, "Alarm");
}

//设置红线
static void redline_init()
{
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 4);
    lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, ENABLE);

    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {5, 5}, {120, 5} };
    lv_obj_t* line = lv_line_create(Scene_Alarm.obj, NULL);
    lv_obj_add_style(line, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
    lv_line_set_points(line, line_points, sizeof(line_points)/sizeof(lv_point_t));     /*Set the points*/
    lv_obj_align(line, NULL, LV_ALIGN_IN_TOP_MID, 0, 30);
}

static void rect_init()
{

    rect_obj[0] = lv_obj_create(Scene_Alarm.obj, NULL);
    lv_obj_set_size(rect_obj[0], 135, 51);
    lv_obj_align(rect_obj[0], NULL, LV_ALIGN_CENTER, -0, -80);
    lv_obj_set_style_local_border_color(rect_obj[0], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_bg_opa(rect_obj[0], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);

    rect_obj[1] = lv_obj_create(Scene_Alarm.obj, rect_obj[0]);
    lv_obj_align(rect_obj[1], NULL, LV_ALIGN_CENTER, -0, -30);

    rect_obj[2] = lv_obj_create(Scene_Alarm.obj, rect_obj[0]);
    lv_obj_align(rect_obj[2], NULL, LV_ALIGN_CENTER, -0, 20);

    rect_obj[3] = lv_obj_create(Scene_Alarm.obj, rect_obj[0]);
    lv_obj_align(rect_obj[3], NULL, LV_ALIGN_CENTER, -0, 70);

    lv_obj_set_style_local_border_color(rect_obj[index], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
}

static void switch_init()
{
    alarm_switch = lv_switch_create(Scene_Alarm.obj, NULL);
    lv_obj_align(alarm_switch, NULL, LV_ALIGN_IN_TOP_MID, 40, 10);

}
static void text_init()
{
    //字体style
    static lv_style_t font_style;
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    //添加字体
    week_label = lv_label_create(Scene_Alarm.obj, NULL);
    hour_label = lv_label_create(Scene_Alarm.obj, NULL);
    min_label = lv_label_create(Scene_Alarm.obj, NULL);
    // time_label = lv_label_create(Scene_Alarm.obj, NULL);
    music_label = lv_label_create(Scene_Alarm.obj, NULL);

    // lv_obj_add_style(time_label, LV_OBJ_PART_MAIN, &font_style);   
    // lv_obj_align(time_label, Scene_Alarm.obj, LV_ALIGN_IN_TOP_LEFT, 10, 15);
    // lv_label_set_text_fmt(time_label, "%02d:%02d", lv_roller_get_selected(hour_roller), lv_roller_get_selected(min_roller));
    
    lv_obj_add_style(music_label, LV_OBJ_PART_MAIN, &font_style);   
    lv_obj_align(music_label, Scene_Alarm.obj, LV_ALIGN_IN_TOP_LEFT, 10, 15);
    lv_label_set_text_fmt(music_label, "music");

    lv_obj_add_style(hour_label, LV_OBJ_PART_MAIN, &font_style);   
    lv_obj_align(hour_label, Scene_Alarm.obj, LV_ALIGN_IN_TOP_LEFT, 10, 59);    
    lv_label_set_text_fmt(hour_label, "hour");

    lv_obj_add_style(min_label, LV_OBJ_PART_MAIN, &font_style);   
    lv_obj_align(min_label, Scene_Alarm.obj, LV_ALIGN_IN_TOP_LEFT, 10, 109);
    lv_label_set_text_fmt(min_label, "min");
    
    lv_obj_add_style(week_label, LV_OBJ_PART_MAIN, &font_style);   
    lv_obj_align(week_label, Scene_Alarm.obj, LV_ALIGN_IN_TOP_LEFT, 10, 159);
    lv_label_set_text_fmt(week_label, "week");
}
static void roller_init()
{
   
    week_roller = lv_roller_create(Scene_Alarm.obj, NULL);
    hour_roller = lv_roller_create(Scene_Alarm.obj, NULL);
    min_roller = lv_roller_create(Scene_Alarm.obj, NULL);
    music_roller = lv_roller_create(Scene_Alarm.obj, NULL);
    lv_roller_set_options(music_roller, "01\n"
                                       "02\n"
                                       "03",
                          LV_ROLLER_MODE_INFINITE);
    lv_roller_set_options(week_roller, "Mon\n"
                                       "Tue\n"
                                       "Wen\n"
                                       "Thu\n"
                                       "Fri\n"
                                       "Sat\n"
                                       "Sun",
                          LV_ROLLER_MODE_INFINITE);
    lv_roller_set_options(hour_roller, "00\n" "01\n" "02\n" "03\n" "04\n" "05\n" "06\n" "07\n" 
                                       "08\n" "09\n" "10\n" "11\n" "12\n" "13\n" "14\n" "15\n" 
                                       "16\n" "17\n" "18\n" "19\n" "20\n" "21\n" "22\n" "23",
                          LV_ROLLER_MODE_INFINITE);

    lv_roller_set_options(min_roller, "00\n" "01\n" "02\n" "03\n" "04\n" "05\n" "06\n" "07\n" "08\n" "09\n" 
                                      "10\n" "11\n" "12\n" "13\n" "14\n" "15\n" "16\n" "17\n" "18\n" "19\n" 
                                      "20\n" "21\n" "22\n" "23\n" "24\n" "25\n" "26\n" "27\n" "28\n" "29\n" 
                                      "30\n" "31\n" "32\n" "33\n" "34\n" "35\n" "36\n" "37\n" "38\n" "39\n" 
                                      "40\n" "41\n" "42\n" "43\n" "44\n" "45\n" "46\n" "47\n" "48\n" "49\n" 
                                      "50\n" "51\n" "52\n" "53\n" "54\n" "55\n" "56\n" "57\n" "58\n" "59",
                          LV_ROLLER_MODE_INFINITE);

    lv_obj_set_style_local_bg_color(music_roller, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_bg_color(week_roller, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_bg_color(hour_roller, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_bg_color(min_roller, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_text_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    lv_style_set_bg_opa(&style_line, LV_STATE_DEFAULT, LV_OPA_TRANSP);

    lv_roller_set_anim_time(music_roller, 40);
    lv_roller_set_anim_time(week_roller, 40);
    lv_roller_set_anim_time(hour_roller, 40);
    lv_roller_set_anim_time(min_roller, 40);

    lv_roller_set_visible_row_count(music_roller, 1);
    lv_roller_set_visible_row_count(week_roller, 1);
    lv_roller_set_visible_row_count(hour_roller, 1);
    lv_roller_set_visible_row_count(min_roller, 1);

    lv_obj_add_style(music_roller, LV_OBJ_PART_MAIN, &style_line);
    lv_obj_add_style(week_roller, LV_OBJ_PART_MAIN, &style_line);
    lv_obj_add_style(hour_roller, LV_OBJ_PART_MAIN, &style_line);
    lv_obj_add_style(min_roller, LV_OBJ_PART_MAIN, &style_line);
    
    lv_obj_set_style_local_border_opa(music_roller, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);  
    lv_obj_set_style_local_border_opa(week_roller, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);  
    lv_obj_set_style_local_border_opa(hour_roller, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_border_opa(min_roller, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);

    lv_obj_align(week_roller, NULL, LV_ALIGN_IN_TOP_MID, 35, 24+130);
    lv_obj_align(hour_roller, NULL, LV_ALIGN_IN_TOP_MID, 40, 24+30);
    lv_obj_align(min_roller, NULL, LV_ALIGN_IN_TOP_MID, 40, 24+80);
    lv_obj_align(music_roller, NULL, LV_ALIGN_IN_TOP_MID, 40, 4);
}

void Alarm_KeyFir_Func()
{
    int val;
    

    switch(index)
    {
        case 0:
            key_mode = false;
            // if(lv_switch_get_state(alarm_switch)) 
            //     lv_switch_off(alarm_switch, LV_ANIM_ON);
            // else
            // {
            //     lv_switch_on(alarm_switch, LV_ANIM_ON);
            //     RTC_Set_AlarmA(lv_roller_get_selected(week_roller) + 1, lv_roller_get_selected(hour_roller), lv_roller_get_selected(min_roller), 0);
            // }
            val = lv_roller_get_selected(music_roller);
            TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //允许定时器4更新中断
            music_index = val;
            alarm_stop = true;
            if(music_index==2)
                lv_task_create(Beep_alarm1_task, 1, LV_TASK_PRIO_LOW, NULL);
            else if(music_index==0)
                lv_task_create(Beep_alarm2_task, 1, LV_TASK_PRIO_LOW, NULL);
            else if(music_index==1)
                lv_task_create(Beep_alarm3_task, 1, LV_TASK_PRIO_LOW, NULL);
            lv_roller_set_selected(music_roller, ++val, LV_ANIM_ON);
        
        
        
        break;
            
        case 1:
            key_mode = true;
            val = lv_roller_get_selected(hour_roller);
            lv_roller_set_selected(hour_roller, ++val, LV_ANIM_ON);
            // lv_label_set_text_fmt(time_label, "%02d:%02d", lv_roller_get_selected(hour_roller), lv_roller_get_selected(min_roller));
            RTC_Set_AlarmA(lv_roller_get_selected(week_roller) + 1, lv_roller_get_selected(hour_roller), lv_roller_get_selected(min_roller), 0);
            break;

        case 2:
            key_mode = true;
            val = lv_roller_get_selected(min_roller);
            lv_roller_set_selected(min_roller, ++val, LV_ANIM_ON);
            // lv_label_set_text_fmt(time_label, "%02d:%02d", lv_roller_get_selected(hour_roller), lv_roller_get_selected(min_roller));
            RTC_Set_AlarmA(lv_roller_get_selected(week_roller) + 1, lv_roller_get_selected(hour_roller), lv_roller_get_selected(min_roller), 0);
            break;

        case 3:
            key_mode = false;
            val = lv_roller_get_selected(week_roller);
            lv_roller_set_selected(week_roller, ++val, LV_ANIM_ON);
            RTC_Set_AlarmA(lv_roller_get_selected(week_roller) + 1, lv_roller_get_selected(hour_roller), lv_roller_get_selected(min_roller), 0);
            break;
    }

    
}      
void Alarm_KeySec_Func()
{
    key_mode = false;

    lv_obj_set_style_local_border_color(rect_obj[index], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    index++;
    index %= 4;
    lv_obj_set_style_local_border_color(rect_obj[index], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);

}
void Alarm_KeyCancel_Func()
{
    key_mode = false;
    MenuScene = &Scene_Select;
    lv_obj_move_foreground(Scene_Select.obj);

}