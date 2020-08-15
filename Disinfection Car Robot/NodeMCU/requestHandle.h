void printData(){
  Serial.print("Arg1: ");
  Serial.print(server.argName(0)); // pwm
  Serial.print(" = ");
  Serial.println(server.arg(0));
  Serial.print("Arg2: ");
  Serial.print(server.argName(1)); // uvl
  Serial.print(" = ");
  Serial.println(server.arg(1));
}

void commonHandler(char Direction){
  printData();
  uvcControl(server.arg(1));
  if(Direction!='w' && Direction!='s')
    driveCar(Direction,server.arg(0));
  else if(Direction=='w' && canGoForward || Direction=='s' && canGoBackward)
    driveCar(Direction,server.arg(0));
}

void printHeaders(){
  //Serial.println(server.header());
  //Serial.println(server.headerName());
  //Serial.println(server.hostHeader());
  //Serial.println(server.headers());
}

void Forward_handle(){
   //server.send(200, "text/html", currentTxRxVal); 
   printHeaders();
   server.send(200, "text/html", "<html><head></head><body>Test</body></html>"); 
   Serial.println("Sent!");
   commonHandler('w');
}

void Backward_handle(){
  server.send(200, "text/html", currentTxRxVal); 
  commonHandler('s');
}

void Stop_handle(){
  //server.send(200, "text/html", currentTxRxVal); 
  printHeaders();
  server.send(200, "text/html","HTTP/1.0 200 OK\r\nServer: NodeMCU on ESP8266\r\nContent-Type: text/html\r\n\r\n<h1> Hello, NodeMCU.</h1>");
  Serial.println("Sent!");
  commonHandler('e');
}

void Left_handle(){
  server.send(200, "text/html", currentTxRxVal); 
  commonHandler('a');
}

void Right_handle(){
  server.send(200, "text/html", currentTxRxVal);
  commonHandler('d');
}

void GoForward_handle(){
  server.send(200, "text/html", currentTxRxVal);
  commonHandler('w');
}
