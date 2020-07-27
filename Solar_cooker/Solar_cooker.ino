#include <EEPROM.h>

#define DEBUG 1

#define address 0

#define o_sensor A0
#define v_sensor A1
#define r_sensor A2
#define optical_1 2
#define optical_2 3

#define limit_switch_v_b 5
#define limit_switch_v_a 1

#define button 7
#define buzzer 6

#define o_motor 8
#define v_motor 9

#define tollerance 1.4 // 1.4                                                            // Accetable difference between sensors

#define min_brightness 130 //130                                                        // Reference value in cloudy situation

#define V_TIMEOUT_SETUP 1800000                                                   // Timeout vertical alignment in setup [ms]
#define O_TIMEOUT_SETUP 60000                                                     // Timeout horizontal alignment in setup [ms]
#define V_TIMEOUT 1200000                                                         // Timeout vertical alignment in loop [ms]
#define O_TIMEOUT 30000                                                           // Timeout horizontal alignment in loop [ms]

#define DELAY 30                                                                  // Delay between consecutive readings [sec]

bool setting_sun = false;
volatile bool setting_cooker = false;
volatile bool lock_optical = true;

unsigned long start = 0;
unsigned int i = 0;
unsigned int j = 0;


void setup() { 
  pinMode(o_sensor, INPUT);
  pinMode(v_sensor, INPUT);
  pinMode(r_sensor, INPUT);
  pinMode(optical_1, INPUT_PULLUP);
  pinMode(optical_2, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(limit_switch_v_b, INPUT_PULLUP);
  pinMode(limit_switch_v_a, INPUT_PULLUP);
  pinMode(o_motor, OUTPUT);
  pinMode(v_motor, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(o_motor, !LOW);
  digitalWrite(v_motor, !LOW);

  attachInterrupt(digitalPinToInterrupt(optical_1), interrupt_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(optical_2), interrupt_2, CHANGE);

  for (i=0; digitalRead(button) && i<600; i++){
    delay(100);
  }
  
  randomSeed(millis()+analogRead(o_sensor)+analogRead(v_sensor)+analogRead(r_sensor));
  
  if (D_read(200, button, LOW) == LOW){
    if (!DEBUG){
      for (j=0; j<4; j++){
        for (i=100; i<800; i+=5){
          tone(buzzer, i, 15);
          delay(10);
        }
        for (i=800; i>100; i-=5){
          tone(buzzer, i, 15);
          delay(10);
        }
      }
    }
    o_motion(O_TIMEOUT_SETUP);
  
    v_motion(true, false, V_TIMEOUT_SETUP);
    
    if (digitalRead(limit_switch_v_b) == LOW){
      v_motion(false, true, V_TIMEOUT_SETUP);
      
      if (digitalRead(limit_switch_v_a) == LOW){
        while (true){
          tone(buzzer, 5000, 1000);
          delay(1100);
        }
      }
    }

    EEPROM.update(address, 0);
  } else {
    setting_sun = EEPROM.read(address);
  }
}




void loop() {
  if (analogRead(o_sensor)>tollerance*analogRead(r_sensor)){
    o_motion(O_TIMEOUT);
  }


  if (analogRead(v_sensor)>tollerance*analogRead(r_sensor)){
    v_motion(setting_sun, false, V_TIMEOUT);
    
    if (digitalRead(limit_switch_v_a) == LOW){
      setting_sun = true;
      EEPROM.update(address, 1);
    } else if (digitalRead(limit_switch_v_b) == LOW){
      while (true){
          tone(buzzer, 5000, 2000);
          delay(5000);
        }
    }
  }
  
  for (i=0; i<DELAY; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}
