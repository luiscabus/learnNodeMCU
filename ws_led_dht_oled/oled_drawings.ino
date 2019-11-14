/***************************************************
* Handle Oled display writing
****************************************************/
void drawDHT() 
{
  display.clear();
  
  int x=0;
  int y=0;
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0 + x, 15 + y, "Hum");
  
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(30 + x, y, "Weather Station");

  display.setFont(ArialMT_Plain_16);
  String hum = String(localHum) + "%";
  display.drawString(0 + x, 25 + y, hum);
  int humWidth = display.getStringWidth(hum);

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(100 + x, 15 + y, "Temp");

  display.setFont(ArialMT_Plain_16);
  String temp = String(localTemp) + "°C";
  display.drawString(70 + x, 25 + y, temp);
//  int tempWidth = display.getStringWidth(temp);

  display.setFont(ArialMT_Plain_10);
  String netip = "IP: " + WiFi.localIP().toString();
  display.drawString(0 + x, 43 + y, netip);
//  int netipWidth = display.getStringWidth(netip);
  
  display.display();
}

// Adapted from Adafruit_SSD1306
void drawRect(void) {
  for (int16_t i=0; i<DISPLAY_HEIGHT/2; i+=2) {
    display.drawRect(i, i, DISPLAY_WIDTH-2*i, DISPLAY_HEIGHT-2*i);
    display.display();
    delay(10);
  }
  delay(1000);
  display.clear();
}
// Adapted from Adafruit_SSD1306
void fillRect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<DISPLAY_HEIGHT/2; i+=3) {
    display.setColor((color % 2 == 0) ? BLACK : WHITE); // alternate colors
    display.fillRect(i, i, DISPLAY_WIDTH - i*2, DISPLAY_HEIGHT - i*2);
    display.display();
    delay(10);
    color++;
  }
  // Reset back to WHITE
  display.setColor(WHITE);
  delay(1000);
  display.clear();
}
