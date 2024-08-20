#include <AccelStepper.h>
// 步进电机1参数
#define STEP_PIN_1 18
#define DIR_PIN_1 19
#define ENABLE_PIN_1 21

// 步进电机2参数
#define STEP_PIN_2 16
#define DIR_PIN_2 17
#define ENABLE_PIN_2 5

// 定义步进电机对象
AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN_1, DIR_PIN_1); // 修正构造函数参数
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN_2, DIR_PIN_2); // 修正构造函数参数

void controlStepper(AccelStepper &stepper, float speed, float acceleration, int steps)
{
    pinMode(ENABLE_PIN_1, OUTPUT);
    pinMode(ENABLE_PIN_2, OUTPUT);
    digitalWrite(ENABLE_PIN_1, LOW);
    digitalWrite(ENABLE_PIN_2, LOW);
    stepper.setMaxSpeed(speed);
    stepper.setAcceleration(acceleration);
    stepper.moveTo(steps); // 设置目标位置

    // 运行电机直到到达目标位置或发生错误
    while (stepper.distanceToGo() != 0)
    {
        stepper.run();
    }
}
void tigao()
{
    controlStepper(stepper1, 950, 1000, 1700);
}

void xiajiang()
{
    controlStepper(stepper1, 950, 1000, 4850);
}
void xiajiang1()
{
    controlStepper(stepper1, 950, 1000, 1900);
}
void yunxin1a()
{
    controlStepper(stepper1, 950, 1000, 2000);
}

void yunxin1b()
{

    controlStepper(stepper1, 950, 1000, 0);
}

void yunxin1()
{
    controlStepper(stepper1, 950, 1000, 3700);
}

void tigao1()
{
    controlStepper(stepper1, 950, 1000, 6000);
}
void huishou()
{
    controlStepper(stepper2, 2000, 2000, -3000);
}

void yunxin2()
{
    controlStepper(stepper1, 950, 1000, 2900);
}

void yunxin2d()
{
    controlStepper(stepper1, 950, 1000, 9000);
}

void yunxin2c()
{
    controlStepper(stepper2, 2000, 2000, -3000);
}
void yunxin2b() // cunfang
{
    controlStepper(stepper2, 2000, 1200, 0);
}

void yunxin2a()
{
    controlStepper(stepper2, 2000, 2000, -2700);
}

// void yunxin2()
//{
//   // 设置目标位置并启动电机
//   stepper2.moveTo(stepsToMove2);
//
//   // 运行电机
//   while (stepper2.distanceToGo() != 0)
//   {
//     stepper2.run();
//   }
// }

void yunxin3()///////////////////////////////////////////////////////////////
{
    controlStepper(stepper1, 950, 1000, 1700);
}

void yunxin4()
{
    controlStepper(stepper2, 950, 1000, 1700);
}
