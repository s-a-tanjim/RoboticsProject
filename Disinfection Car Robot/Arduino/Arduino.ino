
//Sonar Pin
#define sonarTrigForward1Pin 4
#define sonarEchoForward1Pin 5
#define sonarTrigForward2Pin 6
#define sonarEchoForward2Pin 7
#define sonarTrigBackward1Pin 8
#define sonarEchoBackward1Pin 9
#define sonarTrigBackward2Pin 10
#define sonarEchoBackward2Pin 11

#define batterySensorPin A0

#define obstacleIndicatorPin 30

#define MAX_DIST 250 //cm
#define MIN_DIST 60 //cm

String sendingData,prevData="Null";
char sendingDataArr[10];
boolean isObstacle = false;


#include "sonarControl.h"
#include "batterySensor.h"

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(obstacleIndicatorPin,OUTPUT);
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
    
  delay(50);
  //delay(1000);
}
