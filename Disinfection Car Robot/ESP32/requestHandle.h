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
  else if((Direction=='w' && canGoForward) || (Direction=='s' && canGoBackward) || superUserMode)
    driveCar(Direction,pwm_val);
}

void Forward_handle(AsyncWebServerRequest *request){
   request->send(200, "text/plain", currentTxRxVal);
   if (request->hasParam("pwm") && request->hasParam("uvl")){
      commonHandler('w',request->getParam("pwm")->value(),request->getParam("uvl")->value());
   }
}

void Backward_handle(AsyncWebServerRequest *request){
  request->send(200, "text/plain", responseData); 
  if (request->hasParam("pwm") && request->hasParam("uvl")){
      commonHandler('s',request->getParam("pwm")->value(),request->getParam("uvl")->value());
  }
}

void Stop_handle(AsyncWebServerRequest *request){
  request->send(200, "text/plain",responseData);
  if (request->hasParam("pwm") && request->hasParam("uvl")){
      commonHandler('e',request->getParam("pwm")->value(),request->getParam("uvl")->value());
  }
}

void Left_handle(AsyncWebServerRequest *request){
  request->send(200, "text/plain", responseData); 
  if (request->hasParam("pwm") && request->hasParam("uvl")){
      commonHandler('a',request->getParam("pwm")->value(),request->getParam("uvl")->value());
  }
}

void Right_handle(AsyncWebServerRequest *request){
  request->send(200, "text/plain", responseData);
  if (request->hasParam("pwm") && request->hasParam("uvl")){
    commonHandler('d',request->getParam("pwm")->value(),request->getParam("uvl")->value());
  }
}

void Super_Mode_handle(AsyncWebServerRequest *request){
  request->send(200, "text/plain", responseData);
  superUserMode = !superUserMode;
  if (request->hasParam("pwm") && request->hasParam("uvl")){
    commonHandler('e',request->getParam("pwm")->value(),request->getParam("uvl")->value());
  }
}

