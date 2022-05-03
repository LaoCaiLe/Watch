#ifndef __PWM_H
#define __PWM_H

#include "stm32f4xx.h"

void tim1_pwm_init(uint16_t per, uint16_t psc);
void tim2_pwm_init(uint16_t per, uint16_t psc);
void tim3_pwm_init(uint16_t per, uint16_t psc);
#endif