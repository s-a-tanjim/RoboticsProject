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

void handleCornerCaseTxRx(String x){
  int len = x.length();
  //Forward Handle
  int i=len-1;
  while(i>=0){
    if(x[i]=='f'){
      canGoForward = true;
      break;
    } else if(x[i]=='s'){
      canGoForward = false;
      break;
    }
    i--;
  }
  //Backward Handle
  i=len-1;
  while(i>=0){
    if(x[i]=='b'){
      canGoBackward = true;
      break;
    } else if(x[i]=='p'){
      canGoBackward = false;
      break;
    }
    i--;
  }
  
}

void readTxRxData(){
  if(Arduino_Serial.available()>0){
    String x;
    x =Arduino_Serial.readString();
    currentTxRxVal = x;
    Serial.print("String: ");
    Serial.println(x);
    if(x=="p"){
      canGoBackward = false;
    } else if (x=="s") {
      canGoForward = false;
    } else if(x=="ps" || x=="sp") {
      canGoBackward = false;
      canGoForward = false;
    } else if (x=="f") {
      canGoForward = true;
    } else if(x=="b") {
      canGoBackward = true;
    } else if(x=="bf" || x=="fb") {
      canGoBackward = true;
      canGoForward = true;
    } else {
      if(x.length()>2)
        handleCornerCaseTxRx(x);
    }
  }
}
