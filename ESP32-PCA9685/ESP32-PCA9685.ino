/*
  ESP32 PCA9685 Servo Control
  esp32-pca9685.ino
  Driving multiple servo motors with ESP32 and PCA9685 PWM module
  Use I2C Bus

  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/

// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit PCA9685 Servo Library
#include <Adafruit_PWMServoDriver.h>
#include <ESP32Servo.h>
// Creat object to represent PCA9685 at default I2C address
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

// Define maximum and minimum number of "ticks" for the servo motors
// Range from 0 to 4095
// This determines the pulse width

#define SERVOMIN 0   // Minimum value
#define SERVOMAX 360  // Maximum value
#define POSMAX 30  // Maximum value

// Define servo motor connections (expand as required)
#define SER0 0  //Servo Motor 0 on connector 0
#define SER1 1
#define SER2 2
#define SER3 3
#define SER4 4
#define SER5 5
#define SER6 6
#define SER7 7

//const char* servos[] = { "SER0", "SER1", "SER2", "SER3" };
uint servos[8] = { SER0, SER1, SER2, SER3, SER4, SER5, SER6, SER7 };

// Variables for Servo Motor positions (expand as required)
int pwm0;
// int pwm1;
// int pwm2;
// int pwm3;

void setup() {

  // Serial monitor setup
  Serial.begin(115200);

  // Print to monitor
  Serial.println("PCA9685 Servo Test");

  // Initialize PCA9685
  pca9685.begin();

  // Set PWM Frequency to 50Hz
  pca9685.setPWMFreq(50);

  for (int i = 0; i < sizeof(servos); i++) {
      // Determine PWM pulse width
      //pwm = map(posDegrees, 0, 180, SERVOMIN, SERVOMAX);
      // Write to PCA9685
      pca9685.setPWM(servos[i], 0, 0);
    }
}

void loop() {
  rotate(pwm0);
}

void rotate(int pwm) {
  // Move Motor 0 from 0 to 180 degrees
  for (int posDegrees = 0; posDegrees <= POSMAX; posDegrees+=1) {
    for (int i = 0; i < sizeof(servos); i++) {
      // Determine PWM pulse width
      pwm = map(posDegrees, 0, 180, SERVOMIN, SERVOMAX);
      // Write to PCA9685
      pca9685.setPWM(servos[i], 0, pwm);
      // Print to serial monitor
      Serial.print("Motor 0 = ");
      Serial.println(pwm);
      delay(3);
    }
  }
  // Move Motor 0 from 180 to 0 degrees
  for (int posDegrees = POSMAX; posDegrees >= 0; posDegrees-=1) {
    for (int i = 0; i < sizeof(servos); i++) {
      // Determine PWM pulse width
      pwm = map(posDegrees, 0, 180, SERVOMIN, SERVOMAX);
      // Write to PCA9685
      pca9685.setPWM(servos[i], 0, pwm);
      // Print to serial monitor
      Serial.print("Motor 0 = ");
      Serial.println(pwm);
      delay(3);
    }
  }
}