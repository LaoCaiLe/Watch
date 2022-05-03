#include "hardware.h"

static void tim_lv_tick(void);
 
void Hardware_init()
{
    delay_init(100);
    LED_Init(); //LED初始化 B5
    tim3_pwm_init(7200, 1); //LCD背光 B1
    KEY_Init(); //按键初始化 B12 B13 B14
    LCD_Init(); //LCD屏初始化 A4 A5 A6 A7 B0 
    LCD_Fill(0, 0, LCD_W, LCD_H, BLACK);
    Bat_init(); //电池 A0 A1
    Beep_init();
    while(MPU_Init()); //陀螺仪初始化 B9 B8
    while(mpu_dmp_init());

    My_RTC_Init();    //RTC时钟初始化
    RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//配置WAKE UP中断,1秒钟中断一次
   
    Timer_InitDef TIM_2_conf=   //定时器初始化
    {
      .TIMx = TIM2,
      .us   = 1000,
      .NVIC_Priority = 0,
      .event_handler = tim_lv_tick,
    };
    timer_init(&TIM_2_conf);    
        
    lv_init(); //lvgl 系统初始化
    lv_port_disp_init(); //lvgl 显示接口初始化,	放在lv_init()的后面

}

void tim_lv_tick()
{
    lv_tick_inc(1); // lvgl 的 1ms 心跳
}
