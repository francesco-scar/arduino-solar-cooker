bool D_read(int t, int pin, bool expected){
  int start = millis();
  while (millis() <= start + t){
    if (digitalRead(pin) != expected){
      return !expected;
    }
    delay(10);
  }
  return expected;
}

void interrupt_1(){
  if (lock_optical){
    if (digitalRead(optical_1) == digitalRead(optical_2)){
      lock_optical = false;
    }
  } else {
    setting_cooker = true;                               // Depends by sensors disposition
    lock_optical = true;
  }
}

void interrupt_2(){
  if (lock_optical){
    if (digitalRead(optical_1) == digitalRead(optical_2)){
      lock_optical = false;
    }
  } else {
    setting_cooker = false;                               // Depends by sensors disposition
    lock_optical = true;
  }
}
