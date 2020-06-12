void uvcControl(String data){
  Serial.println(data);
  if(data=="1"){
    uvc_status = true;
  } else {
    uvc_status = false;
  }
}

void stopALL(){
  digitalWrite(UVC_Pin,LOW); //Off UVC
  breaks(); //Break Car
  resetArm();
}
