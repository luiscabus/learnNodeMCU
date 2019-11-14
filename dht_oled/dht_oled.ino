#include "SSD1306.h"      // alias for `#include "SSD1306Wire.h"`
const char OLED_SDA = D3; // SDA Pin on nodemcu
const char OLED_SCL = D4; // SCL Pin on nodemcu
SSD1306 display(0x3c, OLED_SDA, OLED_SCL); // Initialize the OLED display using Wire library

// #include "DHT.h"
#include "dht11.h"
// #include <DHT_U.h>
#define DHTPIN D1 // 10 = Pin S3 SD3
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); // DHT module pin

float localTemp = 0, localHum = 0;
int lastTemp = 0, lastHum = 0;

void setup() 
{
  delay(100);
  Serial.begin(115200);
  
  display.init(); // Initialising the UI will init the display too.
  display.flipScreenVertically();
  
  dht.begin(); // Initialising the DHT sensor.
}

void loop() {
  getDHT();
  drawDHT(); 
  delay (2000);

}

/***************************************************
* Get indoor Temp/Hum data
****************************************************/
void getDHT()
{
  float tempIni = localTemp;
  float humIni = localHum;
  localTemp = dht.readTemperature();
  localHum = dht.readHumidity();
  if (isnan(localHum) || isnan(localTemp))   // Check if any reads failed and exit early (to try again).
  {
    Serial.println("Failed to read from DHT sensor!");
    localTemp = tempIni;
    localHum = humIni;
    return;
  }
  else
  {
    if (lastTemp != localTemp && lastHum != localHum){
      Serial.println("");
      Serial.print("Temperatura: ");
      Serial.print(localTemp);
      Serial.println(" *C");
      Serial.print("Umidade: ");
      Serial.print(localHum);
      Serial.print(" %t \n");
      lastTemp = localTemp;
      lastHum = localHum;
    }
  }
}

/***************************************************
* Draw Indoor Page
****************************************************/
void drawDHT() 
{
  display.clear();
  
  int x=0;
  int y=0;
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0 + x, 20 + y, "Hum");
  
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(6 + x, y, "Weather Monitor");

  display.setFont(ArialMT_Plain_16);
  String hum = String(localHum) + "%";
  display.drawString(0 + x, 35 + y, hum);
  int humWidth = display.getStringWidth(hum);

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(98 + x, 20 + y, "Temp");

  display.setFont(ArialMT_Plain_16);
  String temp = String(localTemp) + "°C";
  display.drawString(68 + x, 35 + y, temp);
  int tempWidth = display.getStringWidth(temp);
  
  display.display();
}

