#include "SSD1306.h"      // alias for `#include "SSD1306Wire.h"`
const char OLED_SDA = D3; // SDA Pin on nodemcu
const char OLED_SCL = D4; // SCL Pin on nodemcu
SSD1306 display(0x3c, OLED_SDA, OLED_SCL); // Initialize the OLED display using Wire library

#include <SPI.h>      // RFID Library
#include <MFRC522.h>  // RFID Library
#define RST_PIN D1 // D1
#define SS_PIN D2  // D2
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;

void setup() 
{
  delay(100);
  Serial.begin(115200); // Initiate a serial communication

  display.init();       // Initialising the UI will init the display too.
  display.flipScreenVertically();
  display.clear();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 30, "Identifique-se..");
  display.display();
  
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  pinMode(16, OUTPUT);
}

void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "2A CC 74 63") //change UID of the card that you want to give access
  {
    Serial.println(" Accesso Válido ");
    Serial.println(" Bem-vindo, Sr. Tag Azul ");
    statuss = 1;
    digitalWrite(16, HIGH);
    Oledprint("Acesso Válido \nID: " + content.substring(1) + "\nBem-Vindo", 5000);
  }
  else if (content.substring(1) == "60 C1 5C 56") //change UID of the card that you want to give access
  {
    Serial.println(" Accesso Válido ");
    Serial.println(" Bem-vindo, Sr. Luís ");
    statuss = 1;
    digitalWrite(16, HIGH);
    Oledprint("Acesso Válido \nID: " + content.substring(1) + "\nBem-Vindo", 5000);
  }
  
  else   {
    digitalWrite(16, LOW);
    Serial.println(" Accesso Negado ");
    Oledprint("Acesso Negado", 2000);
  }
  
}

void Oledprint(String param, int tempo)
{
  display.clear();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, param);
  display.display();
  delay(tempo);
  display.clear();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 30, "Identifique-se..");
  display.display();
  return;
}

