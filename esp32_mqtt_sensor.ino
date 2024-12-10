#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

// MQTT broker details
const char* mqtt_server = "your-broker-ip";
const int mqtt_port = 1883;
const char* mqtt_user = "admin";
const char* mqtt_password = "mosquitto123";

// Topics
const char* topic = "agri/soil";

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read sensor data
  float sensorValue = readSensor(); // Implement this function to read from your sensor

  // Publish sensor data
  char msg[50];
  snprintf(msg, 50, "Sensor value: %f", sensorValue);
  client.publish(topic, msg);

  delay(2000); // Adjust the delay as needed
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

float readSensor() {
  // Implement your sensor reading logic here
  return 0.0; // Replace with actual sensor reading
}
