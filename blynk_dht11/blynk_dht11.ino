/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// #include <DHT.h>

#include <dht11.h>
#define DHT11_PIN 5
dht11 DHT;
float lastHum, lastTemp;

// You should get Auth Token in the Blynk App. Go to the Project Settings (nut icon).
char auth[] = "2c22239fb9bf4cb09311967d6a1d2698";

// Your WiFi credentials. Set password to "" for open networks.
char ssid[] = "FED";
char pass[] = "eunaosei";

// Uncomment whatever type you're using!
// #define DHTPIN 5          // What digital pin we're connected to
// #define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
// DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;






// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
	//  float h = dht.readHumidity();
	//  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

	float h, t;

	if (isnan(h) || isnan(t)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}
	// You can send any value at any time.
	// Please don't send more that 10 values per second.
	Blynk.virtualWrite(V5, h);
	Blynk.virtualWrite(V6, t);
}

void sendTemp()
{
	int chk; 
	chk = DHT.read(DHT11_PIN);    // READ DATA

	float localHum, localTemp;
	localHum = DHT.humidity;
	localTemp = DHT.temperature;

	if (isnan(localHum) || isnan(localTemp) || (localHum == 0.00) || (localTemp == 0.00) )  // Check if any reads failed and exit early (to try again).
	{
		Serial.println("Failed to read from DHT sensor!");
		Blynk.virtualWrite(V22, "Failed to read from DHT sensor"); //virtual pin
		localTemp = 0;
		localHum = 0;
		return;
	}
	else
	{
		if (lastHum != localHum && lastTemp != localTemp){
			Serial.println("");
			Serial.print("Umidade: ");
			Serial.print(localHum);
			Serial.print("%t \nTemperatura: ");
			Serial.print(localTemp);
			Serial.print(" ℃");
			Serial.print("\n");
			lastTemp = localTemp;
			lastHum = localHum;
		}
	}

	Blynk.virtualWrite(10, localHum); //virtual pin
	Blynk.virtualWrite(11, localTemp); // virtual pin 
}


void sendRandominfo()
{
	// Generate random temperature value 10.0 to 30.0 (for example)
	float t = float(random(100, 300)) / 10;

	// Format: 1 decimal place, add ℃
	String str = String(t, 1) + "℃";

	// Send it to the server
	Blynk.virtualWrite(V5, str);
}







void setup()
{
	// Debug console
	Serial.begin(115200);

	Blynk.begin(auth, ssid, pass);
	// You can also specify server:
	//Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
	//Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

	//  dht.begin();

	// Setup a function to be called every second
	// timer.setInterval(1000L, sendSensor);
	timer.setInterval(1000L, sendRandominfo);
	timer.setInterval(2000L, sendTemp);
}

void loop()
{
	Blynk.run();
	timer.run();
}
