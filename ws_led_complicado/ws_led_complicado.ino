#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "cabus";
const char* password = "cabusnet01";

ESP8266WebServer server(80); // Instantiate server at port 80 (http port)

String page = ""; // Page variable empty
int LEDPin = D2; // Led Pin

void setup(void) {
  
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p>";
  
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection  
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", []() {
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    Serial.println("Led Ligado");
    delay(1000);
  });
  server.on("/LEDOff", []() {
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    Serial.println("Led Desligado");
    delay(1000);
  });
  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  server.handleClient();
}
