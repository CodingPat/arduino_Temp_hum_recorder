/******************************************************************************
******************************************************************************/

#include <stdint.h>
#include "SparkFunBME280.h"
#include "Wire.h" //I2C

#define BME280_I2C_ADDRESS 0x76

//Global sensor object
BME280 mySensor;

void setup()
{
  
  mySensor.settings.commInterface = I2C_MODE;
  mySensor.settings.I2CAddress = BME280_I2C_ADDRESS;
  
  mySensor.settings.runMode = 3; //Normal mode
  
  //tStandby can be:
  //  0, 0.5ms
  //  1, 62.5ms
  //  2, 125ms
  //  3, 250ms
  //  4, 500ms
  //  5, 1000ms
  //  6, 10ms
  //  7, 20ms
  mySensor.settings.tStandby = 0;
  
  //filter can be off or number of FIR coefficients to use:
  //  0, filter off
  //  1, coefficients = 2
  //  2, coefficients = 4
  //  3, coefficients = 8
  //  4, coefficients = 16
  mySensor.settings.filter = 0;
  
  //tempOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  mySensor.settings.tempOverSample = 1;

  //pressOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
    mySensor.settings.pressOverSample = 1;
  
  //humidOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  mySensor.settings.humidOverSample = 1;
  
  Serial.begin(9600);
  Serial.print("Initializing BME280... ");
  delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
  
  if (!mySensor.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
}

void loop()
{
  
  Serial.print("Temperature: ");
  Serial.print(mySensor.readTempC(), 2);
  Serial.println(" degrees C");

  Serial.print("%RH: ");
  Serial.print(mySensor.readFloatHumidity(), 2);
  Serial.println(" %");
  
  Serial.println();
  
  delay(2000);

}
