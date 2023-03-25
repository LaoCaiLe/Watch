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
#include "usart.h"	
#include "rtc.h"
#include "pwm.h"
#include "timer.h"
#include "../GUI/lvgl/lvgl.h"
#include "lv_port_disp.h"
#include "Scene.h"
#include "LVGL_test.h"
#include "mpu6050.h"
#include "mpu_i2c.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"


int main(void)
{

  Hardware_init();      //硬件驱动及外设初始化

  selection_init();     //选择界面初始化
  Timer_init();         //秒表界面初始化
  Lighting_init();      //亮度调节界面初始化
  game_init();          //游戏界面初始化
  Alarm_init();         //闹钟界面初始化
  Setting_init();       //时间设置界面初始化

  mainMenu_init();      //主界面初始化

  MenuScene = &Scene_MainScence;  //显示界面选择主界面

  lv_task_create(key_task, 30, LV_TASK_PRIO_HIGH, NULL);    //按键任务创建
  lv_task_create(bat_task, 500, LV_TASK_PRIO_LOW, NULL);    //电池电量检测和充电检测任务创建
  lv_task_create(step_task, 1000, LV_TASK_PRIO_LOW, NULL);  //步数检测任务
  // lv_task_create(mpu_task, 100, LV_TASK_PRIO_MID, NULL);    //陀螺仪检测任务
  lv_task_create(temp_task, 3000, LV_TASK_PRIO_LOW, NULL);  //温度检测任务

  while (1)
  {
    lv_task_handler();
  }
}



