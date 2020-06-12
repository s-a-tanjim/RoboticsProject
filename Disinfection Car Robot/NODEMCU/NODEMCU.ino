#include<ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include<SoftwareSerial.h>
#include "utilFunc.h"
#include "armControl.h"

#define UVC_Pin 16
bool uvc_status = false;
bool goForwardFlag = false;
bool canSendTxRx = true;

const char* ssid="Themistocles";
const char* password="01824433198%619";

WiFiClient client;
ESP8266WebServer server(80);
SoftwareSerial ARDUINO_Serial(4, 5);  //D2, D1 = SRX, STX

#include "html.h"
#include "requestHandle.h"

void setup() {
  Serial.begin(9600);
  ARDUINO_Serial.begin(9600);
  pinMode(UVC_Pin,OUTPUT);
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
  s1.attach(servo1Pin);
  s2.attach(servo2Pin);
  s3.attach(servo3Pin);
  s4.attach(servo4Pin);
}

void loop() {
  server.handleClient();
  if(ARDUINO_Serial.available()>0){
    Serial.print("Received!: ");
    char x=ARDUINO_Serial.read();
    Serial.println(x);
    if(x=='>'){
      canSendTxRx=true;
    }
  }
  if(WiFi.status()==WL_CONNECTED){
    if(uvc_status){
      digitalWrite(UVC_Pin,HIGH);
    } else {
      digitalWrite(UVC_Pin,LOW);
    }
    if(goForwardFlag){
      Forward_handle();
      goForwardFlag=true;
    }
  } else {
    digitalWrite(UVC_Pin,LOW);
    Stop_handle();
  }
}
