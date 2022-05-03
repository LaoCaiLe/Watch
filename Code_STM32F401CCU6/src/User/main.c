/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "led.h"
#include "lcd_init.h"
#include "lcd.h"
#include "delay.h"
#include "key.h"
#include "key.h"
#include "usart.h"	
#include "rtc.h"
#include "pwm.h"
#include "timer.h"
#include "../GUI/lvgl/lvgl.h"
#include "lv_port_disp.h"
#include "Scene.h"
#include "LVGL_test.h"



void tim_lv_tick(void);

int main(void)
{  
    Delay_Init();
    LED_Init();
    KEY_Init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
    
    tim3_pwm_init(7200, 1);
   
    My_RTC_Init();
    RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//配置WAKE UP中断,1秒钟中断一次

    Timer_InitDef TIM_2_conf =
    {
      .TIMx = TIM2,
      .ms = 1,
      .NVIC_Priority = 0,
      .event_handler = tim_lv_tick,
    };
    timer_init(&TIM_2_conf);    

    lv_init(); //lvgl 系统初始化
	  lv_port_disp_init(); //lvgl 显示接口初始化,	放在lv_init()的后面

    // lv_demo_img();
    // lv_symbol_show();
    // lv_ex_label_1();
    // lv_circle_show();
    // lv_anim_show();
    // lv_circle_num_show();
    // lv_ex_roller_1();

    mainMenu_init();
    selection_init();
    // Timer_init();
    // Lighting_init();
    // Alarm_init();
    // Setting_init();

    MenuTask = &Task_MainScence;
    // MenuTask = &Task_Setting;    
    lv_obj_move_foreground(MenuTask->obj);
    lv_task_create(key_thread, 30, LV_TASK_PRIO_HIGH, NULL);

    while(1)
    {      
      lv_task_handler();
      // led1 = !led1;
      // delay_ms(100);
    }
}

void tim_lv_tick()
{
    lv_tick_inc(1); // lvgl 的 1ms 心跳
}
