#include "Scene_Lighting.h"
#include "Scene.h"

static lv_obj_t *title_label;   //标题
static lv_obj_t *num_label; //数字标签
static lv_obj_t *arc;       //圆
static int num;


u16 Bright = 0;

void Lighting_init()
{
    back_ground_init();
    // title_init();
    // redline_init();
    circle_num_init();
}


//背景设置
static void back_ground_init()
{
    Scene_Lighting.obj = lv_obj_create(lv_scr_act(),NULL);
    lv_obj_set_style_local_border_opa(Scene_Lighting.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_bg_color(Scene_Lighting.obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_size(Scene_Lighting.obj, LV_HOR_RES_MAX, LV_VER_RES_MAX-30);
    lv_obj_align(Scene_Lighting.obj, NULL, LV_ALIGN_CENTER, 0, 24);

}

//添加标题label
static void title_init()
{
    //顶部字体style
    static lv_style_t font_style;
    lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    //添加字体
    title_label = lv_label_create(Scene_Lighting.obj, NULL);
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(title_label, 135, 50);
    lv_obj_add_style(title_label, LV_OBJ_PART_MAIN, &font_style);   
    lv_label_set_align(title_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(title_label, Scene_Lighting.obj, LV_ALIGN_IN_TOP_MID, 0, 5);
    lv_label_set_text_fmt(title_label, "Lighting");
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
    lv_obj_t* line1 = lv_line_create(Scene_Lighting.obj, NULL);
    lv_obj_add_style(line1, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
    lv_line_set_points(line1, line_points, sizeof(line_points)/sizeof(lv_point_t));     /*Set the points*/
    lv_obj_align(line1, NULL, LV_ALIGN_IN_TOP_MID, 0, 30);
}

// 背景设置


// //添加标题label
// static void title_init()
// {
//     //顶部字体style
//     static lv_style_t font_style;
//     lv_style_set_text_color(&font_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//     lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);

//     //添加字体
//     title_label = lv_label_create(Scene_Lighting.obj, NULL);
//     lv_label_set_long_mode(title_label, LV_LABEL_LONG_BREAK);
//     lv_obj_set_size(title_label, 135, 50);
//     lv_obj_add_style(title_label, LV_OBJ_PART_MAIN, &font_style);   
//     lv_label_set_align(title_label, LV_LABEL_ALIGN_CENTER);
//     lv_obj_align(title_label, Scene_Lighting.obj, LV_ALIGN_IN_TOP_MID, 0, 5);
//     lv_label_set_text_fmt(title_label, "Lighting");
// }

//设置红线
// static void redline_init()
// {
//     static lv_style_t style_line;
//     lv_style_init(&style_line);
//     lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 4);
//     lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_RED);
//     lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, ENABLE);

//     /*Create an array for the points of the line*/
//     static lv_point_t line_points[] = { {5, 5}, {120, 5} };
//     lv_obj_t* line1 = lv_line_create(Scene_Lighting.obj, NULL);
//     lv_obj_add_style(line1, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
//     lv_line_set_points(line1, line_points, sizeof(line_points)/sizeof(lv_point_t));     /*Set the points*/
//     lv_obj_align(line1, NULL, LV_ALIGN_IN_TOP_MID, 0, 30);
// }


static void circle_num_init()
{
    static lv_style_t font_style;
	lv_style_init(&font_style);

	lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);

	lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_26);


	/*前景style*/
	static lv_style_t style_fg;
	lv_style_reset(&style_fg);
	lv_style_init(&style_fg);
	lv_style_set_line_color(&style_fg, LV_STATE_DEFAULT, LV_COLOR_RED);		//设置前景线条颜色为红色
	lv_style_set_line_width(&style_fg, LV_STATE_DEFAULT, 9);				//设置前景线条宽度为9
	lv_style_set_line_rounded(&style_fg, LV_STATE_DEFAULT,0);

	/*背景style*/
	static lv_style_t style_bg;
	lv_style_reset(&style_bg);
	lv_style_init(&style_bg);
	// lv_style_set_bg_color(&style_bg, LV_STATE_DEFAULT, LV_COLOR_BLACK);		//设置背景透明
	// lv_style_set_border_opa(&style_bg, LV_STATE_DEFAULT, LV_OPA_TRANSP);	//设置背景边界线透明
	lv_style_set_line_opa(&style_bg, LV_STATE_DEFAULT, LV_OPA_TRANSP);		//设置背景线条为透明
	lv_style_set_line_width(&style_bg, LV_STATE_DEFAULT, 5);				//设置背景线条宽度为9
	
	/*画圆初始化*/

	arc = lv_arc_create(Scene_Lighting.obj,NULL);

	lv_obj_set_style_local_border_opa(arc,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_OPA_TRANSP);
	lv_obj_set_style_local_bg_color(arc,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_BLACK);
	
	/*将style添加到arc中*/
	lv_obj_add_style(arc,LV_ARC_PART_BG, &style_bg);
	lv_obj_add_style(arc,LV_ARC_PART_INDIC, &style_fg); 
	lv_arc_set_rotation(arc, 270); //旋转270度    

    lv_obj_set_size(arc, 135, 135);
	lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 0);	

	//设置文本标签

	num_label = lv_label_create(Scene_Lighting.obj, NULL);

	lv_label_set_recolor(num_label, true);
	lv_label_set_long_mode(num_label, LV_LABEL_LONG_BREAK);

    lv_obj_set_size(num_label,135,60);
	lv_obj_add_style(num_label, LV_OBJ_PART_MAIN, &font_style);
	lv_label_set_align(num_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_align(num_label, NULL, LV_ALIGN_CENTER, 0, 0);
    
    num = TIM3->CCR4 * 100 / 7200;
    lv_label_set_text_fmt(num_label, "#ffffff %d", num);
    lv_arc_set_angles(arc, 0, (int)(num*36/10));
}
void Lighting_KeyFir_Func()
{
    key_mode = true;

    TIM3->CCR4 += 100;
    if(TIM3->CCR4>=7200)
        TIM3->CCR4 = 7200;
    num = TIM3->CCR4 * 100 / 7200;

	// Bright += 100;
	// if(Bright>=7200)
    //     Bright = 7200;
	// TIM3->CCR4 = Bright;
	
    // num = Bright * 100 / 7200;

    lv_label_set_text_fmt(num_label,"#ffffff %d ", num); 	
    lv_arc_set_angles(arc,0,num*3.6);
}
void Lighting_KeySec_Func()
{
    key_mode = true;

    if(TIM3->CCR4<=100)
        TIM3->CCR4 = 100;
    TIM3->CCR4 -= 100;
    
    num = TIM3->CCR4 * 100 / 7200;

    // if(Bright<=100)
    //     Bright = 100;
    // Bright -= 100;
    // TIM3->CCR4 = Bright;

    // num = Bright * 100 / 7200;

    lv_label_set_text_fmt(num_label,"#ffffff %d ", num); 	
    lv_arc_set_angles(arc,0,num*3.6);
}
void Lighting_KeyCancel_Func()
{
    key_mode = false;

    MenuScene = &Scene_Select;
    lv_obj_move_foreground(Scene_Select.obj);

}