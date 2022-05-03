#include "task_step.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "Scene.h"
#include "led.h"
u32 stepCount;


// float val2;
void step_task(lv_task_t *t)
{
    led3 = !led3;
    // dmp_get_pedometer_step_count(&stepCount);
    // mpu_dmp_get_data(NULL, &val2, NULL);

    // lv_label_set_text_fmt(label_step, "#ff0000 /# #ffffff %d",stepCount);

}