#include "Servo.h"

// Create a new servo object:
Servo myservo;

// Define the servo pin:
#define servoPin 9

void setup() {
  // Attach the Servo variable to a pin:
  myservo.attach(servoPin);
}

void loop() {
  // Tell the servo to go to a particular angle:
  myservo.write(30);
  delay(50);

  // Sweep from 0 to 180 degrees:
  for (int angle = 30; angle <= 60; angle += 1) {
    myservo.write(angle);
    delay(80);
  }

  // And back from 180 to 0 degrees:
  for (int angle = 60; angle >= 30; angle -= 1) {
    myservo.write(angle);
    delay(80);
  }
  delay(50);
}