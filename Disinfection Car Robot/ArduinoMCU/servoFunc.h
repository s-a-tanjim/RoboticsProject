void resetAll(){
  a1.reset(90);
  a2.reset(90);
  a3.reset(90);
  
}

void ControlArm()
{
  while(1)
  {
    dataA=Serial.read();
    Serial.print(" ");
    Serial.println(data);
    if(dataA=='R')//Servo-1
    {
       i1=a1.moveRight(i1);
       info(i1);
     } 
     else if(dataA=='L')
     {
        i1=a1.moveLeft(i1);
        info(i1);
      }
      else if(dataA=='F')//Servo-2
      {
        i2=a2.moveRight(i2);
        info(i2);
      }
      else if(dataA=='B')
      {
        i2=a2.moveLeft(i2);
        info(i2);
      }
      else if(dataA=='I')//Servo-3
      {
       i3=a3.moveRight(i3);
       info(i3);
      }
      else if(dataA=='G')
      {
        i3=a3.moveLeft(i3);
        info(i3);
      }
       //Servo-4
//       else if(dataA=='0' || dataA=='1' || dataA=='2' || dataA=='3' || dataA=='4' || dataA=='5' || dataA=='6' || dataA=='7' || dataA=='8' || dataA=='9')
//       {
//       endF(dataA);
//       }
        else if(dataA=='J')
        {
        i4=a4.moveRight(i4);
        if(i4<95)
          i4=95;
        info(i4);
        }
        else if(dataA=='H')
        {
        i4=a4.moveLeft(i4);
        info(i4);
        if(i4>145)
          i4=145;
        }
       else if(dataA=='w')
       {
         break;
       }
   }
}
