int relayPin = 0; //D3

void setup() {
  pinMode(relayPin, OUTPUT);
  delay(2000);
  Serial.begin(9600);
}

void loop() {
  delay(2000);
  digitalWrite(relayPin, HIGH);
  Serial.println("high");
  delay(2000);
  digitalWrite(relayPin, LOW);
  Serial.println("low");
  delay(2000);
}
