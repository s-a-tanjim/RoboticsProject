#include<NewPing.h>

#define TRIG 8
#define ECHO 9
#define RELAY 7
#define MAX_DIST 200
#define MIN_DIST 100
#define DELAY_OF_PUMP 500

int counter = 0;
bool flag=false;

NewPing sonar(TRIG,ECHO,MAX_DIST);

void setup(){
  pinMode(RELAY,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int distance=sonar.ping_cm();
  Serial.println(distance);
  /*if(distance<MIN_DIST && distance!=0) {
    digitalWrite(RELAY,HIGH);
    delay(DELAY_OF_PUMP);
  } else {
    digitalWrite(RELAY,LOW);
    delay(100);
  }*/
  if(distance<MIN_DIST && distance!=0){
    flag=true;
    counter=1;
  } else {
    flag=false;
    if(counter==0){
      digitalWrite(RELAY,HIGH);//Off
      Serial.println("Off!");
    }
  }

  if(counter<8 && counter!=0){
    digitalWrite(RELAY,LOW);//On
    Serial.println("On!");
    counter++;
  } else {
    counter=0;
  }
  delay(DELAY_OF_PUMP);
}
