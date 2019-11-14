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
