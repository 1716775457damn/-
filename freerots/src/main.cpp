#include <Arduino.h>
#include <AccelStepper.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include<task.h>

TaskHandle_t task1Handle, task2Handle;

void setup()
{
  Serial.begin(115200);
  xTaskCreate(task_00, "Task_00", 2000, NULL, 1, &task1Handle);
}

void loop()
{

}
