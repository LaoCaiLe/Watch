#include "task_beep.h"
#include "timer.h"

static void beep_handler(void);

int beep_duty;
bool alarm_stop = false;
void Beep_init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure MCO2 pin(PC9) in alternate function */
    GPIO_InitStructure.GPIO_Pin = Beep_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_Init(GPIOC, &GPIO_InitStructure);


    Timer_InitDef TIM4_conf=   //定时器初始化
    {
      .TIMx = TIM4,
      .us   = 10,
      .NVIC_Priority = 0,
      .event_handler = beep_handler,
    };
    timer_init(&TIM4_conf);

    TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE); //允许定时器4更新中断
}

void beep_handler()
{
    static int i = 0;
    i++;
    if(i<beep_duty*25/100)
        Beep = 1;
    else
        Beep = 0;
    
    if(i>=25)
        i = 0;
        
}

void Beep_charge_task(lv_task_t *t)    //充电音效
{
    static int i;
    i++;
    if(i>0&&i<100)
        beep_duty = 25;
    else if(i>160&&i<240)
        beep_duty = 40;
    else
        beep_duty = 0;
    if(i>=240)
    { 
        i = 0;
	    TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE); //允许定时器4更新中断
        lv_task_del(t);
    }
}

void Beep_alarm1_task(lv_task_t *t)    //闹钟音效
{
    static int i;
    static int j;

    i++;
    if (i > 0 && i < 100)
        beep_duty = 25;
    else if (i > 200 && i < 500)
        beep_duty = 95;
    else
        beep_duty = 0;
    if (i >= 800)
    {
        i = 0;
        j++;
    }
    
    if(j==5 ||(alarm_stop&&j>2))
    {
        i = 0;
        j = 0;
        alarm_stop = false;

        TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE); //允许定时器4更新中断
        lv_task_del(t);
    }
}

void Beep_alarm2_task(lv_task_t *t)    //闹钟音效
{
    static int i;
    static int j;

    i++;
    if (i > 0 && i < 100)
        beep_duty = 25;
    else if (i > 200 && i < 300)
        beep_duty = 40;
    else if (i > 400 && i < 500)
        beep_duty = 25;
    else
        beep_duty = 0;
    if (i >= 800)
    {
        i = 0;
        j++;
    }
    
    if(j==5||(alarm_stop&&j>2))
    {
        i = 0;
        j = 0;
        alarm_stop = false;
        TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE); //允许定时器4更新中断
        lv_task_del(t);
    }
}

void Beep_alarm3_task(lv_task_t *t)    //闹钟音效
{
    static int i;
    static int j;

    i++;
    if (i > 0 && i < 100)
        beep_duty = 25;
    else if (i > 200 && i < 300)
        beep_duty = 40;
    else if (i > 400 && i < 500)
        beep_duty = 25;
    else if (i > 600 && i < 700)
        beep_duty = 60;   
    else
        beep_duty = 0;
    if (i >= 1200)
    {
        i = 0;
        j++;
    }
    
    if(j==5||(alarm_stop&&j>2))
    {
        i = 0;
        j = 0;
        alarm_stop = false;
    
        TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE); //允许定时器4更新中断
        lv_task_del(t);
    }
}

void Beep_hour_task(lv_task_t *t)    //时间整点音效
{
    static int i;
    i++;
    if(i>0&&i<100)
        beep_duty = 25;    
    else
        beep_duty = 0;
    if(i>=100)
    { 
        i = 0;
	    TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE); //允许定时器4更新中断
        lv_task_del(t);
    }
}

