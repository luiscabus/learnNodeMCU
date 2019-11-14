#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D1

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

void setup() {
  delay(100);
  Serial.begin(115200); // Initiate a serial communication
  Serial.println("Dallas Temperature IC Control Library Demo");
  
  sensors.begin();
}

void loop() {
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Temperature is: ");
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? 
  // You can have more than one IC on the same bus. 
  // 0 refers to the first IC on the wire
  delay(1000); 

}

