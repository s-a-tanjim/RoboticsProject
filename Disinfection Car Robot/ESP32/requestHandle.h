void printData(String pwm_val,String uv_status){
  Serial.print("PWM : "); // pwm
  Serial.println(pwm_val);
  Serial.print("UVL: "); // uvl
  Serial.println(uv_status);
}

void commonHandler(char Direction,String pwm_val,String uv_status){
  printData(pwm_val,uv_status);
  uvcControl(uv_status);
  if(Direction!='w' && Direction!='s')
    driveCar(Direction,pwm_val);
  else if(Direction=='w' && canGoForward || Direction=='s' && canGoBackward)
    driveCar(Direction,pwm_val);
}

void printHeaders(){
  //Serial.println(server.header());
  //Serial.println(server.headerName());
  //Serial.println(server.hostHeader());
  //Serial.println(server.headers());
}

/*
if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
   inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
   inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
   digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
}

*/

void Forward_handle(AsyncWebServerRequest *request){
   request->send(200, "text/plain", currentTxRxVal);
   if (request->hasParam("pwm") && request->hasParam("uvl")){
      commonHandler('w',request->getParam("pwm")->value(),request->getParam("uvl")->value());
   }
   Serial.println("Sent! Forward");
}

void Backward_handle(AsyncWebServerRequest *request){
  request->send(200, "text/plain", responseData); 
  if (request->hasParam("pwm") && request->hasParam("uvl")){
      commonHandler('s',request->getParam("pwm")->value(),request->getParam("uvl")->value());
  }
  Serial.println("Sent! Backward");
  //commonHandler('s');
}

void Stop_handle(AsyncWebServerRequest *request){
  request->send(200, "text/plain",responseData);
  if (request->hasParam("pwm") && request->hasParam("uvl")){
      commonHandler('e',request->getParam("pwm")->value(),request->getParam("uvl")->value());
  }
  Serial.println("Sent! Stop");
  //commonHandler('e');
}

void Left_handle(AsyncWebServerRequest *request){
  request->send(200, "text/plain", responseData); 
  if (request->hasParam("pwm") && request->hasParam("uvl")){
      commonHandler('a',request->getParam("pwm")->value(),request->getParam("uvl")->value());
  }
  Serial.println("Sent! Left");
  //commonHandler('a');
}

void Right_handle(AsyncWebServerRequest *request){
  request->send(200, "text/plain", responseData);
  if (request->hasParam("pwm") && request->hasParam("uvl")){
    commonHandler('d',request->getParam("pwm")->value(),request->getParam("uvl")->value());
  }
  Serial.println("Sent! Right");
  //commonHandler('d');
}
