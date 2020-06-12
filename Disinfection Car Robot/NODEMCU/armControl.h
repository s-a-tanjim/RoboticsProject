#include<Servo.h>

#define servo1Pin 14 //D5
#define servo2Pin 12 //D6
#define servo3Pin 13 //D7
#define servo4Pin 15 //D8

int servoDegree[4];
int prevServoDegree[]={-1,-1,-1,-1};

void printArmData(){
  Serial.print("Arm 1:");
  Serial.println(servoDegree[0]);
  Serial.print("Arm 2:");
  Serial.println(servoDegree[1]);
  Serial.print("Arm 3:");
  Serial.println(servoDegree[2]);
  Serial.print("Arm 4:");
  Serial.println(servoDegree[3]);
}

void parseDegree(String data){
  int i=1,servoNo=0,val;
  Serial.println(data);
  while(data[i]!='}' && data[i]!='\0'){
    val=0;
    while(data[i]!=',' && data[i]!='}'){
      val*=10;
      int temp = data[i]-48;
      val+=temp;
      i++;
    }
    i++;
    prevServoDegree[servoNo]=servoDegree[servoNo];
    servoDegree[servoNo++]=val;
  }
  printArmData();
}
Servo s1,s2,s3,s4;

void controlArm()
{
  if(prevServoDegree[0]!=servoDegree[0]){
    s1.write(servoDegree[0]);
  }
  if(prevServoDegree[1]!=servoDegree[1]){
    s2.write(servoDegree[1]);
  }
  if(prevServoDegree[2]!=servoDegree[2]){
    s3.write(servoDegree[2]);
  }
  if(prevServoDegree[3]!=servoDegree[3]){
    s4.write(servoDegree[3]);
  }
}
