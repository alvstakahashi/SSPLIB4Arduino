#include <toppers.h>
char dummyvar; // to get Arduinoi IDE to include core headers properly

/*
  FlexiTimer2:
  Arduino library to use timer 2 with a configurable resolution.
  Based on MsTimer2 by Javier Valencia. It is called FlexiTimer2 because it
  is based on MsTimer2, but offers more flexibility,
  since it has a configurable timer resolution.
  MsTimer2 library: http://www.arduino.cc/playground/Main/MsTimer2

For more details on FlexiTimer2 see: 
 http://www.arduino.cc/playground/Main/FlexiTimer2
 https://github.com/wimleers/flexitimer2

*/

#include <FlexiTimer2.h>

// Switch on LED on and off each half second

#if defined(ARDUINO) && ARDUINO >= 100
const int led_pin = LED_BUILTIN;	// 1.0 built in LED pin var
#else
#if defined(CORE_LED0_PIN)
const int led_pin = CORE_LED0_PIN;	// 3rd party LED pin define
#else
const int led_pin = 13;			// default to pin 13
#endif
#endif

extern "C" void signal_time(void);
extern "C" void handler(INTHDR userhandler);

int Duration = 0; //受信した間隔
double Distance = 0; //距離
int Duration2 = 0; //受信した間隔
double Distance2 = 0; //距離

void flash()
{
    handler(signal_time);
}

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode( 2, OUTPUT );
  pinMode( 3, INPUT );
  pinMode( 4, OUTPUT );
  pinMode( 5, INPUT );
  
  Serial.begin(115200);
  FlexiTimer2::set(1, 1.0/1000, flash); // call every 500 1ms "ticks"
  // FlexiTimer2::set(500, flash); // MsTimer2 style is also supported
  FlexiTimer2::start();

  tinib_task_set(0,task1);
  tinib_task_set(1,task2);
  tinib_task_set(2,sonicsenser);
  tinib_task_set(3,sonicsenser2);
  cycinib_cychdr_set(0,cyc_handr,1000);
  cycinib_cychdr_set(1,cyc_handr2,500);
  cycinib_cychdr_set(2,cyc_handr3,500);
  
  sta_ker();

}
void t_lock_cpu()
{
  noInterrupts();
}
void t_unlock_cpu()
{
  interrupts();
}
void cyc_handr(intptr_t arg)
{
  iact_tsk(TASK2_ID);
}
void cyc_handr2(intptr_t arg)
{
  iact_tsk(3);    //sonicsenser 起動
}
void cyc_handr3(intptr_t arg)
{
  iact_tsk(4);    //sonicsenser2 起動
}
void task1(intptr_t arg)
{
  Serial.println("task1 here\n");
  sta_cyc(1);
  sta_cyc(2);
  sta_cyc(3);
}

void task2(intptr_t arg)
{
  static int output;
  Serial.println("task2 here \n");
  digitalWrite(13,output);
  output = !output;
  Serial.print("Distance:");
  Serial.print(Distance);
  Serial.println(" cm");
  Serial.print("Distance2:");
  Serial.print(Distance2);
  Serial.println(" cm");
}

void sonicsenser(intptr_t arg)
{
  digitalWrite( 2, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( 2, LOW );
  Duration = pulseIn( 3, HIGH ); //センサからの入力
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance = Duration*340.0*100/1000000; // 音速を340m/sに設定
  }
}
void sonicsenser2(intptr_t arg)
{
  digitalWrite( 4, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( 4, LOW );
  Duration2 = pulseIn( 5, HIGH ); //センサからの入力
  if (Duration2 > 0) {
    Duration2 = Duration2/2; //往復距離を半分にする
    Distance2 = Duration2*340.0*100/1000000; // 音速を340m/sに設定
  }
}

void loop()
{
}
