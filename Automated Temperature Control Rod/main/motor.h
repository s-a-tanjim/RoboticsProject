
//Down
void forward()
{ 
  digitalWrite(motor_en_pin_0,HIGH);
  digitalWrite(motor_en_pin_1,HIGH);
  analogWrite(motor_p_pin,speeed);
  analogWrite(motor_n_pin,0);
}

//Up
void backward()
{
  digitalWrite(motor_en_pin_0,HIGH);
  digitalWrite(motor_en_pin_1,HIGH);
  analogWrite(motor_p_pin,0);
  analogWrite(motor_n_pin,speeed);
}

void breaks()
{
  digitalWrite(motor_en_pin_0,LOW);
  digitalWrite(motor_en_pin_1,LOW);
}

void rod_up(int mul){
  backward();
  delay(mul*STEP_TIME);
  breaks();
}

void rod_down(int mul){
  forward();
  delay(mul*STEP_TIME);
  breaks();
}

void control_rod(int prev_step, int new_step){
  if(prev_step==new_step) {
    // No operation
  } else if(prev_step>new_step){
    rod_up(prev_step-new_step);
    stepp = new_step;
  } else {
    rod_down(new_step-prev_step);
    stepp = new_step;
  }
}
