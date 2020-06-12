void forward()
{ 
  digitalWrite(rmp,HIGH);
  digitalWrite(rmm,HIGH);
  analogWrite(rpf,speeds);
  analogWrite(rpr,0);

  digitalWrite(lmp,HIGH);
  digitalWrite(lmm,HIGH);
  analogWrite(lpf,speeds);
  analogWrite(lpr,0);
}

void backward()
{
  digitalWrite(rmp,HIGH);
  digitalWrite(rmm,HIGH);
  analogWrite(rpf,0);
  analogWrite(rpr,speeds);

  digitalWrite(lmp,HIGH);
  digitalWrite(lmm,HIGH);
  analogWrite(lpf,0);
  analogWrite(lpr,speeds);
}

void breaks()
{
  digitalWrite(rmp,LOW);
  digitalWrite(rmm,LOW);
  
  digitalWrite(lmp,LOW);
  digitalWrite(lmm,LOW);
}
void tright()
{
  digitalWrite(rmp,HIGH);
  digitalWrite(rmm,HIGH);
  analogWrite(rpf,0);
  analogWrite(rpr,speeds);

  digitalWrite(lmp,HIGH);
  digitalWrite(lmm,HIGH);
  analogWrite(lpf,speeds);
  analogWrite(lpr,0);
}

void tleft()
{
  digitalWrite(rmp,HIGH);
  digitalWrite(rmm,HIGH);
  analogWrite(rpf,speeds);
  analogWrite(rpr,0);

  digitalWrite(lmp,HIGH);
  digitalWrite(lmm,HIGH);
  analogWrite(lpf,0);
  analogWrite(lpr,speeds);
}

int parsePWM(String x){
  int i=2; //1st character is direction, 2nd one is: <
  int val=0;
  while(x[i]!='\0' && x[i]!='>'){
    val*=10;
    int temp = x[i]-48;
    val+=temp;
    i++;
  }
  return val;
}

void driveCar(char Direction){
  if(Direction=='w'){
    forward();
  } else if (Direction=='s'){
    backward();
  } else if (Direction=='a'){
    tleft();
  } else if (Direction=='d'){
    tright();
  } else if (Direction=='q'){
    forward();
  } else if (Direction=='e'){
    breaks();
  }
}
