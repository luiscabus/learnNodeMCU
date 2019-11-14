/* Hello World OLED Test */
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
const char OLED_SCL = D1; // SCL Pin on nodemcu
const char OLED_SDA = D2; // SDA Pin on nodemcu
SSD1306  display(0x3c, OLED_SCL, OLED_SDA); // Initialise the OLED display using Wire library

int ledPin = D3; // Set led pin

void setup()
{
  Serial.begin(115200);
  display.init(); // Initialising the UI will init the display too.
  display.flipScreenVertically();

  display.clear();
  drawHelloWorld();
  display.display();

  pinMode(ledPin, OUTPUT);

}

void loop()
{
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

void drawHelloWorld()
{
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Hello world");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "Hello worldd");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 26, "Hello world");
}
