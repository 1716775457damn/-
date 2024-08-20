#include <steeper.h>
#include <servo1.h>
#include<Arduino.h>
#include<sensor.h>
#include<task.h>






void route()
{
  // 工业流程控制框架，可根据自身需求增加case 数量
  switch (routecontrol)
  {

  case 0: // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
    task1();
    break;

  case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
    task2();
    break;

  case 2: // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
    task6();
    break;

  case 3: // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
    task3();
    break;

  case 4:
    task4();
    break;

  case 5:
    task2b();
    break;

  case 6:
    task6b();
    break;

  case 7:
    task3b();
    break;

  case 8:
    task4b();
    break;
  }
}
void setup()
{
  Serial.begin(115200); // 串口0波特率115200, 接串口屏
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(14, INPUT);
  pinMode(27, INPUT);
  pinMode(26, INPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(servoPin1, OUTPUT);
  servo1(105); // 假设servo1是控制舵机的函数
}
void loop()
{
  route();
}
