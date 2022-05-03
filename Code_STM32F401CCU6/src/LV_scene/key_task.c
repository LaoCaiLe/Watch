#include "key_task.h"
#include "key.h"
#include "Scene.h"
#include "led.h"
#include "lcd.h"

uint8_t Key;
bool key_mode=false;

struct ButtonTask *MenuTask = NULL;


struct ButtonTask Task_Select = {
    Select_KeyFir_Func,     Select_KeySec_Func,     Select_KeyCancel_Func};

struct ButtonTask Task_MainScence = {
    Main_KeyFir_Func,       Main_KeySec_Func,       Main_KeyCancel_Func};

struct ButtonTask Task_Alarm = {
    Alarm_KeyFir_Func,      Alarm_KeySec_Func,      Alarm_KeyCancel_Func};

struct ButtonTask Task_Lighting = {
    Lighting_KeyFir_Func,   Lighting_KeySec_Func,   Lighting_KeyCancel_Func};

// struct ButtonTask Task_Game = {
//     Game_KeyFir_Func,       Game_KeySec_Func,       Game_KeyCancel_Func};

struct ButtonTask Task_Timer = {
    Timer_KeyFir_Func,      Timer_KeySec_Func,      Timer_KeyCancel_Func};

struct ButtonTask Task_Setting = {
    Setting_KeyFir_Func,    Setting_KeySec_Func,    Setting_KeyCancel_Func};

void key_thread(lv_task_t *t)
{
    Key = KEY_Scan(key_mode);
    
    switch (Key)
    {
        case KEY_LEFT:
            MenuTask->KeyFir_Func();
            led1 = !led1;
            break;
        case KEY_DOWN:
            MenuTask->KeySec_Func();
            led1 = !led1;
            break;
        case KEY_RIGHT:
            MenuTask->KeyCancel_Func();
            led1 = !led1;
            break;
    }
}

void Scene_init()
{
    
}