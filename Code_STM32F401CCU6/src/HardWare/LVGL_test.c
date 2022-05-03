#include "LVGL_test.h"
#include "../GUI/lvgl/lvgl.h"
#include "delay.h"
#include "led.h"

void lvgl_first_demo_start(void)
{
	/*按钮初始化*/
	lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
	lv_obj_set_size(btn, 70, 30);                          /*Set its size*/

	//lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/

	lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
	lv_label_set_text(label, "Button");                     /*Set the labels text*/

    /*文本标签初始化*/
	static lv_style_t font_style;
	lv_style_init(&font_style);
	lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_14);

	lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_recolor(label1, true);   
	lv_label_set_long_mode(label1,LV_LABEL_LONG_BREAK);
	lv_label_set_text(label1,"#000080 Re-color# #0000ff words# #6666ff of a# label " "Hello world!"); 	
	// lv_obj_set_style_local_text_font(label1,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,lv_font_t)
	lv_obj_set_width(label1,150);
	lv_obj_add_style(label1, LV_OBJ_PART_MAIN, &font_style);
	lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
	//lv_obj_align(btn, label1, LV_ALIGN_OUT_TOP_MID, 0, -10);
 
}

/*图片显示demo*/
void lv_demo_img(void)
{
	static lv_obj_t * imgBg;

	LV_IMG_DECLARE(img_game);
	imgBg = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(imgBg, &img_game);
	// lv_obj_set_size(imgBg, 100, 100);
	// lv_img_set_zoom(imgBg, 512);

	lv_obj_align(imgBg, NULL, LV_ALIGN_CENTER, 0, 0);   // 设置对齐

}

/*库内图标显示demo*/
void lv_symbol_show()
{
	lv_obj_t * my_label = lv_label_create(lv_scr_act(), NULL);
	
	lv_label_set_text(my_label, LV_SYMBOL_OK "ok");
	// lv_obj_set_size(my_label,160,160);	
	lv_obj_align(my_label,NULL, LV_ALIGN_CENTER, 0 ,0);//、
	// lv_obj_set_opa_scale_enable(my_label,ENABLE);   //开启透明度
	// lv_obj_set_opa_scale(my_label,75);              //设置透明度50%

	lv_obj_t * my_label2 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(my_label2, LV_SYMBOL_MUTE "Mute");
	lv_obj_align(my_label2,my_label,LV_ALIGN_IN_BOTTOM_MID,0,30);

}

/*圆弧显示*/


static void ArcTaskCb(lv_task_t *t)
{
	static int16_t a = 0;

	//1. 每20ms任务调度时，此a+3；
	a += 3;
	if(a > 360)a = 360;
	led1 = !led1;
	//2. 给user_data这个传递过来的圆弧对象重绘制0度->a度的弧度	
  	lv_arc_set_bg_angles(t->user_data,0,a);
	lv_arc_set_angles(t->user_data, 0 ,a);
	if(a == 360)   
	{
		a=0;		
		//删除任务
		//lv_task_del(t);
	}
}

void lv_circle_show(void)
{	
	/*前景style*/
	static lv_style_t style_fg;
	lv_style_reset(&style_fg);
	lv_style_init(&style_fg);
	lv_style_set_line_color(&style_fg, LV_STATE_DEFAULT, LV_COLOR_RED);	//设置前景线条颜色为橙色
	lv_style_set_line_width(&style_fg, LV_STATE_DEFAULT, 9);				//设置前景线条宽度为9
	lv_style_set_line_rounded(&style_fg, LV_STATE_DEFAULT,0);

	/*背景style*/
	static lv_style_t style_bg;
	lv_style_reset(&style_bg);
	lv_style_init(&style_bg);
	lv_style_set_bg_color(&style_bg, LV_STATE_DEFAULT, LV_COLOR_BLACK);		//设置背景透明
	lv_style_set_border_opa(&style_bg, LV_STATE_DEFAULT, LV_OPA_TRANSP);		//设置背景边界线透明
	lv_style_set_line_opa(&style_bg, LV_STATE_DEFAULT, LV_OPA_TRANSP);		//设置背景线条为透明
	lv_style_set_line_width(&style_bg, LV_STATE_DEFAULT, 5);				//设置背景线条宽度为9
	
	/*画圆初始化*/
	lv_obj_t *arc = lv_arc_create(lv_scr_act(),NULL);
	lv_obj_set_style_local_border_opa(arc,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_OPA_TRANSP);
	lv_obj_set_style_local_bg_color(arc,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_BLACK);
	/*将style添加到arc中*/
	lv_obj_add_style(arc,LV_ARC_PART_BG, &style_bg);
	lv_obj_add_style(arc,LV_ARC_PART_INDIC, &style_fg); 
	lv_arc_set_rotation(arc, 270); //旋转90度

	/*数字显示*/
	lv_obj_t *label = lv_label_create(arc,NULL);
	
	lv_obj_set_size(label,100,100);
	lv_label_set_text(label,"hello,circle");
	lv_obj_set_style_local_text_color(label,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_RED);

	
	lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

	#if 0
	lv_arc_set_range(arc,0,100);//设置范围为0-200度
	lv_arc_set_value(arc,80);//前景色设置就访问为100 即50%
	#else
	lv_arc_set_bg_angles(arc,90,360);
	lv_arc_set_angles(arc,45,181);

	#endif
	lv_obj_set_size(arc,135,135);
    lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 0);	
	lv_task_create(ArcTaskCb, 10, LV_TASK_PRIO_LOWEST, arc);//创建了一个20ms，优先级为最低的ArcTaskCb重绘任务，并向任务的user_data参数传递arc指针
	
}

/*进度条显示*/
static void BarTaskCb(lv_task_t *t)
{
	static int b=0;
	b+=5;
	b%=500;
	lv_bar_set_value(t->user_data, b, LV_ANIM_OFF);
}

void lv_bar_show(void)
{
    lv_obj_t* bar = lv_bar_create(lv_scr_act(), NULL);
    lv_obj_set_size(bar, 200, 20);
    lv_obj_align(bar, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_bar_set_range(bar,0,1000);
    lv_bar_set_value(bar, 50, LV_ANIM_ON);
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_COLOR_BLACK);		//设置进度条背景
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_COLOR_CYAN);	//设置进度条前景
	lv_task_create(BarTaskCb, 100, LV_TASK_PRIO_LOWEST, bar);//创建了一个20ms，优先级为最低的BarTaskCb重绘任务，并向任务的user_data参数传递bar指针

    lv_obj_t* bar1 = lv_bar_create(lv_scr_act(), NULL);
    lv_obj_set_size(bar1, 200, 20);
    lv_bar_set_range(bar1, 0, 10000);
	lv_obj_align(bar1, NULL, LV_ALIGN_CENTER, 0, 50);
	lv_obj_set_style_local_bg_color(bar1, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_COLOR_BLACK);		//设置进度条背景
	lv_obj_set_style_local_bg_color(bar1, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_COLOR_CYAN);
    lv_bar_set_value(bar1, 9000, LV_ANIM_ON);
 
 
    lv_obj_t* bar2 = lv_bar_create(lv_scr_act(), NULL);
    lv_obj_set_size(bar2, 200, 20);
    lv_bar_set_range(bar2, 0, 10000);
	lv_obj_align(bar2, NULL, LV_ALIGN_CENTER, 0, 100);
	lv_obj_set_style_local_bg_color(bar2, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_COLOR_BLACK);		//设置进度条背景
	lv_obj_set_style_local_bg_color(bar2, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_COLOR_CYAN);
    lv_bar_set_anim_time(bar2, 5000); /* 填充满的时间 */
    lv_bar_set_value(bar2, 9000, LV_ANIM_ON);
    
}

/*日期显示*/
void lv_calendar_show()
{
    lv_calendar_date_t today;
    today.year = 2021;
    today.month = 11;
    today.day = 12;
 
    lv_obj_t* calendar = lv_calendar_create(lv_scr_act(), NULL);
    lv_obj_set_size(calendar, 240, 300);
    lv_obj_align(calendar, NULL, LV_ALIGN_CENTER, 0, 0);

	lv_obj_set_state(calendar,LV_STATE_CHECKED);
 
    lv_calendar_set_today_date(calendar, &today);	//设置时间到calendar部件
	lv_calendar_set_showed_date(calendar, &today);	//显示今天时间 
} 

/*复选框控件*/
void lv_check_box_show(void)
{
    lv_obj_t* cb1 = lv_checkbox_create(lv_scr_act(), NULL);
    lv_checkbox_set_text(cb1, "Check Box 1");
	lv_checkbox_set_disabled(cb1);	//禁用
    lv_obj_align(cb1, NULL, LV_ALIGN_CENTER, 0, -40);
 
    
    lv_obj_t* cb2 = lv_checkbox_create(lv_scr_act(), NULL);
    lv_checkbox_set_text(cb2, "Check Box 2");
    lv_obj_align(cb2, NULL, LV_ALIGN_CENTER, 0, 0);	
    lv_obj_set_style_local_bg_color(cb2, LV_CHECKBOX_PART_BULLET, LV_STATE_DEFAULT, LV_COLOR_RED);
 
    lv_obj_t* cb3 = lv_checkbox_create(lv_scr_act(), NULL);
    lv_checkbox_set_text(cb3, "Check Box 3");
    lv_obj_align(cb3, NULL, LV_ALIGN_CENTER, 0, 40);
	lv_checkbox_set_checked(cb3, true);	//设置打勾
    lv_obj_set_style_local_bg_color(cb3, LV_CHECKBOX_PART_BULLET, LV_STATE_DEFAULT, LV_COLOR_BLUE);
}
/*表格显示*/
void lv_chart_show()
{
	 /*Create a chart*/
    lv_obj_t* chart = lv_chart_create(lv_scr_act(), NULL);
    lv_obj_set_size(chart, 200, 150);
    lv_obj_align(chart, NULL, LV_ALIGN_CENTER, 0, -80);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/
 
    /*Add a faded are effect*/
    lv_obj_set_style_local_bg_opa(chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, LV_OPA_50); 	/*Max. opa.*/
    lv_obj_set_style_local_bg_grad_dir(chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_obj_set_style_local_bg_main_stop(chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 255);    /*Max opa on the top 顶部显色*/ 
    lv_obj_set_style_local_bg_grad_stop(chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 0);      /*Transparent on the bottom 底部透明*/
 
    /*Add two data series*/
    lv_chart_series_t* ser1 = lv_chart_add_series(chart, LV_COLOR_GREEN);
 
    /*Set the next points on 'ser1'*/
    lv_chart_set_next(chart, ser1, 31);
    lv_chart_set_next(chart, ser1, 66);
    lv_chart_set_next(chart, ser1, 10);
    lv_chart_set_next(chart, ser1, 89);
    lv_chart_set_next(chart, ser1, 63);
    lv_chart_set_next(chart, ser1, 56);
    lv_chart_set_next(chart, ser1, 32);
    lv_chart_set_next(chart, ser1, 35);
    lv_chart_set_next(chart, ser1, 57);
    lv_chart_set_next(chart, ser1, 85);
 
    lv_chart_refresh(chart); /*Required after direct set*/
 
    lv_obj_t* chart2 = lv_chart_create(lv_scr_act(), NULL);
    lv_obj_set_size(chart2, 200, 150);
    lv_obj_align(chart2, NULL, LV_ALIGN_CENTER, 0, 80);
    lv_chart_set_type(chart2, LV_CHART_TYPE_LINE);   /*Show lines and points too*/
    lv_obj_set_style_local_bg_color(chart2, LV_CHART_PART_BG, LV_STATE_DEFAULT, LV_COLOR_RED);
 
    lv_chart_series_t* chart2_ser1 = lv_chart_add_series(chart2, LV_COLOR_GREEN);
    /*Set the next points on 'ser1'*/
    lv_chart_set_next(chart2, chart2_ser1, 31);
    lv_chart_set_next(chart2, chart2_ser1, 66);
    lv_chart_set_next(chart2, chart2_ser1, 10);
    lv_chart_set_next(chart2, chart2_ser1, 89);
    lv_chart_set_next(chart2, chart2_ser1, 63);
    lv_chart_set_next(chart2, chart2_ser1, 56);
    lv_chart_set_next(chart2, chart2_ser1, 32);
    lv_chart_set_next(chart2, chart2_ser1, 35);
    lv_chart_set_next(chart2, chart2_ser1, 57);
    lv_chart_set_next(chart2, chart2_ser1, 85);
	lv_chart_set_next(chart2, chart2_ser1, 15);
    //lv_chart_refresh(chart2); /*Required after direct set*/
}
/*画线显示*/
void lv_line_show(void)
{
    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 8);
 
    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {5, 5}, {70, 70}, {120, 10}, {180, 60}, {240, 10} };
    lv_obj_t* line1 = lv_line_create(lv_scr_act(), NULL);
    lv_obj_add_style(line1, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
    lv_line_set_points(line1, line_points, /*sizeof(line_points)/sizeof(lv_point_t)*/5);     /*Set the points*/
    lv_obj_align(line1, NULL, LV_ALIGN_CENTER, 0, 0);
}

/*转圈显示字体 */
int num=0;
lv_obj_t * label1;
void ArcnumTaskCb(lv_task_t *t)
{
	static int a=0;
	a+=2;
	if(a>=360) a=0;
	lv_arc_set_angles(t->user_data,0,a);
	num=a*100/360;
	lv_label_set_text_fmt(label1,"#ffffff %d ", num); 	
	
	
}

void lv_circle_num_show(void)
{
	//全景设置 背景为黑色
	lv_obj_t *obj_t = lv_obj_create(lv_scr_act(),NULL);
	lv_obj_clean_style_list(obj_t, LV_OBJ_PART_MAIN);
	lv_obj_set_size(obj_t,LV_HOR_RES_MAX,LV_VER_RES_MAX);
	lv_obj_set_style_local_bg_color(obj_t,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_BLACK);

	/*字条style*/
	static lv_style_t font_style;
	lv_style_init(&font_style);
	lv_style_set_text_font(&font_style, LV_STATE_DEFAULT, &lv_font_montserrat_30);

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
	lv_obj_t *arc = lv_arc_create(lv_scr_act(),NULL);
	lv_obj_set_style_local_border_opa(arc,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_OPA_TRANSP);
	lv_obj_set_style_local_bg_color(arc,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_BLACK);
	
	/*将style添加到arc中*/
	lv_obj_add_style(arc,LV_ARC_PART_BG, &style_bg);
	lv_obj_add_style(arc,LV_ARC_PART_INDIC, &style_fg); 
	lv_arc_set_rotation(arc, 270); //旋转270度

	lv_obj_set_size(arc, 135, 135);
	lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 0);	
	

	//设置文本标签
	label1 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_recolor(label1, true);
	lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK);
	// lv_obj_set_width(label1, 150);
	lv_obj_set_size(label1,135,60);
	lv_obj_add_style(label1, LV_OBJ_PART_MAIN, &font_style);
	lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);
	lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
	
	lv_task_create(ArcnumTaskCb, 20, LV_TASK_PRIO_LOWEST, arc);//创建了一个20ms，优先级为最低的ArcTaskCb重绘任务，并向任务的user_data参数传递arc指针
}

/*背景渐变色*/
void lv_grad_color_show()
{
	//全景设置 背景为黑色
	lv_obj_t *obj_t = lv_obj_create(lv_scr_act(),NULL);
	lv_obj_clean_style_list(obj_t, LV_OBJ_PART_MAIN);
	lv_obj_set_size(obj_t,240,320);	

	lv_obj_set_style_local_bg_opa(obj_t, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER); 	//设置背景不透明
	lv_obj_set_style_local_bg_color(obj_t, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);	//设置背景颜色为灰色
	lv_obj_set_style_local_bg_grad_color(obj_t, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);	//设置渐变色为蓝色
    lv_obj_set_style_local_bg_grad_dir(obj_t, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);	//设置渐变发现为横向
    lv_obj_set_style_local_bg_main_stop(obj_t, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);    //设置渐变主停止位置为100
    lv_obj_set_style_local_bg_grad_stop(obj_t, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 200);    //设置渐变停止位置为200
}

/*动画显示*/
void lv_anim_show()
{
	//全景设置 背景为黑色
	lv_obj_t *obj_t = lv_obj_create(lv_scr_act(),NULL);
	lv_obj_clean_style_list(obj_t, LV_OBJ_PART_MAIN);
	lv_obj_set_size(obj_t,135,240);
	lv_obj_set_style_local_bg_color(obj_t, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

	//蒙版初始化
	lv_obj_t * om = lv_objmask_create(obj_t, NULL);
	lv_obj_set_size(om, 135, 240);
	// lv_obj_set_style_local_bg_color(om, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
	// lv_obj_align(om, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

	/*创建圆对象*/
	lv_obj_t *obj = lv_arc_create(om, NULL);		//父类为蒙版
	lv_obj_set_style_local_bg_opa(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	//设置背景透明
	lv_obj_set_style_local_border_opa(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	//设置边界线透明
	lv_obj_set_style_local_line_opa(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
	lv_arc_set_angles(obj, 0, 360);
	lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);

	//创建背景style
	static lv_style_t style_fg;
	lv_style_reset(&style_fg);
	lv_style_init(&style_fg);
	lv_style_set_line_color(&style_fg, LV_STATE_DEFAULT, LV_COLOR_MAGENTA);		//设置前景线条颜色为橙色
	lv_style_set_line_width(&style_fg, LV_STATE_DEFAULT, 9);				//设置前景线条宽度为9
	lv_style_set_line_rounded(&style_fg, LV_STATE_DEFAULT,1);

	lv_obj_add_style(obj, LV_ARC_PART_INDIC, &style_fg);

	/*创建动画对象*/
	lv_anim_t a;
	lv_anim_init(&a);
	lv_anim_set_var(&a, obj); 		//设置变量到动画对象
	lv_anim_set_exec_cb(&a,(lv_anim_exec_xcb_t)lv_obj_set_y);	/* 设置“动画制作”功能 */

	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_bounce);
	lv_anim_set_path(&a, &path);

	lv_anim_set_time(&a, 500); 		//设置动画时长 ms
	lv_anim_set_values(&a, -10, 120);		// 设置开始和结束值。 0-200 
	lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); 	//设置动画重复时间
	lv_anim_set_repeat_delay(&a, 500); 	//设置每次动画间隔 500ms
	lv_anim_set_playback_time(&a, 500);
	lv_anim_start(&a);	

	
	lv_area_t r;
	lv_draw_mask_fade_param_t f1;
	r.x1 = 0;
	r.y1 = 0;
	r.x2 = 135;
	r.y2 = 50;	//渐变区域
	lv_draw_mask_fade_init(&f1, &r, LV_OPA_TRANSP, 0, LV_OPA_COVER, 50);
	lv_objmask_add_mask(om, &f1);	

	r.x1 = 0;
	r.y1 = 190;
	r.x2 = 135;
	r.y2 = 240;
	lv_draw_mask_fade_init(&f1, &r, LV_OPA_COVER, 190, LV_OPA_TRANSP, 240);
	lv_objmask_add_mask(om, &f1);
}

#define MASK_WIDTH 100
#define MASK_HEIGHT 50
void lv_ex_objmask_2(void)
{
	/* Create the mask of a text by drawing it to a canvas*/
	static lv_opa_t mask_map[MASK_WIDTH * MASK_HEIGHT];
	/*Create a "8 bit alpha" canvas and clear it*/
	lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas, mask_map, MASK_WIDTH, MASK_HEIGHT, LV_IMG_CF_ALPHA_8BIT);
	lv_canvas_fill_bg(canvas, LV_COLOR_BLACK, LV_OPA_TRANSP);
	/*Draw a label to the canvas. The result "image" will be used as mask*/
	lv_draw_label_dsc_t label_dsc;
	lv_draw_label_dsc_init(&label_dsc);
	label_dsc.color = LV_COLOR_WHITE;
	lv_canvas_draw_text(canvas, 5, 5, MASK_WIDTH, &label_dsc, "Text with gradient", LV_LABEL_ALIGN_CENTER);
	/*The mask is reads the canvas is not required anymore*/
	lv_obj_del(canvas);
	/*Create an object mask which will use the created mask*/
	lv_obj_t * om = lv_objmask_create(lv_scr_act(), NULL);
	lv_obj_set_size(om, MASK_WIDTH, MASK_HEIGHT);
	lv_obj_align(om, NULL, LV_ALIGN_CENTER, 0, 0);
	/*Add the created mask map to the object mask*/
	lv_draw_mask_map_param_t m;
	lv_area_t a;
	a.x1 = 0;
	a.y1 = 0;
	a.x2 = MASK_WIDTH - 1;
	a.y2 = MASK_HEIGHT - 1;
	lv_draw_mask_map_init(&m, &a, mask_map);
	lv_objmask_add_mask(om, &m);
	/*Create a style with gradient*/
	static lv_style_t style_bg;
	lv_style_init(&style_bg);
	lv_style_set_bg_opa(&style_bg, LV_STATE_DEFAULT, LV_OPA_COVER);
	lv_style_set_bg_color(&style_bg, LV_STATE_DEFAULT, LV_COLOR_RED);
	lv_style_set_bg_grad_color(&style_bg, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_style_set_bg_grad_dir(&style_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	/* Create and object with the gradient style on the object mask.
	* The text will be masked from the gradient*/
	lv_obj_t * bg = lv_obj_create(om, NULL);
	lv_obj_reset_style_list(bg, LV_OBJ_PART_MAIN);
	lv_obj_add_style(bg, LV_OBJ_PART_MAIN, &style_bg);
	lv_obj_set_size(bg, MASK_WIDTH, MASK_HEIGHT);
}
void lv_ex_label_1(void)
{
	lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
	lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
	lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
	lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label "
	"and  wrap long text automatically.");
	lv_obj_set_width(label1, 120);
	lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -30);
	lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
	lv_obj_set_width(label2, 120);
	lv_label_set_text(label2, "It is a circularly scrolling text. ");
	lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);
}

// static void event_handler(lv_obj_t * obj, lv_event_t event)
// {
// 	if(event == LV_EVENT_VALUE_CHANGED) {
// 		char buf[32];
// 		lv_roller_get_selected_str(obj, buf, sizeof(buf));
// 		printf("Selected month: %s\n", buf);
// 	}
// }

static void task_roller(lv_task_t *t)
{
	static int i;
	i++;
	lv_roller_set_selected(t->user_data, i, LV_ANIM_ON);
	
}
void lv_ex_roller_1(void)
{
	lv_obj_t *roller1 = lv_roller_create(lv_scr_act(), NULL);
	lv_obj_set_style_local_bg_color(roller1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_set_style_local_text_color(roller1,LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_set_style_local_border_color(roller1,LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
	lv_roller_set_options(roller1,
						  "January\n"
						  "February\n"
						  "March\n"
						  "April\n"
						  "May\n"
						  "June\n"
						  "July\n"
						  "August\n"
						  "September\n"
						  "October\n"
						  "November\n"
						  "December",
						  LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(roller1, 2);
	lv_obj_align(roller1, NULL, LV_ALIGN_CENTER, 0, 0);
	// lv_obj_set_event_cb(roller1, event_handler);
	lv_roller_set_anim_time(roller1, 50);
	lv_task_create(task_roller, 1000, LV_TASK_PRIO_MID, roller1);
	// lv_obj_set_style_(roller1,LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_YELLOW);
}