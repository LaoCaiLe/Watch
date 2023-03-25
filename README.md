# WatchX 

毕业设计智能手环

# 0. 开发

软件开发：vscode（EIDE插件）

硬件开发：AD20

# 1. 软件

STM32F4 标准库

LittleVGL 界面库（lvgl7.11）

# 2. 硬件

主控：STM32F411CEU6

陀螺仪：MPU6050

电源降压：RT9193

电池充电：TP4056

LCD屏：ST7789 135*240 1.14inch

蜂鸣器：5020 无源

电池：3.17Li 500mAh

# 3. 功能

- 可以显示年月日，时分秒的时间日期信息；
- 可以显示温度数据，用户步数数据；
- 可以实时显示手环电池电量，充电时有声音提示和图标提示；
- 可以通过按键切换各个功能界面
- 秒表功能，可精准定时和多次计次；
- 闹钟功能，可设置时间星期，同时可设计闹钟铃声；
- 游戏功能，通过陀螺仪体感进行游戏；
- 时间设置功能，可进行时间日期的校准；

# 3. todo

1. stm32芯片VBAT引脚接降压芯片输出持续供电，可保证掉电计时
2. 温度精度
3. 陀螺仪代码优化
4. 体感熄屏
5. UI界面优化

# 4. pic

主界面
![IMG_20220511_124330](https://user-images.githubusercontent.com/70246846/227701416-6dec3fab-a84c-424e-b033-8c3e48573ba1.jpg)

![IMG_20220511_123037](https://user-images.githubusercontent.com/70246846/227701419-49a38e99-5ddf-4099-918b-34509b818300.jpg)

选择界面
![IMG_20230325_142739](https://user-images.githubusercontent.com/70246846/227701386-b7474aac-bbaa-4f06-b4d0-cb3ecc9a7b10.jpg)

亮度调节界面
![IMG_20230325_142746](https://user-images.githubusercontent.com/70246846/227701491-f4d95a64-bdaa-479f-af49-7553e9806fa9.jpg)

游戏界面
![IMG_20230325_142754](https://user-images.githubusercontent.com/70246846/227701401-8b27e79b-f3a9-4861-be81-019f238024ee.jpg)

秒表界面
![IMG_20230325_142835](https://user-images.githubusercontent.com/70246846/227701404-317a98ab-9a43-4fd3-b34b-6f192aeac4d4.jpg)

时间设置界面
![IMG_20230325_142845](https://user-images.githubusercontent.com/70246846/227701405-75b7846f-58db-4a99-9173-df66ad6de0e7.jpg)

闹钟界面
![IMG_20230325_142938](https://user-images.githubusercontent.com/70246846/227701409-7b1d6be4-82f1-4799-87db-3ed38a51365a.jpg)


# 5. 致谢

https://github.com/FASTSHIFT/WatchX

https://github.com/lvgl/lvgl



