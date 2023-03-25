#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"
#include "sys.h"

#define led1 PCout(13)
#define led2 PBout(14)
#define led3 PBout(5)

#define LED1_PIN GPIO_Pin_13
#define LED2_PIN GPIO_Pin_14
#define LED3_PIN GPIO_Pin_5


void LED_Init();

#endif