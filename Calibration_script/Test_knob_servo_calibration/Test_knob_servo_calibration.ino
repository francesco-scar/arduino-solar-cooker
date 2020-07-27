#include <Servo.h>

Servo myservo;  // create servo object to control a servo

#define MIDDLE_POSITION 80
#define VERTICAL_MOTOR_POSITION 50
#define HORIZONTAL_MOTOR_POSITIOIN 110

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  delay(5000);
}

void loop() {
  
  myservo.write(MIDDLE_POSITION);
  delay(1000);
  myservo.write(VERTICAL_MOTOR_POSITION);
  delay(1000);
  myservo.write(MIDDLE_POSITION);
  delay(1000);
  myservo.write(HORIZONTAL_MOTOR_POSITIOIN);
  delay(1000);
}
