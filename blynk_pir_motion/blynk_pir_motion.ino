#include <ESP8266WiFi.h>
char ssid[] = "FED";
char pass[] = "eunaosei";
// char ssid[] = "IC-ALUNOS";
// char pass[] = "icomputacaoufal";

#include <BlynkSimpleEsp8266.h>
char auth[] = "756e1a5712854954b23fd086ee6d83e4";

BlynkTimer timer;

#include <dht11.h>
#define DHT11_PIN D1
dht11 DHT;

#define sensorPin D2
#define buzzerPin D3

void sendMotion()
{
	int state;
	state = digitalRead(sensorPin);

	// Send it to the server
	if (state == 1) {
		Blynk.virtualWrite(V1, "1023");
		// digitalWrite(buzzerPin, HIGH);
		Blynk.notify("LC Home > Motion detected");  

	} else {
		Blynk.virtualWrite(V1, "100");
		// digitalWrite(buzzerPin, LOW);
	}
	Blynk.virtualWrite(V0, state);
}

void sendTemp()
{
	int chk; 
	chk = DHT.read(DHT11_PIN);

	float h = DHT.humidity;
	Blynk.virtualWrite(V5, h);

	float t = DHT.temperature;
	Blynk.virtualWrite(V6, t);

	Serial.println("");
	Serial.print("Humidade: ");
	Serial.print(h, 0);
	Serial.print("% \nTemperatura: ");
	Serial.print(t, 0);
	Serial.print("C \n");
}

void setup()
{
	// Debug console
	Serial.begin(115200);

	Blynk.begin(auth, ssid, pass);

	pinMode(sensorPin,INPUT);
	pinMode(buzzerPin,OUTPUT);

	timer.setInterval(500L, sendMotion);
	timer.setInterval(1000L, sendTemp);
}

void loop()
{
	Blynk.run();
	timer.run();
}