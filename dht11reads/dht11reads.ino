#include <DHT.h>
#include <DHT_U.h>

DHT dht(D1, DHT11); // DHT module pin
int last_temp = 0, last_humidity = 0;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity(); // A leitura da temperatura e umidade pode levar 250ms!
  float t = dht.readTemperature(); // O atraso do sensor pode chegar a 2 segundos.

  if (isnan(t) || isnan(h)) // testa se retorno é valido, caso contrário algo está errado.
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    if (last_temp != t || last_humidity != h){
      Serial.print("Temperatura: ");
      Serial.print(t);
      Serial.println(" *C");
      Serial.print("Umidade: ");
      Serial.print(h);
      Serial.print(" %t \n");
      last_temp = t;
      last_humidity = h;
    }
    else
    {
      Serial.print("Mesma temperatura \n");
    }
  }

  delay(2000);
}
