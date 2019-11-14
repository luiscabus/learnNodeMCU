#include "font_monospace.h"

#include <ESP8266WiFi.h>
char ssid[] = "wLC";
char pass[] = "";
// char ssid[] = "IC-ALUNOS";
// char pass[] = "icomputacaoufal";

#include <BlynkSimpleEsp8266.h>
char auth[] = "756e1a5712854954b23fd086ee6d83e4";
BlynkTimer timer;

#include "SSD1306.h"      // alias for `#include "SSD1306Wire.h"`
const char OLED_SDA = D6; // SDA Pin on nodemcu
const char OLED_SCL = D7; // SCL Pin on nodemcu
SSD1306 display(0x3c, OLED_SDA, OLED_SCL); // Initialize the OLED display using Wire library

#include <dht11.h>
#define DHT11_PIN D1
dht11 DHT;

#define motionPin D2
#define buzzerPin D3




String g_movimento;
int g_humidade = 0;
int g_temperatura = 0;


void displaySetup()
{
	display.init();       // Initialising the UI will init the display too.
	display.clear();
	display.flipScreenVertically();
	display.setFont((const uint8_t*)Nimbus_Sans_L_Regular_12);
	display.setTextAlignment(TEXT_ALIGN_LEFT);

	display.drawString(0, 0, "Boot iniciado");
	display.drawString(0, 16, "  Conectando ao Wi-Fi,");
	display.drawString(0, 32, "    aguarde...");
	display.display();
}

void displayRefresh()
{
	display.clear();
	display.drawString(0, 0, String("Humi: " + String(g_humidade) + "%"));
	display.drawString(0, 16, String("Temp: " + String(g_temperatura) + ".C"));
	display.drawString(0, 32, String("Movimento: " + String(g_movimento)));
	display.drawString(0, 48, String("Oiiii: "));
	display.display();
}

void sendMotion()
{
	int state;
	state = digitalRead(motionPin);

	// Send it to the server
	if (state == 1) {
		Blynk.virtualWrite(V1, "1023");
		// digitalWrite(buzzerPin, HIGH);
		Blynk.notify("LC Home > Motion detected");
		g_movimento = "sim";

	} else {
		Blynk.virtualWrite(V1, "100");
		// digitalWrite(buzzerPin, LOW);
		g_movimento = "nao";
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

	g_humidade = (int)h;
	g_temperatura = (int)t;
}

void setup()
{
	// Debug console
	Serial.begin(115200);

	pinMode(motionPin,INPUT);
	pinMode(buzzerPin,OUTPUT);

	displaySetup();

	delay(1000);

	Serial.println("");
	Serial.println("Boot iniciado.");
	// Serial.println(String("Chip ID: " + ESP.getChipId()));
	Serial.print("Chip ID: ");
	Serial.println(ESP.getChipId());
	Serial.print("MAC: ");
	Serial.println(WiFi.macAddress());

	Blynk.begin(auth, ssid, pass);

	timer.setInterval(500L, sendMotion);
	timer.setInterval(2000L, sendTemp);
	timer.setInterval(1000L, displayRefresh);
}

void loop()
{
	Blynk.run();
	timer.run();
}
