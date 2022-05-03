#ifndef __SCENE_H
#define __SCENE_H

#include "Scene_Select.h"
#include "Scene_Main.h"
#include "Scene_Timer.h"
#include "Scene_Alarm.h"
#include "Scene_Lighting.h"
#include "Scene_Setting.h"
#include "key_task.h"



extern void Main_KeyFir_Func();
extern void Main_KeySec_Func();
extern void Main_KeyCancel_Func();

extern void Select_KeyFir_Func();
extern void Select_KeySec_Func();
extern void Select_KeyCancel_Func();

extern void Timer_KeyFir_Func();
extern void Timer_KeySec_Func();
extern void Timer_KeyCancel_Func();

extern void Lighting_KeyFir_Func();
extern void Lighting_KeySec_Func();
extern void Lighting_KeyCancel_Func();

extern void Alarm_KeyFir_Func();
extern void Alarm_KeySec_Func();
extern void Alarm_KeyCancel_Func();

extern void Setting_KeyFir_Func();
extern void Setting_KeySec_Func();
extern void Setting_KeyCancel_Func();
#endif // !__SCENE_H
