#include "./secrets.h"
#include "./led.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
 
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
  
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

bool auroraLoop;
 
void connectAWS()
{

  // Connect to WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
 
  // Sert certificates 
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}
 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.println("new message");
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload, length);


  // handle message content
  if (doc.containsKey("red") && doc.containsKey("green") && doc.containsKey("blue")) {
    // hack for loop modes
    auroraLoop = false;

    // parse rgb from message
    int red = doc["red"];
    int green = doc["green"];
    int blue = doc["blue"];
    setAllLEDs(red, green, blue);
  } else if (doc.containsKey("mode")) {
    const char* mode = doc["mode"];
    
    if (strcmp(mode, "aurora") == 0) {
      auroraLoop = true;
      static uint8_t index = 0;

      // hack to run loop in single thread 
      while (auroraLoop) {
        northernLights(index);
        client.loop();
        index = index + 1;
      }
    }

    if (strcmp(mode, "aurora-v2") == 0) {
      auroraLoop = true;
      static uint8_t index = 0;

      while (auroraLoop) {
        northernLightsV2(index);
        client.loop();
        index = index + 1;
      }
    }
  } else {
    Serial.println("Received unknown message");
  }
}
 
void setup()
{
  Serial.begin(115200);
  connectAWS();
  setupLED();
}
 
void loop()
{
  client.loop();
  delay(1000);
}