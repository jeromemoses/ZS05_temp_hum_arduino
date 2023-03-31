#include <Arduino.h>
#include <Wire.h>

#define ZS05_ADDRESS 0x44

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(ZS05_ADDRESS);
  Wire.write(0x2C);  // Measure command
  Wire.write(0x06);  // High repeatability measurement
  Wire.endTransmission();
  
  delay(500);

  Wire.requestFrom(ZS05_ADDRESS, 6);
  byte msb_temp = Wire.read();
  byte lsb_temp = Wire.read();
  byte msb_humidity = Wire.read();
  byte lsb_humidity = Wire.read();
  byte checksum = Wire.read();

  float temperature = ((msb_temp << 8) | lsb_temp) * 175.0 / 65535.0 - 45.0;
  float humidity = ((msb_humidity << 8) | lsb_humidity) * 100.0 / 65535.0;
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  delay(2000);
}