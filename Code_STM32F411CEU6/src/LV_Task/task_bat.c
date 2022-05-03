#include "Task.h"
#include "lcd.h"
#include "lcd_init.h"
#include "Scene.h"
#include "task_bat.h"
float power_val;  //电池电量


void Bat_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef       ADC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟

    //先初始化ADC1通道5 IO口
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PA1 通道1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//充电检测引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  
    
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 
 
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
    ADC_CommonInit(&ADC_CommonInitStructure);//初始化
        
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
    ADC_InitStructure.ADC_NbrOfConversion = 2;//1个转换在规则序列中 也就是只转换规则序列1 
    ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
}

int Get_power(int ch)
{
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles);	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_power(ch);
	}
	return temp_val/times;
} 

void bat_task(lv_task_t *t)
{
    float val;
    char buf[10];
    static bool ChargeFlag=false;
    static bool Is_beepon = false;

    //图标显示
    int temp = Get_Adc_Average(0,5);
   
    if(temp<1000)    
    {
        ChargeFlag = true;
        lv_img_set_src(img_battery, &img_charge);
    }        
    else 
    {
        val = Get_Adc_Average(1,5)*0.0016 ;
        // lv_label_set_text_fmt(label_bat, "%.1f", val);
        ChargeFlag = false;
        Is_beepon = false;
        
        if(val<3.3)
            lv_img_set_src(img_battery, &img_battery_0);
        else if(val<3.5)
            lv_img_set_src(img_battery, &img_battery_1);
        else if(val<3.7)
            lv_img_set_src(img_battery, &img_battery_2);
        else if(val<3.9)
            lv_img_set_src(img_battery, &img_battery_3);
        else 
            lv_img_set_src(img_battery, &img_battery_4);
        // sprintf(buf, "val=%.1f", val);
        // LCD_ShowString(0, 0, buf, RED, BLACK, 24, 0);
    }

    if(ChargeFlag&&!Is_beepon)
    {
	    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器3更新中断
        lv_task_create(Beep_charge_task, 1, LV_TASK_PRIO_LOW, NULL);    //USB插入充电音效
        Is_beepon = true;
    }
}