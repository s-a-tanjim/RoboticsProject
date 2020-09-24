#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include<HardwareSerial.h>
#include <analogWrite.h>

//UVC Pin
#define UVC_Pin 32 //
//Motor Pin
#define motorEnablePin 14 // SDD3
#define rpf 26 // (Right_motor_PWm_forward)
#define rpr 27 // (Right_motor_PWm_Reverse)
#define lpf 25 // (Left_motor_PWm_forward)
#define lpr 33 // (Left_motor_PWm_reverse)
//indicator LED pin
#define wifiIndicatorPin 18
#define txrxIndicatorPin 19

String currentTxRxVal="Null";
String responseData = "*0^0^0*"; 
bool uvc_status = false,car_status=false;
boolean canGoForward = false, canGoBackward = false, protectedMode = false;
//boolean canGoForward = true, canGoBackward = true;
String batteryData="000";

#include "carControl.h"
#include "utilFunc.h"

const char* ssid="UVC_Purge_0002";
const char* password="disinfect_uvc";

//const char* ssid="DLINK";
//const char* password="12345678";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

#include "html.h"
#include "requestHandle.h"

void setup() {
  pinMode(UVC_Pin,OUTPUT);
  pinMode(motorEnablePin,OUTPUT);
  pinMode(rpf,OUTPUT);
  pinMode(rpr,OUTPUT);
  pinMode(lpf,OUTPUT);
  pinMode(lpr,OUTPUT);
  pinMode(wifiIndicatorPin,OUTPUT);
  pinMode(txrxIndicatorPin,OUTPUT);
  stopALL();
  
  //Serial.begin(115200);
  Serial2.begin(9600);
  delay(10);

  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(200);
  }

  server.on("/",HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", htmlData);
  });
  server.on("/forward",HTTP_GET,Forward_handle);
  server.on("/backward",HTTP_GET,Backward_handle);
  server.on("/left",HTTP_GET,Left_handle);
  server.on("/right",HTTP_GET,Right_handle);
  server.on("/stop",HTTP_GET,Stop_handle);
  server.on("/protectedmode",HTTP_GET,Protected_Mode_handle);

  server.begin();
}

void loop() {
  if(WiFi.status()==WL_CONNECTED){
    digitalWrite(wifiIndicatorPin,HIGH);
    readTxRxData();
    if(currentDirection=='w' && !canGoForward && protectedMode){
      breaks(); //break car
    } else if (currentDirection=='s' && !canGoBackward && protectedMode){
      breaks(); //break car
    }
    if(uvc_status){
      digitalWrite(UVC_Pin,HIGH);
    } else {
      digitalWrite(UVC_Pin,LOW);
    }
    updateResponseData();
  } else {
    digitalWrite(wifiIndicatorPin,LOW);
    stopALL();
  }
}
