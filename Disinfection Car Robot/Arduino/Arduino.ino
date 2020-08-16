//Sonar Pin
#define sonarTrigForward1Pin 2
#define sonarEchoForward1Pin 3
#define sonarTrigForward2Pin 4
#define sonarEchoForward2Pin 5
#define sonarTrigBackward1Pin 6
#define sonarEchoBackward1Pin 7
#define sonarTrigBackward2Pin 8
#define sonarEchoBackward2Pin 9

#define upperSonar1TrigPin 10
#define upperSonar1EchoPin 11
#define upperSonar2TrigPin 12
#define upperSonar2EchoPin 13

#define batterySensorPin A0

#define obstacleIndicatorPin 30
#define mustStopIndicatorPin 32

#define motorEnablePin 34

#define MAX_DIST 250 //cm
#define MIN_DIST 60 //cm
#define LOWEST_DIST 10 //cm
#define UPPER_MIN_DIST 90 //cm

String sendingData,prevData="Null";
char sendingDataArr[10];
boolean isObstacle = false;  //for indicator
boolean mustStopFlag = true; //to disable motor


#include "sonarControl.h"
#include "batterySensor.h"

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(obstacleIndicatorPin,OUTPUT);
  pinMode(mustStopIndicatorPin,OUTPUT);
  pinMode(motorEnablePin,OUTPUT);
}

void stringToArr(){
  int i;
  for(i=0;i<sendingData.length();i++){
    sendingDataArr[i]=sendingData[i];
  }
  sendingDataArr[i]='\0';
}

void loop(){
  sendingData="*";
  readSonarData();
  getBatteryData();
  
  sendingData+=String(batteryValueParcent);
  sendingData+="*";
  
  if(sendingData!=prevData){
    stringToArr();
    Serial1.write(sendingDataArr);
    Serial1.flush();
    prevData=sendingData;
    Serial.print("Sent: ");
    Serial.println(sendingDataArr);
  }
  if(isObstacle)
    digitalWrite(obstacleIndicatorPin,HIGH);
  else
    digitalWrite(obstacleIndicatorPin,LOW);
  
  if(mustStopFlag){
    digitalWrite(mustStopIndicatorPin,HIGH);
    digitalWrite(motorEnablePin,LOW);
  }
  else{
    digitalWrite(mustStopIndicatorPin,LOW);
    digitalWrite(motorEnablePin,HIGH);
  }

  
  delay(50);
  //delay(1000);
}
