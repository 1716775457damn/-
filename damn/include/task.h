void tracing1()
{
    // 工业流程控制框架，可根据自身需求增加case 数量
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,14,18"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,18,18"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,18,14"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3: // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10");
        delay(30);
        Serial.print("5,12000,20"); // 后退
        delay(6000);
        Serial.print("8,4600,20"); // 右
        delay(4000);
        routecontrol = 4;
        break;
    }
}

void tracing2()
{
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,14,18"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,18,18"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,18,14"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3: // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10");
        delay(30);
        Serial.print("8,4600,20"); // 右
        delay(2000);
        routecontrol = 3;
        break;
    }
}
void tracing3()
{
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,20,25"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,25,25"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,25,20"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3: // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10");
        delay(30);
        Serial.print("7,4600,20"); // 左
        delay(2000);
        routecontrol = 2;
        break;
    }
}

void tracingback()
{
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("1,80,70"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("1,80,80"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("1,70,80"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3:                      // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

        break;
    }
}
void tracingslow()
{
    // 工业流程控制框架，可根据自身需求增加case 数量
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,65,75"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,75,75"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,75,65"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3:                      // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

        break;
    }
}

void tracingslow1()
{
    // 工业流程控制框架，可根据自身需求增加case 数量
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,22,28"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,28,28"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,28,22"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3:                      // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

        break;
    }
}
void tracing2slow()
{
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,30,40"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,40,40"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,40,30"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3: // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10");
        delay(30);
        Serial.print("8,4600,20"); // 右
        delay(2000);
        routecontrol = 3;
        break;
    }
}

void tracing2m()
{
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,14,18"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,18,18"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,18,14"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3: // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10");
        delay(30);
        Serial.print("7,4600,20"); // 右
        delay(2000);
        routecontrol = 7;
        break;
    }
}

void tracing2mslow()
{
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,30,40"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,40,40"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,40,30"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3: // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10");
        delay(30);
        Serial.print("7,4600,20"); // 右
        delay(2000);
        routecontrol = 7;
        break;
    }
}
void tracingslow2()
{
    // 工业流程控制框架，可根据自身需求增加case 数量
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,50,60"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,60,60"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,60,50"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3:                      // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

        break;
    }
}

void tracingslow3()
{
    // 工业流程控制框架，可根据自身需求增加case 数量
    sheding();
    switch (tracingcontrol)
    {

    case 0:                       // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,90,100"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);                // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                        // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,100,100"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);                 // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                       // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,100,90"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);                // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3:                      // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

        break;
    }
}

void tracingslow4()
{
    // 工业流程控制框架，可根据自身需求增加case 数量
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,30,40"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,40,40"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,40,30"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3:                      // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

        break;
    }
}

void tracing3m()
{
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,20,25"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,25,25"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,25,20"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3: // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10");
        delay(30);
        Serial.print("8,4600,20"); // 左
        delay(2000);
        routecontrol = 6;
        break;
    }
}

void tracingslow5()
{
    // 工业流程控制框架，可根据自身需求增加case 数量
    sheding();
    switch (tracingcontrol)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,30,45"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 1:                      // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,45,45"); // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 2:                      // 按位置向左平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("2,45,30"); // 按位置向右平移（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        break;

    case 3:                      // 按位置向右运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向左运动（全向轮可左右平移），运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算

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
void task1()
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k1++;
        if (k1 == 1)
        {
            servo1(58);
            delay(500);
            yunxin1();
        }
        if (k1 == 2)
        {
            delay(1200);
            yunxin1a();
            servo1(105);
            delay(500);
            Serial.print("5,7000,8"); // 后退
            delay(1800);
            Serial.print("8,9200,10"); // 右
            delay(2500);
            yunxin1b();
            routecontrol = 1;
        }
        break;

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracing();
        delay(30);
        break;
    }
}

void task3()
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k3++;
        if (k3 == 1)
        {
            chucun();
        }
        if (k3 == 2)
        {
            servo1(58);
            delay(500);
            tigao();
            delay(500);
            Serial.print("8,1800,30"); // 右
            delay(3000);
            tigao1();
            routecontrol = 4;
        }
        break;

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracing2slow();
        delay(30);
        break;
    }
}

void task3b()
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k4++;
        if (k4 == 1)
        {
            chucun();
        }
        if (k4 == 2)
        {
            servo1(58);
            delay(500);
            tigao();
            delay(500);
            Serial.print("8,1800,30"); // 右
            delay(3000);
            tigao1();
            routecontrol = 4;
        }
        break;

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracing2slow();
        delay(30);
        break;
    }
}

void task2()
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k3++;
        if (k3 == 1)
        {
            chucun();
        }
        if (k3 == 2)
        {
            servo1(58);
            delay(500);
            tigao();
            delay(500);
            Serial.print("8,6300,30"); // 右
            delay(5000);
            tigao1();
            routecontrol = 3;
        }
        break;

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracing3();
        delay(30);
        break;
    }
}

void task2b()
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k4++;
        if (k4 == 1)
        {
            chucun();
        }
        if (k4 == 2)
        {
            servo1(58);
            delay(500);
            tigao();
            delay(500);
            Serial.print("8,6300,30"); // 右
            delay(5000);
            tigao1();
            routecontrol = 3;
        }
        break;

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracing3();
        delay(30);
        break;
    }
}

void task6()
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k3++;
        if (k3 == 1)
        {
            chucun1();
        }
        if (k3 == 2)
        {
            servo1(57);
            delay(500);
            tigao();
            delay(500);
            Serial.print("8,6300,30"); // 右
            delay(5000);
            tigao1();
            routecontrol = 4;
        }
        break;

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracing2slow();
        delay(30);
        break;
    }
}

void task6b()
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k4++;
        if (k4 == 1)
        {
            chucun1();
        }
        if (k4 == 2)
        {
            servo1(57);
            delay(500);
            tigao();
            delay(500);
            Serial.print("8,6300,30"); // 右
            delay(5000);
            tigao1();
            routecontrol = 4;
        }
        break;

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracing2slow();
        delay(30);
        break;
    }
}

void task4()
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k2++;
        if (k2 == 1)
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
        if (k2 == 2)
        {
            delay(1000);
            xiajiang();
            servo1(105);
            delay(500);
            Serial.print("5,4000,10"); // 后退
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

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracingslow1();
        delay(30);
        break;
    }
}

void task4b()
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k5++;
        if (k5 == 1)
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
        if (k5 == 2)
        {
            delay(1000);
            xiajiang();
            servo1(105);
            delay(500);
            Serial.print("5,4000,10"); // 后退
            delay(2000);
            yunxin1b();
            delay(5000);
            routecontrol = 5;
        }
        break;

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracingslow1();
        delay(30);
        break;
    }
}

void task5() // 放高的物块
{
    tingzhi();
    switch (chaosheng)
    {

    case 0:                      // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        Serial.print("0,10,10"); // 按位置向前进，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        delay(30);               // 测试时用延时 时间3秒 该时间可以使用脉冲数量来精确计算
        k3++;
        if (k3 == 1)
        {
            chucun1();
            Serial.print("8,4600,15");
            delay(2700);
            routecontrol = 4;
        }
        break;

    case 1: // 按位置向后运动，运动距离7200个脉冲，运动速度5（速度参数数值越小，速度越快）
        tracing();
        delay(30);
        break;
    }
}