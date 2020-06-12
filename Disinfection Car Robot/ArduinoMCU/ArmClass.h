class Arm
{
  public:
  Servo s;
   Arm(Servo servo){
   s=servo;
  }
  int moveRight(int i){
    s.write(i);
    i--;
    if(i<5)
      i=5;
    return i;
  }
  int moveLeft(int i){
    s.write(i);
    i++;
    if(i>175)
      i=175;
    return i;
  }
  void reset(int val)
  {
    s.write(val);
  }
};
