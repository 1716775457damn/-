#include "bujin.hpp"
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
  Serial.begin(115200); //串口0波特率115200,接串口屏
  //Serial1.begin(115200); //串口1波特率115200,接串口屏
  //  Serial2.begin(115200); //串口2波特率115200,接串口屏
  //Serial3.begin(115200); //串口3波特率115200,接串口屏
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(servoPin1, OUTPUT);
  pinMode(PUL1, OUTPUT); // 设置io口输出
  pinMode(DIR1, OUTPUT); // 设置io口输出
  pinMode(ENA1, OUTPUT); // 设置io口输出
  digitalWrite(ENA1, LOW); // LOW表示使能开启，HIGH表示使能关闭
  pinMode(PUL2, OUTPUT); // 设置io口输出
  pinMode(DIR2, OUTPUT); // 设置io口输出
  pinMode(ENA2, OUTPUT); // 设置io口输出
  digitalWrite(ENA2, LOW); // LOW表示使能开启，HIGH表示使能关闭
  servo1(105);
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
      mirror2();
      break;

    case 6:
      mirror6();
      break;

    case 7:
      mirror3();
      break;

    case 8:
      mirror4();
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
      Serial.print("2,18,25"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,25,25"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,25,18"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
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
      Serial.print("2,40,50"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,50,50"); //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      break;

    case 2:    //按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("2,50,40"); //按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
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
  if (0 <= averageDistance <= 4)
  {
    chaosheng = 0;
  }
  if (averageDistance > 4)
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
        servo1(63);
        delay(500);
        stepMotorContro4(-18,1);  
      }
      if(k1 == 2)
      {
        delay(1200);
        stepMotorContro3(6,1);
        servo1(105);
        delay(500);
        Serial.print("5,8000,8");//后退
        delay(2300);
        Serial.print("8,9200,15");//右
        delay(4500);
        stepMotorContro2(12,1);
        routecontrol = 1;  
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing();
      delay(30);
      break;
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
        servo1(63);
        delay(500);
        stepMotorContro4(-7,1);
        delay(500);
        Serial.print("8,1800,30");//右
        delay(3000);
        stepMotorContro4(-23,1);
        routecontrol = 4;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing2slow();
      delay(30);
      break;
  }
}

void mirror3()
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
        servo1(63);
        delay(500);
        stepMotorContro4(-7,1);
        delay(500);
        Serial.print("7,1800,30");//右
        delay(3000);
        stepMotorContro4(-23,1);
        routecontrol = 8;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing2mslow();
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
        servo1(63);
        delay(500);
        stepMotorContro4(-7,1);
        delay(500);
        Serial.print("8,6300,30");//右
        delay(5000);
        stepMotorContro4(-23,1);
        routecontrol = 3;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing3();
      delay(30);
      break;
  }
}

void mirror2()
{
  tingzhi();
  switch (chaosheng) {

    case 0:    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      Serial.print("0,10,10"); //按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      delay(30); //测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
      k4++;
      if(k4 == 1)
      {
        chucunm();  
      }
      if(k4 == 2)
      {
        servo1(63);
        delay(500);
        stepMotorContro4(-7,1);
        delay(500);
        Serial.print("7,6300,30");//
        delay(5000);
        stepMotorContro4(-23,1);
        routecontrol = 7;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing3m();
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
        servo1(63);
        delay(500);
        stepMotorContro4(-7,1);
        delay(500);
        Serial.print("8,6300,30");//右
        delay(5000);
        stepMotorContro4(-23,1);
        routecontrol = 4;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing2slow();
      delay(30);
      break;
  }
}

void mirror6()
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
        servo1(63);
        delay(500);
        stepMotorContro4(-7,1);
        delay(500);
        Serial.print("7,6300,30");//右
        delay(5000);
        stepMotorContro4(-23,1);
        routecontrol = 8;
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracing2mslow();
      delay(30);
      break;
  }
}

void chucun()
{
  servo1(63);
  delay(300);
  stepMotorContro2(-14,1);
  stepMotorContro7(13,1);
  stepMotorContro2(4,1);
  servo1(105);
  delay(800);
  stepMotorContro1(-13,1);
  stepMotorContro2(10,1);
  Serial.print("7,4700,15");
  delay(1800);
  routecontrol = 2;  
}

void chucunm()
{
  servo1(63);
  delay(300);
  stepMotorContro2(-14,1);
  stepMotorContro7(13,1);
  stepMotorContro2(4,1);
  servo1(105);
  delay(800);
  stepMotorContro1(-13,1);
  stepMotorContro2(10,1);
  Serial.print("8,4700,15");
  delay(1800);
  routecontrol = 6;  
}

void chucun1()
{
  servo1(63);
  delay(300);
  stepMotorContro2(-14,1);
  stepMotorContro7(13,1);
  stepMotorContro2(4,1);
  servo1(105);
  delay(800);
  stepMotorContro1(-13,1);
  stepMotorContro2(10,1);
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
        stepMotorContro2(5,1);
        servo1(105);
        delay(500);
        Serial.print("5,3000,10");
        delay(1000);
        Serial.print("9,9300,15");
        delay(4300);
        stepMotorContro5(15,1);
        stepMotorContro8(14,1);
        servo1(63);
        delay(300);
        stepMotorContro9(-20,1);
        stepMotorContro1plus(-14,1);  
      }
      if(k2 == 2)
      {
        delay(1000);
        stepMotorContro2(5,1);
        servo1(105);
        delay(500);
        Serial.print("5,12000,10");//后退
        delay(3700);
//        stepMotorContro2(25,1);
        Serial.print("8,4000,10");
        delay(1500);
        Serial.print("9,9600,10");
        delay(3500);
        Serial.print("7,16100,10");//左
        delay(5500);
        stepMotorContro10(25,1);
        routecontrol = 5;  
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracingslow1();
      delay(30);
      break;
  }
}

void mirror4()
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
        stepMotorContro2(5,1);
        servo1(105);
        delay(500);
        Serial.print("5,3000,10");
        delay(1000);
        Serial.print("9,9600,15");
        delay(4400);
        stepMotorContro5(15,1);
        stepMotorContro8(14,1);
        servo1(63);
        delay(300);
        stepMotorContro9(-20,1);
        stepMotorContro1plus(-14,1);  
      }
      if(k5 == 2)
      {
        delay(1000);
        stepMotorContro2(5,1);
        servo1(105);
        delay(500);
        Serial.print("5,3000,10");//后退
        delay(1000);
        stepMotorContro2(25,1);
        delay(2000);  
      }
      break;

    case 1:    //按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
      tracingslow1();
      delay(30);
      break;
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

void stepMotorContro4(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles2;
  circles2 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR2, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数  
  for (int i = 0; i < circles2; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong2(stepsPerRevolution2, speed);
    tracingslow();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

//快速循迹边收边走
void stepMotorContro5(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles2;
  circles2 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR2, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数  
  for (int i = 0; i < circles2; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong2(stepsPerRevolution2, speed);
    tracingslow1();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

//快速循迹边收边走
void stepMotorContro6(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles2;
  circles2 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR2, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数  
  for (int i = 0; i < circles2; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong2(stepsPerRevolution2, speed);
    tracingslow2();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

void stepMotorContro1(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles1;
  circles1 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR1, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数
  for (int i = 0; i < circles1; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong1(stepsPerRevolution1, speed);
    tracingslow3();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

void stepMotorContro7(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles1;
  circles1 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR1, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数
  for (int i = 0; i < circles1; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong1(stepsPerRevolution1, speed);
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

void stepMotorContro8(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles1;
  circles1 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR1, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数
  for (int i = 0; i < circles1; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong1(stepsPerRevolution1, speed);
    tracingslow1();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

void stepMotorContro9(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles2;
  circles2 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR2, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数
  for (int i = 0; i < circles2; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong2(stepsPerRevolution2, speed);
    tracingslow1();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

void stepMotorContro10(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles2;
  circles2 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR2, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数
  for (int i = 0; i < circles2; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong2(stepsPerRevolution2, speed);
    tracingslow5();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

void stepMotorContro1plus(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles1;
  circles1 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR1, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数
  for (int i = 0; i < circles1; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong1(stepsPerRevolution1, speed);
    tracingslow4();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

void stepMotorContro1back(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles1;
  circles1 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR1, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数
  for (int i = 0; i < circles1; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong1(stepsPerRevolution1, speed);
    tracingback();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}
void stepMotorContro2back(int circles, int speed) {
  // 确保传入的圈数是整数
  int circles2;
  circles2 = abs(circles);

  // 根据方向设置方向引脚的状态
  // 假设正转使用LOW，反转使用HIGH
  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
  digitalWrite(DIR2, (circles > 0) ? LOW : HIGH);

  // 循环转动指定的圈数
  for (int i = 0; i < circles2; i++) {
    // 调用已有的脉冲函数来驱动电机转动一圈
    maichong2(stepsPerRevolution2, speed);
    tracingback();
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}

void loop() {
//  task1();
//  task2();
//  task5();
//  stepMotorContro2(24,2);
  route();
}
