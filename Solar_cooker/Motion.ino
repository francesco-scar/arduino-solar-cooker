void o_motion(unsigned long timeout){
  if (analogRead(r_sensor) < min_brightness){
    digitalWrite(o_motor, !HIGH);
    start = millis();
    while (analogRead(r_sensor) < min_brightness && millis()<=start+timeout && analogRead(o_sensor)>tollerance*analogRead(r_sensor)){           // Check inequation sign!
      delay(50);
    }
    digitalWrite(o_motor, !LOW);
    
    if (millis()>start+timeout){
      while (true){
        tone(buzzer, 5000, 500);
        delay(1000);
      }
    }
  }
}




void v_motion(bool calante, bool ignore, unsigned long timeout){
  if(analogRead(r_sensor) < min_brightness){
    set_direction(calante);

    start = millis();
    
    while (analogRead(r_sensor) < min_brightness && millis()<=start+timeout && (digitalRead(limit_switch) || ignore) && (digitalRead(limit_switch_v_a) || setting_sun) && analogRead(v_sensor)>tollerance*analogRead(r_sensor)){           // Check inequation sign!
      if (setting_cooker != calante){
        set_direction(calante);
      }
      delay(50);
    }
    digitalWrite(v_motor, !LOW);

    if (millis()>start+timeout){
      while (true){
        tone(buzzer, 5000, 500);
        delay(5000);
      }
    }
  }
}



void set_direction(bool calante){
  setting_cooker = !calante;
  while (setting_cooker != calante){
    digitalWrite(v_motor, !LOW);
    delay(1010+random(-500, 500));                                              // Wait pseudorandom time interval with the hope that next time the motor will turn the right way
    digitalWrite(v_motor, !HIGH);
    delay(3000);                                                                // Wait to let the rotator to trigger interrupts blocking IR light beam
  }
}
