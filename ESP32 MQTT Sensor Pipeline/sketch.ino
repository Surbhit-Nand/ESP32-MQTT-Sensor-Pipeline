#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22

const char* ssid = "Wokwi-GUEST";   // Wokwi's built-in simulated Wi-Fi
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";
const char* topic = "usp-surbhit-iot/dht22";

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void connectWifi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void connectMqtt() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    String clientId = "esp32-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println(" connected");
    } else {
      Serial.print(" failed, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  connectWifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) connectMqtt();
  client.loop();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Sensor read failed");
  } else {
    char payload[64];
    snprintf(payload, sizeof(payload), "{\"temp\":%.2f,\"hum\":%.2f}", temp, hum);
    client.publish(topic, payload);
    Serial.print("Published: ");
    Serial.println(payload);
  }
  delay(2000);
}