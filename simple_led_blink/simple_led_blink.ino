#define ledPin LED_BUILTIN
// #define ledPin 16

void setup()
{
	// Debug console
	Serial.begin(115200);

	pinMode(ledPin,OUTPUT);

	delay(1000);

	Serial.println("");
	Serial.println("Boot iniciado.");
	delay(1000);
	Serial.println("Vou iniciar o Loop para piscar os leds.");
	delay(1000);
	Serial.println("Lá vai!");
	
}

void loop()
{
	digitalWrite(ledPin, HIGH);
	delay(1000);
	digitalWrite(ledPin, LOW);
	delay(1000);

}