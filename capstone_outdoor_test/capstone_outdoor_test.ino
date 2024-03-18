//Import libraries needed for MQTT
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// buzzer
#include "pitches.h"
//const int BUZZZER_PIN = 23; // GIOP18 pin connected to piezo buzzer
int BUZZER_PIN = 13;
int BUZZER_CHANNEL = 0;

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

// intialize variables for sensor and actuators
#define SOIL_PIN 35
// #include "DHT.h"
// #define DHTPIN 17      // Digital pin connected to the DHT sensor
// #define DHTTYPE DHT22  // DHT 22
// DHT dht(DHTPIN, DHTTYPE);


// Timers auxiliar variables
unsigned long now = millis();
unsigned long lastMeasure = 0;

//servo angles
float angle_max = 120;
float angle_min = 30;

float moisture_publish;

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

  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  //settings for the DHT22
  //dht.begin();
}

//Main program loop
void loop() {
  if (!client.connected()) reconnect();
  client.loop();


  now = millis();
  // Publishes topics every n second
  if (now - lastMeasure > 100) {
    lastMeasure = now;

    // float humidity = dht.readHumidity();
    // float temperature = dht.readTemperature();

    int moistureValue = analogRead(SOIL_PIN);  // Read analog value from the sensor
    if (moistureValue >= 2700) {
      moisture_publish = angle_max;
    } else if (moistureValue <= 1000) {
      moisture_publish = angle_min;
    } else {
      moisture_publish = map(moistureValue, 1000, 2700, angle_min, angle_max);
    }
    //Serial.print("Moisture Value: ");
    //Serial.println(moistureValue);  // Print the moisture value

    // Publishes values to a topic of your choice.
    client.publish("soil", String(moisture_publish).c_str());
    Serial.println((String) "soil published:" + moisture_publish);
    
    if (touchFromMQTT == 1) {
      ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_E, 8);
      delay(800);
    } else {
      ledcWrite(0, 0);
    }
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