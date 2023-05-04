# Watch

毕业设计智能手环

![Main_Scene](https://user-images.githubusercontent.com/70246846/227701753-35052132-d3d5-47de-9e95-39b077187813.jpg)
![IMG_20220511_123037](https://user-images.githubusercontent.com/70246846/227701957-23137809-59ea-498f-b79e-4d6e6e7adfef.jpg)


# 0. 开发

- 软件开发：vscode（EIDE插件）
- 硬件开发：AD20

# 1. 软件

- STM32F4 标准库
- LVGL 界面库（v7.11.0)

# 2. 硬件

- 主控：STM32F411CEU6
- 陀螺仪：MPU6050
- 电源降压：RT9193
- 电池充电：TP4056
- LCD屏：ST7789 135*240 1.14inch
- 蜂鸣器：5020 无源
- 电池：3.17Li 500mAh
# 3. 功能

- 可以显示年月日，时分秒的时间日期信息；
- 可以显示温度数据，用户步数数据；
- 可以实时显示手环电池电量，充电时有声音提示和图标提示；
- 可以通过按键切换各个功能界面
- 秒表功能，可精准定时和多次计次；
- 闹钟功能，可设置时间星期，同时可设计闹钟铃声；
- 游戏功能，通过陀螺仪体感进行游戏；
- 时间设置功能，可进行时间日期的校准；

# 4. todo

- stm32芯片VBAT引脚接降压芯片输出持续供电，可保证掉电计时
- 温度精度
- 陀螺仪代码优化
- 体感熄屏
- UI界面优化



# 5. 致谢
- https://github.com/lvgl/lvgl
- https://github.com/FASTSHIFT/WatchX
- https://github.com/tianxiaohuahua/Twantch





