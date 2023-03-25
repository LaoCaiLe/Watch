#ifndef _HARDWARE_H
#define _HARDWARE_H

#include "led.h"
#include "lcd_init.h"
#include "lcd.h"
#include "delay.h"
#include "usart.h"	
#include "rtc.h"
#include "pwm.h"
#include "timer.h"
#include "mpu6050.h"
#include "mpu_i2c.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Hardware_init(void);

#endif