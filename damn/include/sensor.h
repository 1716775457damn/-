#define ECHOPIN 33
#define TRIGPIN 25
int tracingcontrol = 0;
int chaosheng = 0;
float distance;
float averageDistance;
int routecontrol = 0;
int k1;
int k2;
int k3;
int k4;
int k5;
int panduan;
bool daoche1 = false;

int a;
int b;
int c;
int d;
int e;
uint16_t thresholdR1 = 800;
uint16_t thresholdR2 = 800;
uint16_t thresholdM = 800;
uint16_t thresholdL1 = 800;
uint16_t thresholdL2 = 800;

void ultrasonic()
{
    float totalDistance = 0; // 用于存储三次读取的总和
    int numReadings = 3;     // 定义读取次数

    for (int i = 0; i < numReadings; i++)
    {
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
    a = analogRead(13);
    b = analogRead(12);
    c = analogRead(14);
    d = analogRead(27);
    e = analogRead(26);
    a = a > thresholdR2 ? 1 : 0;
    b = b > thresholdR1 ? 1 : 0;
    c = c > thresholdM ? 1 : 0;
    d = d > thresholdL1 ? 1 : 0;
    e = e > thresholdL2 ? 1 : 0;
}

void sheding()
{
    huidu();
    if ((d == 0 || e == 0) && c == 0 && b == 1 && a == 1)
    {
        tracingcontrol = 0;
    }
    else if ((d == 0 || e == 0) && c == 1 && b == 1 && a == 1)
    {
        tracingcontrol = 0;
    }
    else if (d == 1 && e == 1 && c == 0 && b == 1 && a == 1)
    {
        tracingcontrol = 1;
    }
    else if (d == 1 && e == 1 && c == 1 && b == 1 && a == 1)
    {
        tracingcontrol = 1;
    }
    else if ((a == 0 || b == 0) && c == 0 && d == 1 && e == 1)
    {
        tracingcontrol = 2;
    }
    else if ((a == 0 || b == 0) && c == 1 && d == 1 && e == 1)
    {
        tracingcontrol = 2;
    }
    else if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0)
    {
        tracingcontrol = 3;
    }
    else
    {
        tracingcontrol = 1; // 当以上条件都不满足时执行
    }
}