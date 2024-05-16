//Import libraries needed for MQTT
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// buzzer
//#include "pitches.h"

//const int BUZZZER_PIN = 23; // GIOP18 pin connected to piezo buzzer
// int BUZZER_PIN = 13;
// int BUZZER_CHANNEL = 0;

//credentials to connect ESP32 to your router or wifi connection
// const char* ssid = "ZTE_0762D0";
// const char* password = "1234567890";
const char* ssid = "nyu-iot";
const char* password = "12345670";
// const char* ssid = "ASUS";
// const char* password = "interact";

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

// intialize variables for sensor and actuators
#define SOIL_PIN 35
#include "DHT.h"
#define DHTPIN 17      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22  // DHT 22
DHT dht(DHTPIN, DHTTYPE);

#define UV_PIN 4

const int SOUND_PIN = A4;

const int xpin = A0;  // x-axis of the accelerometer
const int ypin = A1;  // y-axis
const int zpin = A2;  // z-axis (only on 3-axis models)

//define variables
int moistureValue;
float humidity;
float temperature;
float sunlight;
int soundvar;
int lastState = HIGH;  // the previous state from the input pin
int currentState;      // the current reading from the input pin
int xvalue;
int yvalue;
int zvalue;

//DFPlayer
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))  // Using a soft serial port
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/14, /*tx =*/13);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif

DFRobotDFPlayerMini myDFPlayer;
//void printDetail(uint8_t type, int value);

// Timers auxiliar variables
unsigned long now = millis();
unsigned long lastMeasure = 0;

//servo angles
float angle_max = 120;
float angle_min = 30;

int moisture_publish;
int sunlight_publish;

//Variables will store the incoming values from the MQTT broker for every topic
int touchFromMQTT = 0;


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
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");  // Attempt to connect

    if (client.connect("ESP32-eadin", mqtt_username, mqtt_password)) {
      //You need to change the ESP device ID "ESP32-andy" to something unique to you.
      //This helps avoid problems when using multiple ESP32 with the same MQTT connection
      Serial.println("connected");
      // subscribe the topics here
      client.subscribe("touch");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
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

  //ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  //settings for the DHT22
  dht.begin();

//mp3
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/D7, /*tx =*/D6);
#else
  FPSerial.begin(9600);
#endif
  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));


  //xyz
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  //sound
  pinMode(SOUND_PIN, INPUT);
}

//Main program loop
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  now = millis();

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  sunlight = analogRead(UV_PIN);
  moistureValue = analogRead(SOIL_PIN);  // Read analog value from the sensor
  //sound
  soundvar = analogRead(SOUND_PIN);

  //xyz
  xvalue = analogRead(xpin);
  yvalue = analogRead(ypin);
  zvalue = analogRead(zpin);


  // Publishes topics every n second§
  if (now - lastMeasure > 500) {
    lastMeasure = now;

    // if (moistureValue >= 2700) {
    //   moisture_publish = angle_max;
    // } else if (moistureValue <= 1000) {
    //   moisture_publish = angle_min;
    // } else {
    //   moisture_publish = map(moistureValue, 1000, 2700, angle_min, angle_max);
    // }


    //Serial.print("Moisture Value: ");
    //Serial.println(moistureValue);  // Print the moisture value

    // Publishes values to a topic of your choice.
    //1
    int moisture_publish = map(moistureValue, 100, 700, 0, 255);
    client.publish("soil", String(moisture_publish).c_str());
    Serial.println((String) "soil published:" + moisture_publish);
    //2
    int temperature_publish = map(temperature, 20, 30, 0, 255);
    client.publish("temperature", String(temperature_publish).c_str());
    Serial.println((String) "temperature published:" + temperature);
    //3
    int humidity_publish = map(humidity, 30, 60, 0, 255);
    client.publish("humidity", String(humidity_publish).c_str());
    Serial.println((String) "humidity published:" + humidity);
    //
    int sunlight_publish = map(sunlight, 0, 900, 0, 255);
    client.publish("sunlight", String(sunlight_publish).c_str());
    Serial.println((String) "sunlight published:" + sunlight);
    //
    int sound_publish = map(soundvar, 50, 1000, 0, 255);
    client.publish("sound", String(sound_publish).c_str());
    //Serial.println(soundvar);
    Serial.println((String) "sound published:" + soundvar);
    //
    int xvalue_publish = map(xvalue, 1000, 2000, 0, 255);
    client.publish("xvalue", String(xvalue_publish).c_str());
    Serial.println((String) "xvalue published:" + xvalue);
    //
    int yvalue_publish = map(yvalue, 1000, 2000, 0, 255);
    client.publish("yvalue", String(yvalue_publish).c_str());
    Serial.println((String) "yvalue published:" + yvalue);
    //
    int zvalue_publish = map(zvalue, 1000, 2000, 0, 255);
    client.publish("zvalue", String(zvalue_publish).c_str());
    Serial.println((String) "zvalue published:" + zvalue);
  }

  //mp3
  if (touchFromMQTT == 1) {

    if (!myDFPlayer.begin(FPSerial, /*isACK = */ true, /*doReset = */ true)) {  //Use serial to communicate with mp3.
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
      while (true) {
        delay(0);  // Code to compatible with ESP8266 watch dog.
      }
    }
    Serial.println(F("DFPlayer Mini online."));
    //ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_E, 8);
    myDFPlayer.volume(10);  //Set volume value. From 0 to 30
    myDFPlayer.play(1);     //Play the first mp3
    delay(9000);
  // } else {
  //   //ledcWrite(0, 0);
  //   myDFPlayer.disableLoopAll();
  }
}

// This function is executed when some device publishes a message to a topic that your ESP32 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that
// your ESP32 is subscribed you can actually do something
void callback(char* topic, byte* payload, unsigned int length) {

  if (strcmp(topic, "touch") == 0) {
    //Get the characters of the payload message
    char* getValue;
    getValue = (char*)malloc(length + 1);
    memcpy(getValue, payload, length);
    getValue[length] = '\0';

    //Conversion to String
    String getValueStr = (String)getValue;

    //Conversion to Int
    int getValueInt = getValueStr.toInt();
    Serial.println("Message arrived [" + String(topic) + "]: " + getValueInt);

    //Assign value to a global variable
    touchFromMQTT = getValueInt;
  }
}

// void printDetail(uint8_t type, int value) {
//   switch (type) {
//     case TimeOut:
//       Serial.println(F("Time Out!"));
//       break;
//     case WrongStack:
//       Serial.println(F("Stack Wrong!"));
//       break;
//     case DFPlayerCardInserted:
//       Serial.println(F("Card Inserted!"));
//       break;
//     case DFPlayerCardRemoved:
//       Serial.println(F("Card Removed!"));
//       break;
//     case DFPlayerCardOnline:
//       Serial.println(F("Card Online!"));
//       break;
//     case DFPlayerUSBInserted:
//       Serial.println("USB Inserted!");
//       break;
//     case DFPlayerUSBRemoved:
//       Serial.println("USB Removed!");
//       break;
//     case DFPlayerPlayFinished:
//       Serial.print(F("Number:"));
//       Serial.print(value);
//       Serial.println(F(" Play Finished!"));
//       break;
//     case DFPlayerError:
//       Serial.print(F("DFPlayerError:"));
//       switch (value) {
//         case Busy:
//           Serial.println(F("Card not found"));
//           break;
//         case Sleeping:
//           Serial.println(F("Sleeping"));
//           break;
//         case SerialWrongStack:
//           Serial.println(F("Get Wrong Stack"));
//           break;
//         case CheckSumNotMatch:
//           Serial.println(F("Check Sum Not Match"));
//           break;
//         case FileIndexOut:
//           Serial.println(F("File Index Out of Bound"));
//           break;
//         case FileMismatch:
//           Serial.println(F("Cannot Find File"));
//           break;
//         case Advertise:
//           Serial.println(F("In Advertise"));
//           break;
//         default:
//           break;
//       }
//       break;
//     default:
//       break;
//   }
// }