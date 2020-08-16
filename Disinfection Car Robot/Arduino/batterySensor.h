#define HIGHEST_BATTERY 12.1
#define LOWEST_BATTERY 10.5
int val,batteryValueParcent;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;

void getBatteryData(){
  val = analogRead(batterySensorPin);
  //vOUT = (val * 5.0) / 1024.0;
  vOUT = (val * 5.0) / 930;
  vIN = vOUT / (R2/(R1+R2));
  batteryValueParcent=(float)((vIN-LOWEST_BATTERY)*100)/(HIGHEST_BATTERY-LOWEST_BATTERY);
  if(batteryValueParcent>100) batteryValueParcent=100;
  else if(batteryValueParcent<0)batteryValueParcent=0;
  Serial.print("Vin: ");
  Serial.println(vIN);
  Serial.print("Battery: ");
  Serial.println(batteryValueParcent);
}
