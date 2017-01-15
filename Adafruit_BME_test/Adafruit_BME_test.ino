#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define BME280_I2C_ADDRESS 0x76
#define BAUDRATE 9600

Adafruit_BME280 bme; // I2C

void setup() {
  Serial.begin(BAUDRATE);
  Serial.println("Initializing BME280 ...");

  if (!bme.begin(BME280_I2C_ADDRESS)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
    delay(2000);
}
