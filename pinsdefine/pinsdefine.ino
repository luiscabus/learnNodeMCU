/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis
  Modified for ESP8266 platform by Ivan Grokhotkov, 2014-2015.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
  #define Pins_Arduino_h
  
  #define PIN_WIRE_SDA (4)
  #define PIN_WIRE_SCL (5)
  
  static const uint8_t SDA = PIN_WIRE_SDA;
  static const uint8_t SCL = PIN_WIRE_SCL;
  
  #define LED_BUILTIN 16
  
  static const uint8_t D0   = 16;
  static const uint8_t D1   = 5;
  static const uint8_t D2   = 4;
  static const uint8_t D3   = 0;
  static const uint8_t D4   = 2;
  static const uint8_t D5   = 14;
  static const uint8_t D6   = 12;
  static const uint8_t D7   = 13;
  static const uint8_t D8   = 15;
  static const uint8_t D9   = 3;
  static const uint8_t D10  = 1;
  
  #include "../generic/common.h"

#endif /* Pins_Arduino_h */

void setup() {
  Serial.begin(115200); //INICIALIZA A SERIAL
  pinMode(LED_BUILTIN, OUTPUT);   //Set the Built in LED to pin to act as an output pin
  pinMode(5, OUTPUT); //Set the D0 to pin to act as an output pin

}
void loop() {
  digitalWrite(LED_BUILTIN, LOW); //Turn off the LED
  digitalWrite(5, LOW);
  Serial.print("led OFF");
  delay(1000); // Wait for a second 
  digitalWrite(LED_BUILTIN, HIGH);//Turn on the LED
  digitalWrite(5, HIGH);
  Serial.print("led ON");
  delay(1000); // Wait for a second

}




