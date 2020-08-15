#include<NewPing.h>

NewPing sonarForward1(sonarTrigForward1Pin,sonarEchoForward1Pin,MAX_DIST);
NewPing sonarForward2(sonarTrigForward2Pin,sonarEchoForward2Pin,MAX_DIST);
NewPing sonarBackward1(sonarTrigBackward1Pin,sonarEchoBackward1Pin,MAX_DIST);
NewPing sonarBackward2(sonarTrigBackward2Pin,sonarEchoBackward2Pin,MAX_DIST);

int forward1Dist,forward2Dist,backward1Dist,backward2Dist;
boolean canGoForward = false, canGoBackward = false;
boolean sendGoForwardFlag = false,sendGoBackwardFlag = false;
boolean sendStopForwardFlag = false,sendStopBackwardFlag = false;

void printSonarData(){
  Serial.print("Forward1: ");
  Serial.println(forward1Dist);
  Serial.print("Forward2: ");
  Serial.println(forward2Dist);

  Serial.print("Backward1: ");
  Serial.println(backward1Dist);
  Serial.print("Backward1: ");
  Serial.println(backward2Dist);
  Serial.print("CanGoForward:");
  Serial.println(canGoForward);
  Serial.print("canGoBackward:");
  Serial.println(canGoBackward);
  Serial.println("......");
}

void readSonarData(){
  forward1Dist = sonarForward1.ping_cm();
  forward2Dist = sonarForward2.ping_cm();
  backward1Dist = sonarBackward1.ping_cm();
  backward2Dist = sonarBackward2.ping_cm();
  
  isObstacle=false;
  if(forward1Dist!=0 && forward1Dist<MIN_DIST || forward2Dist!=0 && forward2Dist<MIN_DIST  ){
    canGoForward = false;
    sendingData+="0";
    isObstacle=true;
  } else {
    canGoForward = true;
    sendingData+="1";
  }
  
  if(backward1Dist!=0 && backward1Dist<MIN_DIST || backward2Dist!=0 && backward2Dist<MIN_DIST){
    canGoBackward = false;
    sendingData+="0";
    isObstacle=true;
  } else {
    canGoBackward =true;
    sendingData+="1";
  }
  sendingData+="^";
  printSonarData();
}
