#include "temp.h"
#define STEP_TIME 2000

#define motor_p_pin 3
#define motor_n_pin 5
#define motor_en_pin_0 6
#define motor_en_pin_1 7
int speeed = 70;
int stepp = 1,heater_btn_state = 0, cooler_btn_state = 0;
boolean can_temp_up = false,can_temp_down = false;

#define peltier_en_pin 8
#define pump_en_pin 9
#define heater_en_pin 10
#define cooler_btn_pin 11
#define heater_btn_pin 12

#include "relay_device.h"
#include "motor.h"

void setup() {
  Serial.begin(9600);

  pinMode(motor_p_pin,OUTPUT);
  pinMode(motor_n_pin,OUTPUT);
  pinMode(motor_en_pin_0,OUTPUT);
  pinMode(motor_en_pin_1,OUTPUT);
  
  pinMode(peltier_en_pin,OUTPUT);
  pinMode(pump_en_pin,OUTPUT);
  pinMode(heater_en_pin,OUTPUT);

  pinMode(cooler_btn_pin,INPUT);
  pinMode(heater_btn_pin,INPUT);

  
  //Stop all
  breaks();
  cooler_off();
  heater_off();
}
void loop() {
  int pt100 = analogRead(A0);

  float Vout = pt100 * (5.0 / 1023.0);
  float R2 = R1 * 1/(5.0/Vout - 1);

  float c =  MultiMap(R2,in,80);
  
  //Serial.print("Resistance: ");
  //Serial.print(R2);
  //Serial.println(" Ohm");
  
  //Serial.print("Temperature: ");
  Serial.println(c);
  //Serial.println(" C");
  
  heater_btn_state = digitalRead(heater_btn_pin);
  cooler_btn_state = digitalRead(cooler_btn_pin);
  //Serial.println(heater_btn_state);
  //Serial.println(cooler_btn_state);

  if (heater_btn_state == HIGH && c<60.0) {
    can_temp_up = true;
  } else {
    can_temp_up = false;
  }

  if (cooler_btn_state == HIGH && c>4.0) {
    can_temp_down = true;
  } else {
    can_temp_down = false;
  }

  if(can_temp_up) {
    //Serial.println("Heater On");
    heater_on();
    cooler_off();
  } else {
    //Serial.println("Heater Off");
    heater_off();
  }

  if(can_temp_down) {
    //Serial.println("Cooler On");
    cooler_on();
    heater_off();
  } else {
    //Serial.println("Cooler Off");
    cooler_off();
  }

  if(c<=25.0){
    control_rod(stepp,1);
  } else if(c>25.0 && c<=50.0) {
    control_rod(stepp,2);
  } else if(c>50.0 && c<=55.0) {
    control_rod(stepp,3);
  } else if(c>55.0) {
    control_rod(stepp,4);
  }

  /*control_rod(stepp,1);
  delay(2000);
  control_rod(stepp,2);
  delay(2000);
  control_rod(stepp,3);
  delay(2000);
  control_rod(stepp,4);
  delay(2000);*/
  delay(400);
}
