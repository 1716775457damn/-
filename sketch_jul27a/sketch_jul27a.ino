#include "xinbujin.hpp"
#include "servo.hpp"


int tracingcontrol = 0;
int chaosheng = 0;
float distance ;
float averageDistance;
int routecontrol = 0;
int k1;
int k2;
int k3;
int k4;
int k5;
int panduan;
bool daoche1 = false;

#define ECHOPIN 24
#define TRIGPIN 22


void setup() {
  Serial.begin(115200); // 串口0波特率115200, 接串口屏
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(servoPin1, OUTPUT);
  
  // 初始化步进电机
  pinMode(ENABLE_PIN1, OUTPUT);
  digitalWrite(ENABLE_PIN1, LOW); // 使能电机
  pinMode(ENABLE_PIN2, OUTPUT);
  digitalWrite(ENABLE_PIN2, LOW); // 使能电机
  
  float maxSpeed1 = 950.0;
  stepper1.setMaxSpeed(maxSpeed1);
  stepper1.setAcceleration(acceleration1);
  
  float maxSpeed2 = 1400.0;
  stepper2.setMaxSpeed(maxSpeed2);
  stepper2.setAcceleration(acceleration2);
  
  float maxSpeed3 = 1100.0;
  stepper3.setMaxSpeed(maxSpeed3);
  stepper3.setAcceleration(acceleration3);
  
  float maxSpeed4 = 1700.0;
  stepper4.setMaxSpeed(maxSpeed4);
  stepper4.setAcceleration(acceleration4);
  
  // 舵机初始化位置
  servo1(105); // 假设servo1是控制舵机的函数
}

int a;
int b;
int c;
int d;
int e;
uint16_t thresholdR1 = 170;
uint16_t thresholdR2 = 170;
uint16_t thresholdM = 170;
uint16_t thresholdL1 = 170;
uint16_t thresholdL2 = 170;






void ultrasonic()
{
  float totalDistance = 0; // 用于存储三次读取的总和
  int numReadings = 3;     // 定义读取次数

  for (int i = 0; i < numReadings; i++) {
    // 触发超声波传感器发送信号
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);

    // 使用pulseIn函数读取脉冲宽度
    float distance = pulseIn(ECHOPIN, HIGH);

    // 计算距离，58是根据声速和脉冲时间计算出的距离转换系数
    distance = distance / 58;
    totalDistance += distance; // 累加每次的距离读数

    // 等待一段时间，确保传感器稳定
    delay(10);
  }
  averageDistance = totalDistance / numReadings;
  // 打印平均距离值
//    Serial.print("Average Distance: ");
//    Serial.println(averageDistance);
}

void huidu()
{
  a = analogRead(A12);
  b = analogRead(A11);
  c = analogRead(A10);
  d = analogRead(A9);
  e = analogRead(A8);
  a = a > thresholdR2 ? 1 : 0;
  b = b > thresholdR1 ? 1 : 0;
  c = c > thresholdM ? 1 : 0;
  d = d > thresholdL1 ? 1 : 0;
  e = e > thresholdL2 ? 1 : 0;
}


void sheding()
{
  huidu();
  if ((d == 0 || e == 0) && c == 0 && b == 1 && a == 1) {
    tracingcontrol = 0;
  } else if ((d == 0 || e == 0) && c == 1 && b == 1 && a == 1) {
    tracingcontrol = 0;
  } else if (d == 1 && e == 1 && c == 0 && b == 1 && a == 1) {
    tracingcontrol = 1;
  } else if (d == 1 && e == 1 && c == 1 && b == 1 && a == 1) {
    tracingcontrol = 1;
  } else if ((a == 0 || b == 0) && c == 0 && d == 1 && e == 1) {
    tracingcontrol = 2;
  } else if ((a == 0 || b == 0) && c == 1 && d == 1 && e == 1) {
    tracingcontrol = 2;
  } else if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0) {
    tracingcontrol = 3;
  } else {
    tracingcontrol = 1; // 当以上条件都不满足时执行
  }
}

void tracing1()
{
  //工业流程控制框架，可根据自身需求增加case 数量
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,14,18"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,18,18"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,18,14"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10");
      delay(30);
      Serial.print("5,12000,20");//后退
      delay(6000);
      Serial.print("8,4600,20");//右
      delay(4000);
      routecontrol = 4;
      break;

  }   
}

void tracing2()
{
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,14,18"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,18,18"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,18,14"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10");
      delay(30);
      Serial.print("8,4600,20");//右
      delay(2000);
      routecontrol = 3;
      break;

  }    
}

void tracing2slow()
{
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,30,40"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,40,40"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,40,30"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10");
      delay(30);
      Serial.print("8,4600,20");//右
      delay(2000);
      routecontrol = 3;
      break;

  }    
}

void tracing2m()
{
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,14,18"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,18,18"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,18,14"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10");
      delay(30);
      Serial.print("7,4600,20");//右
      delay(2000);
      routecontrol = 7;
      break;

  }     
}

void tracing2mslow()
{
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,30,40"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,40,40"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,40,30"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10");
      delay(30);
      Serial.print("7,4600,20");//右
      delay(2000);
      routecontrol = 7;
      break;

  }    
}

void tracing3()
{
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,20,25"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,25,25"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,25,20"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10");
      delay(30);
      Serial.print("7,4600,20");//左
      delay(2000);
      routecontrol = 2;
      break;

  }  
}

void tracing3m()
{
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,20,25"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,25,25"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,25,20"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10");
      delay(30);
      Serial.print("8,4600,20");//左
      delay(2000);
      routecontrol = 6;
      break;

  }  
}

void route()
{
 //工业流程控制框架，可根据自身需求增加case 数量
  switch (routecontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      task1();
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      task2();
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      task6();
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
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


void tracing()
{
  //工业流程控制框架，可根据自身需求增加case 数量
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,14,18"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,18,18"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,18,14"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

      break;

  }
}

void tracingback()
{
  sheding();
    switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("1,80,70"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("1,80,80"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("1,70,80"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

      break;

  }  
}
void tracingslow()
{
  //工业流程控制框架，可根据自身需求增加case 数量
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,65,75"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,75,75"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,75,65"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

      break;

  }
}

void tracingslow1()
{
    //工业流程控制框架，可根据自身需求增加case 数量
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,22,28"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,28,28"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,28,22"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

      break;

  }  
}

void tracingslow5()
{
    //工业流程控制框架，可根据自身需求增加case 数量
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,30,45"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,45,45"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,45,30"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

      break;

  }  
}


void tracingslow2()
{
    //工业流程控制框架，可根据自身需求增加case 数量
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,50,60"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,60,60"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,60,50"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

      break;

  }  
}

void tracingslow3()
{
    //工业流程控制框架，可根据自身需求增加case 数量
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,90,100"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,100,100"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,100,90"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

      break;

  }  
}

void tracingslow4()
{
  //工业流程控制框架，可根据自身需求增加case 数量
  sheding();
  switch (tracingcontrol) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,30,40"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,40,40"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,40,30"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 3:    //按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

      break;

  }    
}

void tingzhi()
{
  ultrasonic();
  if (0 <= averageDistance <= 4.5)
  {
    chaosheng = 0;
  }
  if (averageDistance > 4.5)
  {
    chaosheng = 1; 
  }  
}


void task1()
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k1++;
      if(k1 == 1)
      {
        servo1(58);
        delay(500);
        yunxin1(); 
      }
      if(k1 == 2)
      {
        delay(1200);
        yunxin1a();
        servo1(105);
        delay(500);
        Serial.print("5,7000,8");//后退
        delay(1800);
        Serial.print("8,9200,10");//右
        delay(2500);
        yunxin1b();
        routecontrol = 1;  
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing();
      delay(30);
      break;
  }
}

void yunxin1()
{
  // 设置目标位置并启动电机
  stepper1.moveTo(3700);

  // 运行电机
  Serial.print("2,45,45");
  while (stepper1.distanceToGo() != 0)
  {
    stepper1.run();
  }
}

void yunxin1a()
{
  // 设置目标位置并启动电机
  stepper1.moveTo(2000);

  // 运行电机
  while (stepper1.distanceToGo() != 0)
  {
     stepper1.run();
  }
}

void yunxin1b()
{
  // 设置目标位置并启动电机
  stepper1.moveTo(0);

  // 运行电机
  while (stepper1.distanceToGo() != 0)
  {
    stepper1.run();
  }
}

void task3()
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k3++;
      if(k3 == 1)
      {
        chucun();  
      }
      if(k3 == 2)
      {
        servo1(58);
        delay(500);
        tigao();
        delay(500);
        Serial.print("8,1800,30");//右
        delay(3000);
        tigao1();
        routecontrol = 4;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing2slow();
      delay(30);
      break;
  }
}

void task3b()
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k4++;
      if(k4 == 1)
      {
        chucun();  
      }
      if(k4 == 2)
      {
        servo1(58);
        delay(500);
        tigao();
        delay(500);
        Serial.print("8,1800,30");//右
        delay(3000);
        tigao1();
        routecontrol = 4;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing2slow();
      delay(30);
      break;
  }
}



void task2()
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k3++;
      if(k3 == 1)
      {
        chucun();  
      }
      if(k3 == 2)
      {
        servo1(58);
        delay(500);
        tigao();
        delay(500);
        Serial.print("8,6300,30");//右
        delay(5000);
        tigao1();
        routecontrol = 3;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing3();
      delay(30);
      break;
  }
}

void task2b
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k4++;
      if(k4 == 1)
      {
        chucun();  
      }
      if(k4 == 2)
      {
        servo1(58);
        delay(500);
        tigao();
        delay(500);
        Serial.print("8,6300,30");//右
        delay(5000);
        tigao1();
        routecontrol = 3;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing3();
      delay(30);
      break;
  }
}

void task6()
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k3++;
      if(k3 == 1)
      {
        chucun1();  
      }
      if(k3 == 2)
      {
        servo1(57);
        delay(500);
        tigao();
        delay(500);
        Serial.print("8,6300,30");//右
        delay(5000);
        tigao1();
        routecontrol = 4;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing2slow();
      delay(30);
      break;
  }
}

void task6b()
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k4++;
      if(k4 == 1)
      {
        chucun1();  
      }
      if(k4 == 2)
      {
        servo1(57);
        delay(500);
        tigao();
        delay(500);
        Serial.print("8,6300,30");//右
        delay(5000);
        tigao1();
        routecontrol = 4;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing2slow();
      delay(30);
      break;
  }   
}



void chucun()
{
  servo1(58);
  delay(500);
  yunxin2();
  yunxin2a();
  yunxin1a();
  servo1(105);
  delay(600);
  yunxin2b();
  yunxin1b();
  Serial.print("7,4700,15");
  delay(1500);
  routecontrol = 2;  
}


void chucun1()
{
  servo1(58);
  delay(500);
  yunxin2();
  yunxin2a();
  yunxin1a();
  servo1(105);
  delay(600);
  yunxin2b();
  yunxin1b();
}


void task4()
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k2++;
      if(k2 == 1)
      {
        delay(1000);
        xiajiang();
        servo1(105);
        delay(500);
        Serial.print("5,5000,10");
        delay(2000);
        Serial.print("9,4700,10");
        delay(2000);
        Serial.print("6,5000,10");
        delay(1500);
        Serial.print("8,8300,15");
        delay(2000);
        yunxin2a();
        xiajiang1();
        servo1(60);
        delay(400);
        tigao1();
        yunxin2b(); 
      }
      if(k2 == 2)
      {
        delay(1000);
        xiajiang();
        servo1(105);
        delay(500);
        Serial.print("5,4000,10");//后退
        delay(2000);
        Serial.print("9,4700,15");
        delay(2500);
        Serial.print("6,4000,20");
        delay(2000);
        Serial.print("8,5700,20");
        delay(3000);
        yunxin1b();
        delay(5000);
        routecontrol = 5;  
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracingslow1();
      delay(30);
      break;
  }
}

void task4b()
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k5++;
      if(k5 == 1)
      {
        delay(1000);
        xiajiang();
        servo1(105);
        delay(500);
        Serial.print("5,5000,10");
        delay(2000);
        Serial.print("9,4700,10");
        delay(2000);
        Serial.print("6,5000,10");
        delay(1500);
        Serial.print("8,8300,15");
        delay(2000);
        yunxin2a();
        xiajiang1();
        servo1(60);
        delay(400);
        tigao1();
        yunxin2b(); 
      }
      if(k5 == 2)
      {
        delay(1000);
        xiajiang();
        servo1(105);
        delay(500);
        Serial.print("5,4000,10");//后退
        delay(2000);
        yunxin1b();
        delay(5000);
        routecontrol = 5;  
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracingslow1();
      delay(30);
      break;
  }  
}
void xiajiang()
{
  // 设置目标位置并启动电机
  stepper1.moveTo(4850);

  // 运行电机
  while (stepper1.distanceToGo() != 0)
  {
    stepper1.run();
  } 
}

void xiajiang1()
{
  // 设置目标位置并启动电机
  stepper1.moveTo(1900);

  // 运行电机
  while (stepper1.distanceToGo() != 0)
  {
    stepper1.run();
  } 
}




void task5()//放高的物块
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k3++;
      if(k3 == 1)
      {
        chucun1();
        Serial.print("8,4600,15");
        delay(2700);
        routecontrol = 4;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing();
      delay(30);
      break;
  }    
}


void loop() {
  route();
}
