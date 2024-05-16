/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-sound-SOUND
 */

const int SOUND_PIN = A4; // ESP32 pin GPIO18 connected to the OUT pin of the sound SOUND

//int lastState = HIGH;  // the previous state from the input pin
//int currentState;      // the current reading from the input pin
int soundvar;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the ESP32's pin as an input
  pinMode(SOUND_PIN, INPUT);
}

void loop() {
  // read the state of the the ESP32's input pin
  
  //currentState = digitalRead(SOUND_PIN);
  soundvar = analogRead(SOUND_PIN);
  Serial.println(soundvar);

  // if (lastState == HIGH && currentState == LOW){
  //   Serial.println("The sound has been detected");
  //   Serial.println(soundvar);
  // }
  // else if (lastState == LOW && currentState == HIGH){
    
  //   Serial.println("The sound has disappeared");
  //   Serial.println(soundvar);
  // }

  // save the the last state
  //lastState = currentState;
  delay(100);
  
}
