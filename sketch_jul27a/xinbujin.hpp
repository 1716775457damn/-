#include <AccelStepper.h>

// 步进电机参数
#define MOTOR_INTERFACE_TYPE 1 // 接口类型，1为单步模式
#define STEP_PIN1 11            // 步进信号引脚
#define DIR_PIN1 13             // 方向信号引脚
#define ENABLE_PIN1 10          // 使能信号引脚
#define STEP_PIN2 28           // 步进信号引脚
#define DIR_PIN2 30             // 方向信号引脚
#define ENABLE_PIN2 25          // 使能信号引脚

// 定义步进电机对象
AccelStepper stepper1(MOTOR_INTERFACE_TYPE, STEP_PIN2, DIR_PIN2, ENABLE_PIN2);
AccelStepper stepper2(MOTOR_INTERFACE_TYPE, STEP_PIN2, DIR_PIN2, ENABLE_PIN2);
AccelStepper stepper3(MOTOR_INTERFACE_TYPE, STEP_PIN2, DIR_PIN2, ENABLE_PIN2);
AccelStepper stepper4(MOTOR_INTERFACE_TYPE, STEP_PIN1, DIR_PIN1, ENABLE_PIN1);

// 电机参数设置 
float maxSpeed1;               // 最大速度 (steps per second)
const float acceleration1 = 2000.0; // 加速度 (steps per second^2)
int stepsToMove1;              // 移动步数

float maxSpeed2;              // 最大速度 (steps per second)
const float acceleration2 = 1600.0; // 加速度 (steps per second^2)
int stepsToMove2;              // 移动步数

float maxSpeed3;              // 最大速度 (steps per second)
const float acceleration3 = 2000.0; // 加速度 (steps per second^2)
int stepsToMove3;              // 移动步数

float maxSpeed4;              // 最大速度 (steps per second)
const float acceleration4 = 2000.0; // 加速度 (steps per second^2)
int stepsToMove4;              // 移动步数



void tigao()
{
  // 设置目标位置并启动电机
  stepper1.moveTo(1700);

  // 运行电机
  while (stepper1.distanceToGo() != 0)
  {
    stepper1.run();
  }
}

void tigao1()
{
  // 设置目标位置并启动电机
  stepper1.moveTo(6000);

  // 运行电机
  while (stepper1.distanceToGo() != 0)
  {
    stepper1.run();
  } 
}
void huishou()
{
  // 设置目标位置并启动电机
  stepper2.moveTo(-3000);

  // 运行电机
  while (stepper2.distanceToGo() != 0)
  {
    stepper2.run();
  } 
}



void yunxin2()
{
  // 设置目标位置并启动电机
  stepper1.moveTo(2900);

  // 运行电机
  while (stepper1.distanceToGo() != 0)
  {
    stepper1.run();
  }
}

void yunxin2d()
{
  // 设置目标位置并启动电机
  stepper1.moveTo(9000);

  // 运行电机
  while (stepper1.distanceToGo() != 0)
  {
    stepper1.run();
  }  
}

void yunxin2c()
{
  // 设置目标位置并启动电机
  stepper2.moveTo(-3000);

  // 运行电机
  while (stepper2.distanceToGo() != 0)
  {
    stepper2.run();
  }
}
void yunxin2b()//cunfang
{
  // 设置目标位置并启动电机
  stepper4.moveTo(0);

  // 运行电机
  while (stepper4.distanceToGo() != 0)
  {
    stepper4.run();
  }
}

void yunxin2a()
{
    // 设置目标位置并启动电机
  stepper4.moveTo(-2700);

  // 运行电机
  while (stepper4.distanceToGo() != 0)
  {
    stepper4.run();
  }   
}

//void yunxin2()
//{
//  // 设置目标位置并启动电机
//  stepper2.moveTo(stepsToMove2);
//
//  // 运行电机
//  while (stepper2.distanceToGo() != 0)
//  {
//    stepper2.run();
//  }
//}

void yunxin3()
{
  // 设置目标位置并启动电机
  stepper3.moveTo(stepsToMove3);

  // 运行电机
  while (stepper3.distanceToGo() != 0)
  {
    stepper3.run();
  }
}

void yunxin4()
{
  // 设置目标位置并启动电机
  stepper4.moveTo(stepsToMove4);

  // 运行电机
  while (stepper4.distanceToGo() != 0)
  {
    stepper4.run();
  }
}
