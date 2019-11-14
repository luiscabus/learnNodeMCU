#include <ESP8266WiFi.h>
const char* ssid = "FED";
const char* password = "eunaosei";
IPAddress networkIP;
WiFiServer server(80);

#include "SSD1306.h"      // alias for `#include "SSD1306Wire.h"`
const char OLED_SDA = D3; // SDA Pin on nodemcu
const char OLED_SCL = D4; // SCL Pin on nodemcu
SSD1306 display(0x3c, OLED_SDA, OLED_SCL); // Initialise the OLED display using Wire library

#include <DHT.h>
// #include <DHT_U.h>
#define DHTPIN 10 // SD3 Pin
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); // DHT module pin
float localTemp = 0, localHum = 0;
int lastTemp = 0, lastHum = 0;

int ledPin = D8; // GPIO0


void setup() {
  delay(100);
  Serial.begin(115200); 

  display.init(); // Initialising the UI will init the display too.
  display.flipScreenVertically();

  dht.begin(); // Initialising the DHT sensor.
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  drawRect();
  fillRect();
  getDHT();
  drawDHT();

    display.drawString(0, 54, "Conectando ao Wifi...");
    display.display();
  connectToWifi();
  drawDHT();
}
 
void loop() {
  webserverFunctions(); 

  delay(5000);

  dweetio();

  getDHT();
  drawDHT();
}
