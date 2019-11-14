void dweetio()
{
  // Host
  const char* host = "dweet.io";

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  Serial.println("connecting to dweet.io");
  // This will send the request to the server
  client.print(String("GET /dweet/for/esp8266lcbr?temperature=") + String(lastTemp) + "&humidity=" + String(lastHum) + 
               "&ipaddress=" + String(WiFi.localIP().toString()) + 
               " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}

