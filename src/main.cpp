
#include "./Config.h"

void verificaStatusWifi()
{
	while (WiFi.status() != WL_CONNECTED)
	{
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}
	digitalWrite(LED_BUILTIN, LOW);
}

void lerSensorDHT11()
{
	float temp = dht.getTemperature();
	float humid = dht.getHumidity();

	if (isnan(temp) || isnan(humid))
	{
		Serial.println("Failed to read from DHT sensor!");
		return;
	}

	if (temp >= tempHigh)
	{
		client.publish(topicTempColor, tempHighColor, true);
		client.publish(topicTempHigh, String(temp).c_str(), true);
	}
	else if (temp <= tempLow)
	{
		client.publish(topicTempColor, tempLowhColor, true);
		client.publish(topicTempLow, String(temp).c_str(), true);
	}
	else
	{
		client.publish(topicTempColor, tempNormalhColor, true);
	}

	ntpTime.update();
	String formattedTime = ntpTime.getFormattedTime();
	Serial.print(formattedTime + " -> ");
	Serial.print("Temperature: ");
	Serial.print(temp);
	Serial.print(" | ");
	Serial.print("Humidity: ");
	Serial.println(humid);

	client.publish(topicTemp, String(temp).c_str(), true);
	client.publish(topicHumid, String(humid).c_str(), true);
	client.publish(topicClock, String(formattedTime).c_str(), true);
	client.publish(topicUptime, String((millis() / 1000) / 60).c_str(), true);
}

void setup()
{
	Serial.begin(9600);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

	dht.setup(DHTPIN);

	WiFi.begin(ssid, password);
	verificaStatusWifi();
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	client.setServer(mqttServer, mqttPort);

	ntpTime.setTimeOffset(-3 * 3600);
	ntpTime.begin();
}

void loop()
{
	verificaStatusWifi();
	while (!client.connected())
	{
		client.connect(mqttClientId);
		delay(500);
		Serial.println("Initializing MQTT client...");
	}
	lerSensorDHT11();
	delay(10000);
}