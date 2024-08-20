class STEPPER
{
  public:
    byte DirPin, PulPin, EnablePin;
    long CurrentStepTime = 0, TargetStepTime = 1000, LastStepSt = 0;
    long CurrentStep = 0, TargetStep = 0, StartStep = 0;
    long Acceleration = 600;//加速度(步/秒~2）
    long SpeedUpStep, SpeedDownStep;//加速,减速时的步数
    bool IsDebug = false;

    STEPPER(byte dir, byte pul, byte en)
    {
      DirPin = dir;
      PulPin = pul;
      EnablePin = en;
      calCulateSpeedChangeMinimunDis();

      pinMode(DirPin, OUTPUT);
      pinMode(PulPin, OUTPUT);
      pinMode(EnablePin, OUTPUT);

      digitalWrite(DirPin, 0);
      digitalWrite(PulPin, 0);
      digitalWrite(EnablePin, 0);
    }

    void SetAcceleration(long acceleration)
    {
      Acceleration = acceleration;
      calCulateSpeedChangeMinimunDis();
    }

    bool IsRunToTarget()
    {
      return TargetStep == CurrentStep;
    }

    bool CanRun()
    {
      return micros() - LastStepSt >= CurrentStepTime;
    }

    bool RunTo(long target)
    {
      if (TargetStep != target)
      {
        TargetStep = target;
        CurrentStepTime = 0;
        StartStep = CurrentStep;
        calCulateSpeedChangeMinimunDis();
        if (IsDebug)
        { /*
            Serial.print ("V: ");
            Serial.println (1000000.0 / TargetStepTime);

            Serial.print ("_speedChangeMinimumDis: ");
            Serial.println (_speedChangeMinimumDis);
            Serial.print ("StartStep: ");
            Serial.println (StartStep);*/
        }
        long souldMoveSteps = TargetStep - CurrentStep;

        if ( _speedChangeMinimumDis * 2 > abs(souldMoveSteps))
        {
          SpeedUpStep =  souldMoveSteps / 2 + CurrentStep;
          SpeedDownStep = SpeedUpStep;
        }

        else
        {
          if (CurrentStep < TargetStep)//正向
          {
            SpeedUpStep =  _speedChangeMinimumDis + CurrentStep;
            SpeedDownStep = TargetStep - _speedChangeMinimumDis;
          }
          else//反向
          {
            SpeedUpStep =  CurrentStep - _speedChangeMinimumDis;
            SpeedDownStep = TargetStep + _speedChangeMinimumDis;
          }
        }
        if (IsDebug)
        {
          /*
                    Serial.print ("SpeedUpStep: ");
                    Serial.println (SpeedUpStep);
                    Serial.print ("SpeedDownStep: ");
                    Serial.println (SpeedDownStep);
          */
        }
      }

      if (IsRunToTarget() == false)
      {
        if (CanRun())
        {
          runStep(CurrentStep < target);
        }
      }

      return IsRunToTarget();
    }

    bool RunTo(long target, unsigned long stepTime)
    {
      TargetStepTime = stepTime;
      return RunTo(target);
    }

    void RunCycle(bool dir,  unsigned long stepTime)
    {
      TargetStepTime = stepTime;
      CurrentStepTime = 0;
      if (CanRun())
      {
        runStep( dir);
      }
    }

  private:
    long _speedChangeMinimumDis = 0;

    void calCulateSpeedChangeMinimunDis()
    {
      double v = 1000000.0 / TargetStepTime;//步/秒
      _speedChangeMinimumDis =  pow(v, 2) / 2 / Acceleration;
    }

    void runStep(bool dir)
    {
      LastStepSt = micros();
      digitalWrite(DirPin, dir);
      digitalWrite(PulPin, 1);
      delayMicroseconds(10);
      digitalWrite(PulPin, 0);
      CurrentStep += (dir ? 1 : -1);

      if (Acceleration == 0)
      {
        CurrentStepTime = TargetStepTime ;
        return;
      }
      double v = 0.0;// =  CurrentStepTime > 0 ? 1000000.0 / CurrentStepTime  : 0;//步/秒
      if (dir)
      {
        if (CurrentStep < SpeedUpStep || CurrentStep > SpeedDownStep)
        {
          if (CurrentStep < SpeedUpStep)
          {
            v = sqrt(double( Acceleration * 2.0 * (CurrentStep - StartStep)));//步/秒
          }
          else
          {
            v = 1000000.0 / TargetStepTime;//步/秒
            v = sqrt(double((-Acceleration) * 2.0 * (CurrentStep - SpeedDownStep )  +  pow(v, 2)));//步/秒
          }
          CurrentStepTime = 1000000.0 / v;
          CurrentStepTime = CurrentStepTime <= TargetStepTime ? TargetStepTime : CurrentStepTime;
        }

        else
        {
          CurrentStepTime = TargetStepTime ;
        }
      }

      else
      {
        if (CurrentStep > SpeedUpStep || CurrentStep < SpeedDownStep)
        {
          if (CurrentStep > SpeedUpStep)
          {
            v = sqrt(Acceleration * 2 * (StartStep - CurrentStep));//步/秒
          }
          else
          {
            v = 1000000.0 / TargetStepTime;//步/秒
            v = sqrt((-Acceleration) * 2 * abs(CurrentStep - SpeedDownStep)  +  pow(v, 2));//步/秒
          }
          CurrentStepTime = 1000000.0 / v;
          CurrentStepTime = CurrentStepTime <= TargetStepTime ? TargetStepTime : CurrentStepTime;
        }

        else
        {
          CurrentStepTime = TargetStepTime ;
        }
      }
      if (IsDebug)
      {
        // Serial.print (CurrentStep);
        //Serial.print (",");
        Serial.print ( v == 0 ? 1000000.0 / CurrentStepTime : v);
        Serial.print (",");
        Serial.println (CurrentStepTime);
      }
    }
};

STEPPER  MyStepperA(2, 3, 4);
STEPPER  MyStepperB(5, 6, 7);

long targetA = 5000, targetB = -4000;

void setup()
{  
  Serial.begin(115200);
  MyStepperA.SetAcceleration(1500);
  MyStepperB.SetAcceleration(800);
  //MyStepperA.IsDebug = true;
}

unsigned long st = 0;

void loop()
{
  if (MyStepperA.RunTo(targetA, 600))
  {
    targetA = -targetA;
  }
  if (MyStepperB.RunTo(targetB, 450))
  {
    targetB = -targetB;
  }
/*
  if (millis() - st >= 10)
  {
    st = millis();
    Serial.print (1000000.0 / MyStepperB.CurrentStepTime);
    Serial.print (",");
    Serial.print (MyStepperB.CurrentStep);
    Serial.print (",");
    Serial.print (1000000.0 / MyStepperA.CurrentStepTime);
    Serial.print (",");
    Serial.println (MyStepperA.CurrentStep);
  }
*/
}













