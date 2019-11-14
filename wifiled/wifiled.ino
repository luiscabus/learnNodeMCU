
#include <ESP8266WiFi.h>

const char* ssid     = "FED";
const char* password = "eunaosei";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);   // this is a temporary line, to be removed after SDK update to 1.5.4
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  pinMode(LED_BUILTIN, OUTPUT);   //Set the Built in LED to pin to act as an output pin
  pinMode(5, OUTPUT); //Set the D0 to pin to act as an output pin

}

int value = 0;

void loop() {
  delay(5000);

  digitalWrite(LED_BUILTIN, LOW); //Turn off the LED
  digitalWrite(5, LOW);
  Serial.print("led OFF");
  delay(1000); // Wait for a second 
  digitalWrite(LED_BUILTIN, HIGH);//Turn on the LED
  digitalWrite(5, HIGH);
  Serial.print("led ON");
  delay(1000); // Wait for a second


}

