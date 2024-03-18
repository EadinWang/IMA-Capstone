#include <Servo.h>

Servo servo1;
int set_angle = 0;
int current_angle = 90;  // setting starting angle to 90 degrees
unsigned long servo_timestamp = 0;
#define SERVO_INTERVAL 80  // changing the servo position every 10ms, defines the speed of the servo

void setup() {
  Serial.begin(9600);
  servo1.attach(9);
  pinMode(A0, INPUT);  // Connect potentiometer or Joystick x or y pin to A0 input
}

void loop() {
  if (millis() - servo_timestamp > SERVO_INTERVAL) {
    servo_timestamp += SERVO_INTERVAL;  // increment our timestamp by the servo interval
    // Measure the new set_angle only, if we really want to move the sensor
    int val1 = analogRead(A0);                // Read the potentiometer position
    set_angle = map(val1, 0, 1023, 90, 130);  // Map the value to be used with servo

    // Increment or decrement the current angle according to the set_angle
    // and don't change it, when we already are at the set_angle
    if (set_angle > current_angle) {
      current_angle++;
    } else if (set_angle < current_angle) {
      current_angle--;
    }
    // Write the new angle to the servo
    servo1.write(current_angle);
    Serial.println(current_angle);
  }
}