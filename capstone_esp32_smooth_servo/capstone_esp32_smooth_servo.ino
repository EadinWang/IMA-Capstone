
// servo settings

#include <ESP32Servo.h>
Servo servo1;
//int set_angle = 0;
int current_angle = 90;  // setting starting angle to 90 degrees
unsigned long servo_timestamp = 0;


// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
// Possible PWM GPIO pins on the ESP32-S3: 0(used by on-board button),1-21,35-45,47,48(used by on-board LED)
// Possible PWM GPIO pins on the ESP32-C3: 0(used by on-board button),1-7,8(used by on-board LED),9-10,18-21

// #if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
// int servoPin = 17;
// #elif defined(CONFIG_IDF_TARGET_ESP32C3)
// int servoPin = 7;
// #else
#define servoPin 18
// #endif
#define SERVO_INTERVAL 10  // changing the servo position every 10ms, defines the speed of the servo


// Timers auxiliar variables
unsigned long now = millis();
unsigned long lastMeasure = 0;


//Setup function
void setup() {
  Serial.begin(9600);
  
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo1.setPeriodHertz(50);            // standard 50 hz servo
  servo1.attach(servoPin, 1000, 2000);  // attaches the servo on pin 18 to the servo object

  pinMode(35, INPUT);
}

//Main program loop
void loop() {
  
  now = millis();
  // every n second
  if (now - lastMeasure > 100) {
    lastMeasure = now;

    //Serial.println(varFromMQTT);

    //int val1 = analogRead(A0);                // Read the potentiometer position
    //float angle_moisture = map(varFromMQTT, 1000, 2800, 90, 130);
    int val1 = analogRead(35);                // Read the potentiometer position

    motion(map(val1, 0, 1023, 90, 130));

    // if (varFromMQTT < 0) {
    // } else {
    //   float angle = map(varFromMQTT, 0, 15, 50, 255);
    //   led_red(5, lighting_g);
    // }

    delay(1);
  }
}


void motion(int set_angle) {
  if (millis() - servo_timestamp > SERVO_INTERVAL) {
    servo_timestamp += SERVO_INTERVAL;  // increment our timestamp by the servo interval
    // Measure the new set_angle only, if we really want to move the sensor
    

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