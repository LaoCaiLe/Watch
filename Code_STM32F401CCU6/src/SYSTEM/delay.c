/*
 * MIT License
 * Copyright (c) 2019 _VIFEXTech
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "delay.h"
//#include "Arduino.h"

#define SysTick_LoadValue (F_CPU / 1000U)

volatile static uint32_t System_ms = 0;

/**
  * @brief  ϵͳ�δ�ʱ����ʼ������ʱ1ms
  * @param  ��
  * @retval ��
  */
void Delay_Init(void)
{    
    SystemCoreClockUpdate();
    SysTick_Config(SysTick_LoadValue);
    NVIC_SetPriority(SysTick_IRQn, 0);
}

/**
  * @brief  ϵͳ�δ�ʱ���ж����
  * @param  ��
  * @retval ��
  */
void SysTick_Handler(void)
{
    System_ms++;
}

/**
  * @brief  ��ȡ��Ƭ�����ϵ����������ĺ�����
  * @param  ��
  * @retval ��ǰϵͳʱ�Ӻ�����
  */
uint32_t millis(void)
{
   return System_ms;
//    return 0;
}

/**
  * @brief  ��ȡ��Ƭ�����ϵ�����������΢����
  * @param  ��
  * @retval ��ǰϵͳʱ��΢����
  */
uint32_t micros(void)
{
    return (System_ms * 1000 + (SysTick_LoadValue - SysTick->VAL) / CYCLES_PER_MICROSECOND);
}

/**
  * @brief  ���뼶��ʱ
  * @param  ms: Ҫ��ʱ�ĺ�����
  * @retval ��
  */
void delay_ms(uint32_t ms)
{
    uint32_t Stop_TimePoint = System_ms + ms;
    while(System_ms < Stop_TimePoint);
}

/**
  * @brief  ΢�뼶��ʱ
  * @param  us: Ҫ��ʱ��΢����
  * @retval ��
  */
void delay_us(uint32_t us)
{
    uint32_t total = 0;
    uint32_t target = CYCLES_PER_MICROSECOND * us;
    int last = SysTick->VAL;
    int now = last;
    int diff = 0;
start:
    now = SysTick->VAL;
    diff = last - now;
    if(diff > 0)
    {
        total += diff;
    }
    else
    {
        total += diff + SysTick_LoadValue;
    }
    if(total > target)
    {
        return;
    }
    last = now;
    goto start;
}
