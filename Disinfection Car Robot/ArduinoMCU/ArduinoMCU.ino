#include<Servo.h>

#define rmp 36
#define rmm 37
#define rpf 4 //Right_motor_PWm_forward
#define rpr 5 //Right_motor_PWm_Reverse

#define lmp 34
#define lmm 35
#define lpf 8 //Left_motor_PWm_forward
#define lpr 9 //Left_motor_PWm_reverse

int speeds=0;
char data,dataA;

#include "motorFunc.h"

#define servo1 6
#define servo2 7
#define servo3 10
#define servo4 11

#include "ArmClass.h"

int i1=90,i2=90,i3=90,i4=95,pos;
Servo s1,s2,s3,s4;

void info(int i){
    Serial.print(" ");
    Serial.print(i);
}
void endF(char DATA)
  {
     pos=(DATA-48)*11;
    if(pos==0)
      pos=10;
    Serial.print(" ");
    Serial.print(pos);
    s4.write(pos);
  }
Arm a1(s1),a2(s2),a3(s3),a4(s4);

#include "servoFunc.h"

int pwm = 0;

void setup(){
  Serial.begin(9600);
  Serial3.begin(9600);

  //Motor pinMode//Right_Motor
  pinMode(rmp,OUTPUT);
  pinMode(rmm,OUTPUT);
  pinMode(rpf,OUTPUT);
  pinMode(rpr,OUTPUT);
  //Left_Motor
  pinMode(lmp,OUTPUT);
  pinMode(lmm,OUTPUT);
  pinMode(lpf,OUTPUT);
  pinMode(lpr,OUTPUT);

  s1.attach(servo1);
  s2.attach(servo2);
  s3.attach(servo3);
  s4.attach(servo4);

  resetAll();
}

void loop(){
  if(Serial3.available()>0){
    String x;
    x =Serial3.readStringUntil('\0');
    //Serial.print("String: ");
    Serial.println(x);
    Serial3.write('>');
    speeds=parsePWM(x);
    driveCar(x[0]);
    Serial.print("Speed: ");
    Serial.println(speeds);
  }
}
