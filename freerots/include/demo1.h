// #include <Arduino.h>
// #include <task.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>
// #include <AccelStepper.h>

// TaskHandle_t task1Handle, task2Handle;
// void task1(void *pvParameters)
// {
//     task_first();
// }

// void task2(void *pvParameters)
// {
//     task_second();
// }

// void setup()
// {
//     Serial.begin(9600);
//     pinMode(ENABLE_PIN_1, OUTPUT);
//     pinMode(ENABLE_PIN_2, OUTPUT);

//     // 使能步进电机
//     digitalWrite(ENABLE_PIN_1, HIGH);
//     digitalWrite(ENABLE_PIN_2, HIGH);
//     xTaskCreate(task1, "Task1", 10000, NULL, 1, &task1Handle);
//     xTaskCreate(task2, "Task2", 10000, NULL, 1, &task2Handle);
// }

// void loop()
// {
// }

// void task_0(void *pvParameters)
// {
//   int a = 0;
//   // tracing();
//   chaosheng = measureDistanceAndSetState(); // 测距并设置状态
//   // Serial.println(chaosheng);
//   switch (chaosheng)
//   {
//   case 0:
//     Serial.print("0,10,10");
//     delay(30);
//     a += 1;
//     if (a == 1)
//     {
//       Serial.print("0,10,10");
//       servo1(63);
//       delay(30);
//       // a += 1;
//     }
//   }
// }
// void task_first(void *pvParameters)
// {
//   int a = 0;
//   chaosheng = measureDistanceAndSetState();
//   Serial.print(chaosheng);
//   switch (chaosheng)
//   {
//   case 0:
//     Serial.print("0,10,10");
//     delay(30);
//     a += 1;
//     if (a == 1)
//     {
//       servo1(63);
//       delay(30);
//       controlStepper(stepper2, 1800, 2000, 1000);
//       // a += 1;
//     }
//     if (a == 2)
//     {
//       delay(1200);
//       controlStepper(stepper1, 1000, 1000, 1000);
//       servo1(105);
//       delay(500);
//       Serial.print("5,8000,8"); // 后退
//       delay(2300);
//       Serial.print("8,9200,15"); // 右
//       delay(4500);
//       controlStepper(stepper2, 1000, 1000, 1000);
//       // routecontrol = 1;
//     }
//     break;
//   case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
//     tracing();
//     delay(30);
//     break;
//   }
// }

// void task_second(void *pvParameters)
// {
//   int k3 = 0;
//   chaosheng = measureDistanceAndSetState();
//   switch (chaosheng)
//   {
//   case 0:                    // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
//     Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
//     delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
//     k3++;
//     if (k3 == 1)
//     {
//       place();
//     }
//     // if (k3 == 2)
//     // {
//     //     servo1(63);
//     //     delay(500);
//     // stepMotorContro4(-7, 1);
//     //     delay(500);
//     //     Serial.print("8,6300,30"); // 右
//     //     delay(5000);
//     //     stepMotorContro4(-23, 1);
//     //     // routecontrol = 3;
//     // }
//     // break;

//     // case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
//     //     tracing3();
//     //     delay(30);
//     //     break;
//   }
// }