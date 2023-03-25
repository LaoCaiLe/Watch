#include "Task.h"
#include "mpu6050.h"
#include "Scene.h"

static float get_temprature(void)
{
    return MPU_Get_Temperature();
}

void temp_task(lv_task_t *t)
{
    float temp = get_temprature();
    lv_label_set_text_fmt(label_temp, "%02d 'C",(int)temp-10);

}