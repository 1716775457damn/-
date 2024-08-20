
int ENA1 = 10;  // 使能信号的io口
int PUL1 = 11;  // 脉冲信号的io口
int DIR1 = 13;// 方向信号的io口
int ENA2 = 25;  // 使能信号的io口
int PUL2 = 28;  // 脉冲信号的io口
int DIR2 = 30;
int x1;
int x2;


// 步进电机参数设置
const int stepsPerRevolution1 = 200; // 每转一圈的步数（根据具体电机参数调整）
const int speed1 = 5; // 脉冲间隔（单位：毫秒）

void maichong1(int times, int speed) // times是脉冲的数量，speed是脉冲间隔，对应着电机的速度
{
  for(x1 = 0; x1 < times; x1++)
  {
    digitalWrite(PUL1, HIGH);
    delayMicroseconds(200); // 这个函数单位为微秒
    digitalWrite(PUL1, LOW);
    delayMicroseconds(200); // 驱动器说明书规定了脉冲信号的持续时间，在规定的时间内选择尽量小的数值
    delay(speed); // 前后两个脉冲之间的间隔
  }
}

//void stepMotorContro1(int circles, int speed) {
//  // 确保传入的圈数是整数
//  int circles1;
//  circles1 = abs(circles);
//
//  // 根据方向设置方向引脚的状态
//  // 假设正转使用LOW，反转使用HIGH
//  // 注意：具体的电平和您的硬件设计有关，这里需要根据实际情况调整
//  digitalWrite(DIR1, (circles > 0) ? LOW : HIGH);
//
//  // 循环转动指定的圈数
//  for (int i = 0; i < circles1; i++) {
//    // 调用已有的脉冲函数来驱动电机转动一圈
//    maichong1(stepsPerRevolution1, speed);
//
//    // 延时一段时间，防止电机过热或其他问题
//    delay(10);
//  }
//}

const int stepsPerRevolution2 = 200; // 每转一圈的步数（根据具体电机参数调整）
const int speed2 = 5; // 脉冲间隔（单位：毫秒）

void maichong2(int times, int speed) // times是脉冲的数量，speed是脉冲间隔，对应着电机的速度
{
  for(x2 = 0; x2 < times; x2++)
  {
    digitalWrite(PUL2, HIGH);
    delayMicroseconds(200); // 这个函数单位为微秒
    digitalWrite(PUL2, LOW);
    delayMicroseconds(200); // 驱动器说明书规定了脉冲信号的持续时间，在规定的时间内选择尽量小的数值
    delay(speed); // 前后两个脉冲之间的间隔
  }
}


void stepMotorContro2(int circles, int speed) {
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
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}


void stepMotorContro3(int circles, int speed) {
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
    // 延时一段时间，防止电机过热或其他问题
    delay(10);
  }
}
