#include<ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//UVC Pin
#define UVC_Pin 16 //D0
//Motor Pin
#define motorEnablePin 10 // SDD3
#define rpf 5 // D1 (Right_motor_PWm_forward)
#define rpr 4 // D2 (Right_motor_PWm_Reverse)
#define lpf 0 // D3 (Left_motor_PWm_forward)
#define lpr 2 // D4 (Left_motor_PWm_reverse)
//Servo Pin
#define servo1Pin 14 //D5
#define servo2Pin 12 //D6
#define servo3Pin 13 //D7
#define servo4Pin 15 //D8
bool uvc_status = false;

#include "armControl.h"
#include "carControl.h"
#include "utilFunc.h"

const char* ssid="Themistocles";
const char* password="01824433198%619";

WiFiClient client;
ESP8266WebServer server(80);

#include "html.h"
#include "requestHandle.h"

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  Serial.println("Connected");

  server.begin();
  Serial.println("Server Connected!");
  Serial.print("Use this IP to connect:"); 
  Serial.print(WiFi.localIP());  

  server.on("/", [](){
    server.send(200, "text/html", htmlData);
  });
  server.on("/forward",Forward_handle);
  server.on("/backward",Backward_handle);
  server.on("/left",Left_handle);
  server.on("/right",Right_handle);
  server.on("/stop",Stop_handle);
  server.on("/goforward",GoForward_handle);

  server.begin();
  Serial.println("Web server started!");

  pinMode(UVC_Pin,OUTPUT);
  pinMode(motorEnablePin,OUTPUT);
  pinMode(rpf,OUTPUT);
  pinMode(rpr,OUTPUT);
  pinMode(lpf,OUTPUT);
  pinMode(lpr,OUTPUT);
  s1.attach(servo1Pin);
  s2.attach(servo2Pin);
  s3.attach(servo3Pin);
  s4.attach(servo4Pin);
}

void loop() {
  server.handleClient();
  if(WiFi.status()==WL_CONNECTED){
    if(uvc_status){
      digitalWrite(UVC_Pin,HIGH);
    } else {
      digitalWrite(UVC_Pin,LOW);
    }
  } else {
    stopALL();
  }
}
