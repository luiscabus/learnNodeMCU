#include <ESP8266WiFi.h>
char ssid[] = "FED";
char pass[] = "eunaosei";

#include <BlynkSimpleEsp8266.h>
char auth[] = "756e1a5712854954b23fd086ee6d83e4";

BlynkTimer timer;

/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial

#include "SSD1306.h"      // alias for `#include "SSD1306Wire.h"`
const char OLED_SDA = D6; // SDA Pin on nodemcu
const char OLED_SCL = D7; // SCL Pin on nodemcu
SSD1306 display(0x3c, OLED_SDA, OLED_SCL); // Initialize the OLED display using Wire library

#include <SPI.h>      // RFID Library
#include <MFRC522.h>  // RFID Library

#define RST_PIN D1 // D1
#define SS_PIN D2  // D2
//MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;


WidgetLED led50(V50);
WidgetLED led51(V51);
WidgetLED led52(V52);
WidgetLED led53(V53);
WidgetLED led54(V54);
WidgetLED led55(V55);
WidgetLED led56(V56);
WidgetLED led57(V57);

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
}

// Attach virtual serial terminal to Virtual Pin V1
WidgetTerminal terminal(V0);

// You can send commands from Terminal to your hardware. Just use
// the same Virtual Pin as your Terminal Widget
BLYNK_WRITE(V0)
{

  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
  } else {

    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}


void setup() {
  delay(1000);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  display.init();       // Initialising the UI will init the display too.
  display.flipScreenVertically();
  helloDisplay();

  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Type 'Marco' and get a reply, or type"));
  terminal.println(F("anything else and get it printed back."));
  terminal.flush();

  timer.setInterval(2000L, myTimerEvent);
  timer.setInterval(1000L, checkRfid);
}

void loop() {
  Blynk.run();
  timer.run();
//  monitorRfid();
  
}
