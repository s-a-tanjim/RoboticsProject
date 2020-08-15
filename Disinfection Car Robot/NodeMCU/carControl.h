int motorPWM = 0;
char currentDirection = 'e';

void forward()
{ 
  digitalWrite(motorEnablePin,HIGH);
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(rpf,motorPWM);
  analogWrite(rpr,0);

  digitalWrite(motorEnablePin,HIGH);
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(lpf,motorPWM);
  analogWrite(lpr,0);
}

void backward()
{
  digitalWrite(motorEnablePin,HIGH);
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(rpf,0);
  analogWrite(rpr,motorPWM);

  digitalWrite(motorEnablePin,HIGH);
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(lpf,0);
  analogWrite(lpr,motorPWM);
}

void breaks()
{
  digitalWrite(motorEnablePin,LOW);
  digitalWrite(motorEnablePin,LOW);
  
  digitalWrite(motorEnablePin,LOW);
  digitalWrite(motorEnablePin,LOW);
}
void tright()
{
  digitalWrite(motorEnablePin,HIGH);
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(rpf,0);
  analogWrite(rpr,motorPWM);

  digitalWrite(motorEnablePin,HIGH);
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(lpf,motorPWM);
  analogWrite(lpr,0);
}

void tleft()
{
  digitalWrite(motorEnablePin,HIGH);
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(rpf,motorPWM);
  analogWrite(rpr,0);

  digitalWrite(motorEnablePin,HIGH);
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(lpf,0);
  analogWrite(lpr,motorPWM);
}

int parsePWM(String x){
  int i=0;
  int val=0;
  while(x[i]!='\0'){
    val*=10;
    int temp = x[i]-48;
    val+=temp;
    i++;
  }
  return val;
}

void driveCar(char Direction,String PWM){
  motorPWM = parsePWM(PWM);
  currentDirection = Direction;
  if(Direction=='w'){
    forward();
  } else if (Direction=='s'){
    backward();
  } else if (Direction=='a'){
    tleft();
  } else if (Direction=='d'){
    tright();
  } else if (Direction=='e'){
    breaks();
  }
}
