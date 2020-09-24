int motorPWM = 0;
char currentDirection = 'e';

void forward()
{ 
  car_status=true;
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(rpf,motorPWM);
  analogWrite(rpr,0);

  analogWrite(lpf,motorPWM);
  analogWrite(lpr,0);
}

void backward()
{
  car_status=true;
  digitalWrite(motorEnablePin,HIGH);
  analogWrite(rpf,0);
  analogWrite(rpr,motorPWM);

  analogWrite(lpf,0);
  analogWrite(lpr,motorPWM);
}

void breaks()
{
  car_status=false;
  digitalWrite(motorEnablePin,LOW);
  analogWrite(rpf,0);
  analogWrite(rpr,0);
  analogWrite(lpf,0);
  analogWrite(lpr,0);
}
void tright()
{
  car_status=true;
  digitalWrite(motorEnablePin,HIGH);

  analogWrite(rpf,0);
  analogWrite(rpr,motorPWM);

  analogWrite(lpf,motorPWM);
  analogWrite(lpr,0);
}

void tleft()
{
  car_status=true;
  digitalWrite(motorEnablePin,HIGH);
  
  analogWrite(rpf,motorPWM);
  analogWrite(rpr,0);
  
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
  if(motorPWM>90) 
    motorPWM=90;
  if(currentDirection!=Direction) {
    breaks();
    delay(350);
  }
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
