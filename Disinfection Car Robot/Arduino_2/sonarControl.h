#include<NewPing.h>

NewPing sonarForward1(sonarTrigForward1Pin,sonarEchoForward1Pin,MAX_DIST);
NewPing sonarForward2(sonarTrigForward2Pin,sonarEchoForward2Pin,MAX_DIST);
NewPing sonarForward3(sonarTrigForward3Pin,sonarEchoForward3Pin,MAX_DIST);
NewPing sonarBackward1(sonarTrigBackward1Pin,sonarEchoBackward1Pin,MAX_DIST);
NewPing sonarBackward2(sonarTrigBackward2Pin,sonarEchoBackward2Pin,MAX_DIST);
NewPing sonarBackward3(sonarTrigBackward3Pin,sonarEchoBackward3Pin,MAX_DIST);

int forward1Dist,forward2Dist,forward3Dist,backward1Dist,backward2Dist,backward3Dist;
boolean canGoForward = false, canGoBackward = false;

void printSonarData(){
  Serial.print("Forward1: ");
  Serial.println(forward1Dist);
  Serial.print("Forward2: ");
  Serial.println(forward2Dist);
  Serial.print("Forward3: ");
  Serial.println(forward3Dist);

  Serial.print("Backward1: ");
  Serial.println(backward1Dist);
  Serial.print("Backward2: ");
  Serial.println(backward2Dist);
  Serial.print("Backward3: ");
  Serial.println(backward3Dist);
  
  Serial.print("CanGoForward:");
  Serial.println(canGoForward);
  Serial.print("canGoBackward:");
  Serial.println(canGoBackward);
  Serial.println("......");
}

void readNewData(){
  forward1Dist = sonarForward1.ping_cm();
  forward2Dist = sonarForward2.ping_cm();
  forward3Dist = sonarForward3.ping_cm();
  backward1Dist = sonarBackward1.ping_cm();
  backward2Dist = sonarBackward2.ping_cm();
  backward3Dist = sonarBackward3.ping_cm();
  if(forward1Dist==0) forward1Dist = MAX_DIST;
  if(forward2Dist==0) forward2Dist = MAX_DIST;
  if(forward3Dist==0) forward3Dist = MAX_DIST;
  if(backward1Dist==0) backward1Dist = MAX_DIST;
  if(backward2Dist==0) backward2Dist = MAX_DIST;
  if(backward3Dist==0) backward3Dist = MAX_DIST;
  printSonarData();
}

void readData(){
  int forward1DistTemp = sonarForward1.ping_cm();
  int forward2DistTemp = sonarForward2.ping_cm();
  int forward3DistTemp = sonarForward3.ping_cm();
  int backward1DistTemp = sonarBackward1.ping_cm();
  int backward2DistTemp = sonarBackward2.ping_cm();
  int backward3DistTemp = sonarBackward3.ping_cm();

  if(forward1DistTemp==0) forward1DistTemp = MAX_DIST;
  if(forward2DistTemp==0) forward2DistTemp = MAX_DIST;
  if(forward3DistTemp==0) forward3DistTemp = MAX_DIST;
  if(backward1DistTemp==0) backward1DistTemp = MAX_DIST;
  if(backward2DistTemp==0) backward2DistTemp = MAX_DIST;
  if(backward3DistTemp==0) backward3DistTemp = MAX_DIST;

  forward1Dist = (forward1DistTemp + forward1Dist)/2;
  forward2Dist = (forward2DistTemp + forward2Dist)/2;
  forward3Dist = (forward3DistTemp + forward3Dist)/2;
  backward1Dist = (backward1DistTemp + backward1Dist)/2;
  backward2Dist = (backward2DistTemp + backward2Dist)/2;
  backward3Dist = (backward3DistTemp + backward3Dist)/2;
  printSonarData();
}

void readSonarData(){
  readNewData();
  readData();
  readData();
  
  isObstacle=false;
  if(forward1Dist!=0 && forward1Dist<MIN_DIST || 
     forward2Dist!=0 && forward2Dist<MIN_DIST || 
     forward3Dist!=0 && forward3Dist<MIN_DIST){
    canGoForward = false;
    sendingData+="0";
    isObstacle=true;
  } else {
    canGoForward = true;
    sendingData+="1";
  }
  
  if(backward1Dist!=0 && backward1Dist<MIN_DIST || 
     backward2Dist!=0 && backward2Dist<MIN_DIST || 
     backward3Dist!=0 && backward3Dist<MIN_DIST){
    canGoBackward = false;
    sendingData+="0";
    isObstacle=true;
  } else {
    canGoBackward =true;
    sendingData+="1";
  }
  sendingData+="^";
  //printSonarData();
  Serial.println("___________");
}
