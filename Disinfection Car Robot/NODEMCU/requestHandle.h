void printData(){
  Serial.print("Arg1: ");
  Serial.print(server.argName(0));
  Serial.print(" = ");
  Serial.println(server.arg(0));
  Serial.print("Arg2: ");
  Serial.print(server.argName(1));
  Serial.print(" = ");
  Serial.println(server.arg(1));
  Serial.print(server.argName(2));
  Serial.print(" = ");
  Serial.println(server.arg(2));
  Serial.print(server.argName(3));
  Serial.print(" = ");
  Serial.println(server.arg(3));
}

void uvcControl(){
  if(server.arg(1)=="1"){
    uvc_status = true;
  } else {
    uvc_status = false;
  }
}

void sendOverSerial(String dir){
  if(server.argName(3)=="servoflag"){
    parseDegree(server.arg(2));
    controlArm();
  } else {
    if(canSendTxRx){
      char *x = stringToCharPtr(dir+"<"+server.arg(0)+">");
      int sentByte = ARDUINO_Serial.write(x);
      ARDUINO_Serial.flush();
      canSendTxRx=false;
      delete x;
    }
  }
}

void Forward_handle(){
  Serial.println("Forward");
   server.send(200, "text/html", "Success"); 
   printData();
   goForwardFlag=false;
   sendOverSerial("w");
}

void Backward_handle(){
  Serial.println("Backward");
  server.send(200, "text/html", "Success"); 
  printData();
  goForwardFlag=false;
  sendOverSerial("s");
}

void Stop_handle(){
  Serial.println("Stop");
  server.send(200, "text/html", "Success"); 
  printData();
  goForwardFlag=false;
  sendOverSerial("e");
}

void Left_handle(){
  Serial.println("Left");
  server.send(200, "text/html", "Success"); 
  printData();
  goForwardFlag=false;
  sendOverSerial("a");
}

void Right_handle(){
  Serial.println("Right");
  server.send(200, "text/html", "Success");
  printData();
  goForwardFlag=false;
  sendOverSerial("d");
}

void GoForward_handle(){
  Serial.println("GoForward");
  server.send(200, "text/html", "Success");
  printData();
  goForwardFlag=true;
  sendOverSerial("w");
}
