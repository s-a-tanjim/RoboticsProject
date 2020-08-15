void uvcControl(String data){
  Serial.println(data);
  if(data=="1"){
    uvc_status = true;
  } else {
    uvc_status = false;
  }
}

void stopALL(){
  digitalWrite(UVC_Pin,HIGH); //Off UVC
  breaks(); //Break Car
}

void updateResponseData(){ 
  responseData="*"+batteryData+"^";
  if(uvc_status)
    responseData+="1";
  else
    responseData+="0";
  responseData+="^";
  if(car_status)
    responseData+="1";
  else
    responseData+="0";
  responseData+="*";
}

void readTxRxData(){
  if(Serial2.available()>0){
    digitalWrite(txrxIndicatorPin,HIGH);
    String x;
    while(Serial2.available()>0){
      char c=Serial2.read();
      x+=c;
    }
    
    currentTxRxVal = x;
    Serial.print("String: "); // *00^100*
    Serial.println(x);

    int i=0;
    while(x.length()>i && x[i]!='*'){
      if(x[i]=='^')
      //Error data
      i++;
    }
    i++;
    if(x.length()>i+1){
      if(x[i]=='0')
        canGoForward = false;
      else
        canGoForward = true;
      if(x[i+1]=='0')
        canGoBackward = false;
      else
        canGoBackward = true;
    }
    i=4;
    if(x.length()>i && x[i-1]=='^'){
      batteryData="";
      batteryData+=x[i++];
      if(x.length()>i && x[i]!='*'){
        batteryData+=x[i++];
        if(x.length()>i && x[i]!='*'){
          batteryData+=x[i++];
        }
      }
    }
   Serial.print("Battery :");
   Serial.println(batteryData);
  } else {
    digitalWrite(txrxIndicatorPin,LOW);
  }
}
