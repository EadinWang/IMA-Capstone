//Import libraries needed for MQTT
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Adafruit_PWMServoDriver.h>

//credentials to connect ESP32 to your router or wifi connection
// const char* ssid = "ZTE_0762D0";
// const char* password = "1234567890";
// const char* ssid = "ASUS";
// const char* password = "interact";
const char* ssid = "nyu-iot";
const char* password = "12345670";

// MQTT broker credentials
const char* mqtt_server = "f6e52a62054042d18fd5d743fcf6fed7.s2.eu.hivemq.cloud";
const char* mqtt_username = "capstoneA";
const char* mqtt_password = "Capstone123";
const int mqtt_port = 8883;

// Initializes the espClient.
WiFiClientSecure espClient;
PubSubClient client(espClient);


//This certificate is used for TLS authenticating with HiveMQ
static const char* root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

////////////////// servo settings
#include <ESP32Servo.h>
//int set_angle = 0;
//int current_angle = 90;  // setting starting angle to 90 degrees
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

//servo
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 390  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 430  // This is the 'maximum' pulse length count (out of 4096)
#define SERVOPRE 400
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates
int current_angle = SERVOPRE;
// Define servo motor connections (expand as required)
#define SER0 0  //Servo Motor 0 on connector 0
#define SER1 1
#define SER2 2
#define SER3 3
#define SER4 4
#define SER5 5
#define SER6 6
#define SER7 7


// our servo # counter
int servonum = 8;
//const char* servos[] = { "SER0", "SER1", "SER2", "SER3" };
uint servos[8] = { SER0, SER1, SER2, SER3, SER4, SER5, SER6, SER7 };


// #define servoPin 18
#define SERVO_INTERVAL 60  // changing the servo position every 10ms, defines the speed of the servo


////////////////// capacitive sensing settings
int capacitiveValue = 100;
int threshold = 44;  //Threshold to adjust
int touched = 0;


//Variables will store the incoming values from the MQTT broker for every topic
int soil_FromMQTT;
int temperature_FromMQTT;
int humidity_FromMQTT;
int sunlight_FromMQTT;
int sound_FromMQTT;
int xvalue_FromMQTT;
int yvalue_FromMQTT;
int zvalue_FromMQTT;

// Timers auxiliar variables
unsigned long now = millis();
unsigned long lastMeasure = 0;

// This functions connects your ESP32 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  delay(1000);
  WiFi.disconnect();
  delay(1000);
  WiFi.begin(ssid, password);
  delay(1000);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.print("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions reconnects your ESP32 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP32
void reconnect() {
  // Loop until we’re reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection…");  // Attempt to connect

    if (client.connect("ESP32-eadinA", mqtt_username, mqtt_password)) {
      //You need to change the ESP device ID "ESP32-andy" to something unique to you.
      //This helps avoid problems when using multiple ESP32 with the same MQTT connection
      Serial.println("connected");
      // subscribe the topics here
      client.subscribe("soil");
      client.subscribe("temperature");
      client.subscribe("humidity");
      client.subscribe("sunlight");
      client.subscribe("sound");
      client.subscribe("xvalue");
      client.subscribe("yvalue");
      client.subscribe("zvalue");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");  // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


//Setup function
void setup() {
  Serial.begin(9600);
  setup_wifi();
  while (!Serial) delay(1);
  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  ESP32PWM::allocateTimer(4);
  ESP32PWM::allocateTimer(5);
  ESP32PWM::allocateTimer(6);
  ESP32PWM::allocateTimer(7);
  // servo1.setPeriodHertz(50);            // standard 50 hz servo
  // servo1.attach(servoPin, 1000, 2000);  // attaches the servo on pin 18 to the servo object

  //pinMode(A0, INPUT);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;

  pulselength = 1000000;      // 1,000,000 us per second
  pulselength /= SERVO_FREQ;  // Analog servos run at ~60 Hz updates
  Serial.print(pulselength);
  Serial.println(" us per period");
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength);
  Serial.println(" us per bit");
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}


//Main program loop
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  ////////////// servo
  now = millis();

  // every n second
  if (now - lastMeasure > 150) {
    lastMeasure = now;

    ////////////// capacitive
    capacitiveValue = touchRead(4);
    //client.publish("touch", String(capacitiveValue).c_str());
    Serial.println(capacitiveValue);
    if (capacitiveValue < threshold) {  //being touched
      touched = 1;

    } else {
      touched = 0;
    }
    client.publish("touch", String(touched).c_str());
    Serial.println((String) "touch published: " + touched);




    //Serial.println(soil_FromMQTT+temperature_FromMQTT+yvalue_FromMQTT+sunlight_FromMQTT+sound_FromMQTT+xvalue_FromMQTT+humidity_FromMQTT+zvalue_FromMQTT);
    //DEBUGVAL(soil_FromMQTT, temperature_FromMQTT, yvalue_FromMQTT, sunlight_FromMQTT, sound_FromMQTT, xvalue_FromMQTT, humidity_FromMQTT, zvalue_FromMQTT);
    motion(0, soil_FromMQTT);
    Serial.println(soil_FromMQTT);
    motion(1, temperature_FromMQTT);
    Serial.println(temperature_FromMQTT);

    motion(2, yvalue_FromMQTT);
    Serial.println(yvalue_FromMQTT);
    motion(3, sunlight_FromMQTT);
    Serial.println(sunlight_FromMQTT);
    motion(4, sound_FromMQTT);
    Serial.println(sound_FromMQTT);

    motion(5, xvalue_FromMQTT);
    Serial.println(xvalue_FromMQTT);
    motion(6, humidity_FromMQTT);
    Serial.println(humidity_FromMQTT);
    motion(7, zvalue_FromMQTT);
    Serial.println(zvalue_FromMQTT);
  }
}

// void motion(int set_angle) {
//   if (millis() - servo_timestamp > SERVO_INTERVAL) {
//     servo_timestamp += SERVO_INTERVAL;  // increment our timestamp by the servo interval
//     // Measure the new set_angle only, if we really want to move the sensor
//     // int val1 = analogRead(A0);                // Read the potentiometer position
//     // set_angle = map(val1, 0, 1023, 90, 130);  // Map the value to be used with servo

//     // Increment or decrement the current angle according to the set_angle
//     // and don't change it, when we already are at the set_angle
//     if (set_angle > current_angle) {
//       current_angle++;
//     } else if (set_angle < current_angle) {
//       current_angle--;
//     }
//     // Write the new angle to the servo

//     servo1.write(current_angle);
//     // Serial.print("current_angle: ");
//     // Serial.println(current_angle);
//   }
// }

void motion(int i, float set_angle) {

  // if (millis() - servo_timestamp > SERVO_INTERVAL) {
  //   servo_timestamp += SERVO_INTERVAL;  // increment our timestamp by the servo interval

  //   // if (set_angle > current_angle) {
  //   //   current_angle++;
  //   // } else if (set_angle < current_angle) {
  //   //   current_angle--;
  //   // }

  //   if (current_angle = SERVOMAX) {
  //     current_angle -= 10;
  //   } else if (current_angle = SERVOMIN) {
  //     current_angle += 10;
  //   }

  //   current_angle = set_angle;
  //   // Write the new angle to the servo
  //   pwm.setPWM(servos[i], 0, current_angle);
  //   Serial.print(i);
  //   Serial.print(" current_angle: ");
  //   Serial.println(current_angle);
  if (set_angle > current_angle) {
    for (uint16_t pulselen = SERVOPRE; pulselen < SERVOMAX; pulselen++) {
      //for (int i = 0; i < sizeof(servos); i++) {
      pwm.setPWM(servos[i], 0, pulselen);
      delay(100);
      //}
      //i = 0;
    }

  } else {
    for (uint16_t pulselen = SERVOPRE; pulselen > SERVOMIN; pulselen--) {
      //for (int i = 0; i < sizeof(servos); i++) {
      pwm.setPWM(servos[i], 0, pulselen);
      delay(100);
      //}
    }
  }
  current_angle = set_angle;

  Serial.print(i);
  Serial.print(" current_angle: ");
  Serial.println(current_angle);
  delay(800);
}



//Callback function - get messages from MQTT
void callback(char* topic, byte* payload, unsigned int length) {

  if (strcmp(topic, "soil") == 0) {
    //Get the characters of the payload message
    char* getValue_soil;
    getValue_soil = (char*)malloc(length + 1);
    memcpy(getValue_soil, payload, length);
    getValue_soil[length] = '\0';
    //Conversion to String
    String getValueStr_soil = (String)getValue_soil;
    //Conversion to Int
    int getValueInt_soil = getValueStr_soil.toInt();
    Serial.println("Message arrived [" + String(topic) + "]: " + getValueInt_soil);
    //Assign value to a global variable
    soil_FromMQTT = map(getValueInt_soil, 0, 255, SERVOMIN, SERVOMAX);
  }
  if (strcmp(topic, "temperature") == 0) {
    //Get the characters of the payload message
    char* getValue_temperature;
    getValue_temperature = (char*)malloc(length + 1);
    memcpy(getValue_temperature, payload, length);
    getValue_temperature[length] = '\0';
    //Conversion to String
    String getValueStr_temperature = (String)getValue_temperature;
    //Conversion to Int
    int getValueInt_temperature = getValueStr_temperature.toInt();
    Serial.println("Message arrived [" + String(topic) + "]: " + getValueInt_temperature);
    //Assign value to a global variable
    temperature_FromMQTT = map(getValueInt_temperature, 0, 255, SERVOMIN, SERVOMAX);
  }

  if (strcmp(topic, "humidity") == 0) {
    //Get the characters of the payload message
    char* getValue_humidity;
    getValue_humidity = (char*)malloc(length + 1);
    memcpy(getValue_humidity, payload, length);
    getValue_humidity[length] = '\0';
    //Conversion to String
    String getValueStr_humidity = (String)getValue_humidity;
    //Conversion to Int
    int getValueInt_humidity = getValueStr_humidity.toInt();
    Serial.println("Message arrived [" + String(topic) + "]: " + getValueInt_humidity);
    //Assign value to a global variable
    humidity_FromMQTT = map(getValueInt_humidity, 0, 255, SERVOMIN, SERVOMAX);
  }
  if (strcmp(topic, "sunlight") == 0) {
    //Get the characters of the payload message
    char* getValue_sunlight;
    getValue_sunlight = (char*)malloc(length + 1);
    memcpy(getValue_sunlight, payload, length);
    getValue_sunlight[length] = '\0';
    //Conversion to String
    String getValueStr_sunlight = (String)getValue_sunlight;
    //Conversion to int
    int getValueInt_sunlight = getValueStr_sunlight.toInt();
    Serial.println("Message arrived [" + String(topic) + "]: " + getValueInt_sunlight);
    //Assign value to a global variable
    sunlight_FromMQTT = map(getValueInt_sunlight, 0, 255, SERVOMIN, SERVOMAX);
  }
  if (strcmp(topic, "sound") == 0) {
    //Get the characters of the payload message
    char* getValue_sound;
    getValue_sound = (char*)malloc(length + 1);
    memcpy(getValue_sound, payload, length);
    getValue_sound[length] = '\0';
    //Conversion to String
    String getValueStr_sound = (String)getValue_sound;
    //Conversion to int
    int getValueInt_sound = getValueStr_sound.toInt();
    Serial.println("Message arrived [" + String(topic) + "]: " + getValueInt_sound);
    //Assign value to a global variable
    sound_FromMQTT = map(getValueInt_sound, 0, 255, SERVOMIN, SERVOMAX);
  }
  if (strcmp(topic, "xvalue") == 0) {
    //Get the characters of the payload message
    char* getValue_xvalue;
    getValue_xvalue = (char*)malloc(length + 1);
    memcpy(getValue_xvalue, payload, length);
    getValue_xvalue[length] = '\0';
    //Conversion to String
    String getValueStr_xvalue = (String)getValue_xvalue;
    //Conversion to int
    int getValueInt_xvalue = getValueStr_xvalue.toInt();
    Serial.println("Message arrived [" + String(topic) + "]: " + getValueInt_xvalue);
    //Assign value to a global variable
    xvalue_FromMQTT = map(getValueInt_xvalue, 0, 255, SERVOMIN, SERVOMAX);
  }
  if (strcmp(topic, "yvalue") == 0) {
    //Get the characters of the payload message
    char* getValue_yvalue;
    getValue_yvalue = (char*)malloc(length + 1);
    memcpy(getValue_yvalue, payload, length);
    getValue_yvalue[length] = '\0';
    //Conversion to String
    String getValueStr_yvalue = (String)getValue_yvalue;
    //Conversion to int
    int getValueInt_yvalue = getValueStr_yvalue.toInt();
    Serial.println("Message arrived [" + String(topic) + "]: " + getValueInt_yvalue);
    //Assign value to a global variable
    yvalue_FromMQTT = map(getValueInt_yvalue, 0, 255, SERVOMIN, SERVOMAX);
  }
  if (strcmp(topic, "zvalue") == 0) {
    //Get the characters of the payload message
    char* getValue_zvalue;
    getValue_zvalue = (char*)malloc(length + 1);
    memcpy(getValue_zvalue, payload, length);
    getValue_zvalue[length] = '\0';
    //Conversion to String
    String getValueStr_zvalue = (String)getValue_zvalue;
    //Conversion to int
    int getValueInt_zvalue = getValueStr_zvalue.toInt();
    Serial.println("Message arrived [" + String(topic) + "]: " + getValueInt_zvalue);
    //Assign value to a global variable
    zvalue_FromMQTT = map(getValueInt_zvalue, 0, 255, SERVOMIN, SERVOMAX);
  }
}
