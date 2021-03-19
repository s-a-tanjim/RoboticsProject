void cooler_on(){
  digitalWrite(peltier_en_pin,HIGH); //peltier_on
  digitalWrite(pump_en_pin,LOW); //Pump on
}

void cooler_off(){
  digitalWrite(peltier_en_pin,LOW); //peltier_off
  digitalWrite(pump_en_pin,HIGH); //pump_off
}


void heater_on(){
  digitalWrite(heater_en_pin,LOW);
}

void heater_off(){
  digitalWrite(heater_en_pin,HIGH);
}
