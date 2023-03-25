#include "Scene_Timer.h"
#include "Scene.h"
#include <math.h>
#include "lcd.h"

#define Line_number 28
#define Center_x 68
#define Center_y 70
#define Radiu_1 48
#define Radiu_2 55
#define PI 3.141596


static lv_obj_t *title_label;
static lv_obj_t *line_obj[Line_number];
static lv_point_t line_points[Line_number][2];
static lv_obj_t *counter_label[3];
static lv_obj_t *time_label;

uint8_t line_P1[2][Line_number];
uint8_t line_P2[2][Line_number];

uint16_t millisecond_10 = 0;
uint8_t second = 0;
uint8_t minute = 0;
uint8_t index = 0;

bool Is_Start = false;

void Timer_init()
{
    back_ground_init();
    // title_init();
    // redline_init();
    circle_init();
    rect_init();
}

//背景设置
static void back_ground_init()
{
    Scene_Timer.obj = lv_obj_create(lv_scr_act(),NULL);
    lv_obj_set_style_local_border_opa(Scene_Timer.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_bg_color(Scene_Timer.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_size(Scene_Timer.obj, LV_HOR_RES_MAX, LV_VER_RES_MAX-30);
    lv_obj_align(Scene_Timer.obj, NULL, LV_ALIGN_CENTER, 0, 25);
}

//添加标题label
static void title_init()
{
    //顶部字体style
    static lv_style_t font_style;
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    //添加字体
    title_label = lv_label_create(Scene_Timer.obj, NULL);

    lv_label_set_long_mode(title_label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(title_label, 135, 50);
    lv_obj_add_style(title_label, LV_OBJ_PART_MAIN, &font_style);   
    lv_label_set_align(title_label, LV_LABEL_ALIGN_CENTER);

    lv_obj_align(title_label, Scene_Timer.obj, LV_ALIGN_IN_TOP_MID, 0, 5);

    lv_label_set_text_fmt(title_label, "Timer");
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

    lv_obj_t* line = lv_line_create(Scene_Timer.obj, NULL);

    lv_obj_add_style(line, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
    lv_line_set_points(line, line_points, sizeof(line_points)/sizeof(lv_point_t));     /*Set the points*/
    lv_obj_align(line, NULL, LV_ALIGN_IN_TOP_MID, 0, 30);
}

static void circle_init()
{
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 3);
    lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, ENABLE);
    lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_RED);

    for (int i = 0; i < Line_number; i++)
    {
        line_P1[0][i] = Center_x + Radiu_1 * cos(i * 360/Line_number * PI/180);
        line_P1[1][i] = Center_y - Radiu_1 * sin(i * 360/Line_number * PI/180);

        line_P2[0][i] = Center_x + Radiu_2 * cos(i * 360/Line_number * PI/180);
        line_P2[1][i] = Center_y - Radiu_2 * sin(i * 360/Line_number * PI/180);

        line_points[i][0] = (lv_point_t){line_P1[0][i], line_P1[1][i]};
        line_points[i][1] = (lv_point_t){line_P2[0][i], line_P2[1][i]};
        

        line_obj[i] = lv_line_create(Scene_Timer.obj, NULL);

        lv_obj_add_style(line_obj[i], LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
        lv_line_set_points(line_obj[i], line_points[i], 2);     /*Set the points*/
        lv_obj_set_style_local_line_color(line_obj[i], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    }

    static lv_style_t font_style;
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_26);

    time_label = lv_label_create(Scene_Timer.obj, NULL);

    lv_obj_add_style(time_label, LV_OBJ_PART_MAIN, &font_style);
    lv_label_set_recolor(time_label, ENABLE);
    lv_label_set_long_mode(time_label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(time_label, 135, 50);
    lv_obj_set_pos(time_label, Center_x-36, Center_y-30);
    lv_label_set_text_fmt(time_label, "%02d#ff0000 :#%02d\r\n #ff0000  .#%02d",minute,second,millisecond_10);
}

static void rect_init()
{
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 2);
    lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, ENABLE);
    lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_RED);

    static lv_point_t line_points1[] = { {5, 140}, {120, 140} };

    lv_obj_t* line1 = lv_line_create(Scene_Timer.obj, NULL);

    lv_obj_add_style(line1, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
    lv_line_set_points(line1, line_points1, sizeof(line_points1)/sizeof(lv_point_t));     /*Set the points*/

    static lv_point_t line_points2[] = { {15, 130}, {15, 207} };

    lv_obj_t* line2 = lv_line_create(Scene_Timer.obj, NULL);   

    lv_obj_add_style(line2, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
    lv_line_set_points(line2, line_points2, sizeof(line_points2)/sizeof(lv_point_t));     /*Set the points*/

    static lv_style_t font_style;
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    int i = 0;
    for (int i = 0; i < 3; i++)
    {
        counter_label[i] = lv_label_create(Scene_Timer.obj, NULL);

        lv_obj_add_style(counter_label[i], LV_OBJ_PART_MAIN, &font_style);
        lv_label_set_text(counter_label[i], "--:--.--");
        lv_obj_set_pos(counter_label[i], 30, 142 + i * 20);        
    }
}

void timing_start(lv_task_t *t)
{
    millisecond_10++;
    if(millisecond_10==100)
    {
        millisecond_10 = 0;
        second++;
    }
    if(second==60)
    {
        second=0;
        minute++;
  
    }
    lv_label_set_text_fmt(time_label, "%02d#ff0000 :#%02d\r\n #ff0000  .#%02d", minute, second, millisecond_10);

    if(!Is_Start)
        lv_task_del(t);
}

void Timer_KeyFir_Func()
{
    if(!Is_Start)
    {
        lv_task_create(timing_start, 10, LV_TASK_PRIO_HIGHEST, NULL);
        Is_Start = true;
    }
    else
    {
        Is_Start = false;
    }
}
void Timer_KeySec_Func()
{
    if(Is_Start)
    {
        lv_label_set_text_fmt(counter_label[index], "%02d:%02d.%02d", minute, second, millisecond_10);
        index++;
        index %= 3;
    }
    else
    {
        index = 0;
        lv_label_set_text(counter_label[0], "--:--.--");
        lv_label_set_text(counter_label[1], "--:--.--");
        lv_label_set_text(counter_label[2], "--:--.--");

        minute = second = millisecond_10 = 0;
        lv_label_set_text_fmt(time_label, "%02d#ff0000 :#%02d\r\n #ff0000  .#%02d", minute, second, millisecond_10);
    }
}
void Timer_KeyCancel_Func()
{

    Is_Start = false;
    MenuScene = &Scene_Select;
    lv_obj_move_foreground(Scene_Select.obj);

}