#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int val = 90;
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    char c = Serial.read();
    if (c == '+'){
      val++;
      Serial.println(val);
    } else if (c == '-') {
      val--;
      Serial.println(val);
    }
  }
  
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
