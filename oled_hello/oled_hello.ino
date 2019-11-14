/* Hello World OLED Test */
//#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier

#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
const char OLED_SDA = D3; // SDA Pin on nodemcu
const char OLED_SCL = D4; // SCL Pin on nodemcu
SSD1306 display(0x3c, OLED_SDA, OLED_SCL); // Initialize the OLED display using Wire library

void setup() 
{
  delay(100);
  Serial.begin(115200);

  display.init(); // Initialising the UI will init the display too.
  display.flipScreenVertically();
}

void loop() 
{
  display.clear();
  
    drawWhatever();

  display.display();
  delay (2000);
}

/***************************************************
* Draw Indoor Page
****************************************************/
void drawWhatever() 
{
  int x=0;
  int y=0;
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0 + x, 5 + y, "Hum");
  
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(38 + x, y, "Oled Hello");

  display.setFont(ArialMT_Plain_24);
  display.drawString(0 + x, 15 + y, "77");

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(95 + x, 5 + y, "Temp");

  display.setFont(ArialMT_Plain_24);
  display.drawString(70 + x, 15 + y, "39 °C");
}


