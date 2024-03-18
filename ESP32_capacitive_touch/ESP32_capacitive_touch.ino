int capacitiveValue = 100;
int threshold = 24; //Threshold to adjust

void setup() {
    Serial.begin(9600);
    delay(1000); // Delay to launch the serial monitor
    Serial.println("ESP32 Touch Demo");
}

void loop() {

    capacitiveValue = touchRead(4);
    Serial.println(capacitiveValue);
    if(capacitiveValue < threshold ){
        Serial.println("Wire touched");
        }
    delay(500);
}