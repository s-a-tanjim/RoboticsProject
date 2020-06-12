void printData(){
  Serial.print("Arg1: ");
  Serial.print(server.argName(0)); // pwm
  Serial.print(" = ");
  Serial.println(server.arg(0));
  Serial.print("Arg2: ");
  Serial.print(server.argName(1)); // uvl
  Serial.print(" = ");
  Serial.println(server.arg(1));
  Serial.print(server.argName(2)); // servo
  Serial.print(" = ");
  Serial.println(server.arg(2));
  Serial.print(server.argName(3)); // servoflag
  Serial.print(" = ");
  Serial.println(server.arg(3));
}

void commonHandler(char Direction){
  printData();
  uvcControl(server.arg(1));
  if(server.argName(3)=="servoflag"){
    controlArm(server.arg(2));
  } else {
    driveCar(Direction,server.arg(0));
  }
  
}

void Forward_handle(){
   server.send(200, "text/html", "Success"); 
   commonHandler('w');
}

void Backward_handle(){
  server.send(200, "text/html", "Success"); 
  commonHandler('s');
}

void Stop_handle(){
  server.send(200, "text/html", "Success"); 
  commonHandler('e');
}

void Left_handle(){
  server.send(200, "text/html", "Success"); 
  commonHandler('a');
}

void Right_handle(){
  server.send(200, "text/html", "Success");
  commonHandler('d');
}

void GoForward_handle(){
  server.send(200, "text/html", "Success");
  commonHandler('w');
}
