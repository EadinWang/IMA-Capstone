//Import libraries needed for MQTT
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

//credentials to connect ESP32 to your router or wifi connection
const char* ssid = "ASUS";
const char* password = "interact";


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
#define SERVO_INTERVAL 60  // changing the servo position every 10ms, defines the speed of the servo


////////////////// capacitive sensing settings
int capacitiveValue = 100;
int threshold = 24;  //Threshold to adjust
int touched = 0;


//Variables will store the incoming values from the MQTT broker for every topic
int varFromMQTT = 90;

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
      // client.subscribe("RED");

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
  servo1.setPeriodHertz(50);            // standard 50 hz servo
  servo1.attach(servoPin, 1000, 2000);  // attaches the servo on pin 18 to the servo object

  //pinMode(A0, INPUT);
}

//Main program loop
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  ////////////// servo
  now = millis();
  // every n second
  if (now - lastMeasure > 100) {
    lastMeasure = now;
    //Serial.print("varFromMQTT: ");
    //Serial.println(varFromMQTT);

  
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

    delay(1);
  }
  //int val1 = analogRead(A0);                // Read the potentiometer position
    //float angle_moisture = map(varFromMQTT, 1000, 2800, 0, 130);
    float angle_moisture = varFromMQTT;
    motion(angle_moisture);
}


void motion(int set_angle) {
  if (millis() - servo_timestamp > SERVO_INTERVAL) {
    servo_timestamp += SERVO_INTERVAL;  // increment our timestamp by the servo interval
    // Measure the new set_angle only, if we really want to move the sensor
    // int val1 = analogRead(A0);                // Read the potentiometer position
    // set_angle = map(val1, 0, 1023, 90, 130);  // Map the value to be used with servo

    // Increment or decrement the current angle according to the set_angle
    // and don't change it, when we already are at the set_angle
    if (set_angle > current_angle) {
      current_angle++;
    } else if (set_angle < current_angle) {
      current_angle--;
    }
    // Write the new angle to the servo

    servo1.write(current_angle);
    // Serial.print("current_angle: ");
    // Serial.println(current_angle);
  }
}

//Callback function - get messages from MQTT
void callback(char* topic, byte* payload, unsigned int length) {

  if (strcmp(topic, "soil") == 0) {
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
    varFromMQTT = getValueInt;
  }
}
