#include <CapacitiveSensor.h>

// capacitive sensing constant
CapacitiveSensor sensor = CapacitiveSensor(4, 2);  // 1M resistor between pins 4 & 2, pin 2 is sensor pin


float SMOOTHING = 0.5;
float smoothed;


void setup() {
  Serial.begin(9600);
}

void loop() {
  long measurement = sensor.capacitiveSensor(30);

  Serial.println(measurement);

  smoothed = smoothed * (1.0 - SMOOTHING) + measurement * SMOOTHING;
  Serial.println(smoothed);
  delay(50);
}


