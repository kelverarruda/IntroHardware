#include <SPI.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define DHTPIN D1

DHT dht;
WiFiClient nodeMCU;
WiFiUDP ntpUDP;
NTPClient ntpTime(ntpUDP, "a.ntp.br");

PubSubClient client(nodeMCU);

/*          WIFI SETTINGS           */
const char* ssid = "MotoOneAction";
const char* password = "expresso";

/*          MQTT SETTINGS            */
const char* mqttServer = "mqtt.eclipseprojects.io";
const int   mqttPort = 1883;
const char* mqttClientId = "NodeMCU-ESP8266-RKLab";
const char* mqttUser = "";
const char* mqttPassword = "";
const char* topicTemp = "rklab/temperature";
const char* topicHumid = "rklab/humidity";
const char* topicTempColor = "rklab/temperature-color";
const char* topicTempHigh = "rklab/temperature-high";
const char* topicTempLow = "rklab/temperature-low";
const char* topicClock = "rklab/clock";
const char* topicUptime = "rklab/uptime";

/*          SETTINGS            */
int tempHigh = 32;
int tempLow = 18;
const char* tempHighColor = "[217, 21, 17]";
const char* tempLowhColor = "[37, 176, 248]";
const char* tempNormalhColor = "[33, 217, 128]";