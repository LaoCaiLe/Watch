#include "Task.h"
#include "mpu6050.h"
#include "mpu_i2c.h"
#include "inv_mpu.h"
#include "led.h"
#include "Scene.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "lcd.h"

bool Is_PowerSave=true;  //省电模式
bool LCD_State=true; //屏幕状态

static void Lcd_BLK_Off(lv_task_t *t)       //屏幕熄灭任务
{
    // static int i = Bright;
    // i -= 15;
    TIM3->CCR4 -= 15;
    if(TIM3->CCR4<=0)
    {
        TIM3->CCR4 = 0;
        lv_task_del(t);
    }
}
static void Lcd_BLK_On(lv_task_t *t)    //屏幕打开任务
{


    TIM3->CCR4 += 15; 
    if(TIM3->CCR4>=7000)
    {
        lv_task_del(t);
       
    }
    
}

void mpu_task(lv_task_t *t)
{
    float temp[5],all,roll; 		//欧拉角
    char buf[20];
    static int i=0;
    if(Is_PowerSave)
    {
        mpu_dmp_get_data(NULL, &roll, NULL);
        // mpu_dmp_get_data(NULL, &temp[i], NULL);
        // if(temp[i]<0)
        //     temp[i] += 360;
        // all += temp[i];
        // i++;
        // if(i==5)
        {
            // i = 0;
            // roll = all / 5.0;
            sprintf(buf, "roll=%.2f", roll);
            LCD_ShowString(0,0,buf,RED,BLACK,24,0);
            // if(roll==0)
            // {

            // }
            // else if((roll>155.0&&roll<215.0)&&!LCD_State)    //角度小于一定值并且屏幕关闭，打开屏幕
            // {
            //     lv_task_create(Lcd_BLK_On, 2, LV_TASK_PRIO_LOW, NULL);
            //     // led1 = 1;
            //     LCD_State = true;
            //     TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器3更新中断
            //     lv_task_create(Beep_charge_task, 1, LV_TASK_PRIO_LOW, NULL);    //USB插入充电音效
            // }
            // else if((roll<155.0||roll>215.0)&&LCD_State)     //角度大于一定值并且屏幕打开，关闭屏幕
            // {
            //     lv_task_create(Lcd_BLK_Off, 2, LV_TASK_PRIO_LOW, NULL);
            //     // led1 = 0;
            //     LCD_State = false;

            //     TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器3更新中断
            //     lv_task_create(Beep_hour_task, 1, LV_TASK_PRIO_LOW, NULL);    //USB插入充电音效
            // }
        }
        
    }
    //     mpu_dmp_get_data(NULL, &roll, NULL);
    // // val = Get_power(0);
    //     sprintf(buf, "val1=%.2f", all/5.0);
    //     LCD_ShowString(0, 0, buf, RED, BLACK, 24, 0);
}