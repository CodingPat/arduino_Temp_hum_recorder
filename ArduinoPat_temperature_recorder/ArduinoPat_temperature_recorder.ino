#include <Wire.h>
#include <RTClib.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"
#include <extEEPROM.h>
#include <Time.h>

//define baudrate for serial communications
#define BAUDRATE 9600

//parameters for pressure/temperature sensor (BME280)
#define SEALEVELPRESSURE_HPA (1013.25)
#define BME280_I2C_ADDRESS 0x76

//time (ms) between capture of date 
#define DELAY 5000

//create real-time clock object
RTC_DS3231 rtc;

//create bme280 object
Adafruit_BME280 bme;

//create external eeprom AT24c32 object
extEEPROM eeprom(kbits_32,1,32);//32K, 1 eeprom externe, taille de page=32 bytes (datasheet AT24C32)

struct DataRecord {
  time_t time;
  float temperature;
  float humidity;
  unsigned int next_record;
  };

DataRecord record; //record
DataRecord *recordp; //pointer to record
DataRecord *lastrecordp;//pointer to last used record



//setup
void setup() {
  // Initialize RTC:
  Serial.begin(BAUDRATE);
  Serial.println(F("Initializing RTC ..."));
  if (! rtc.begin()) {
    Serial.println(F("FATTAL ERROR - Couldn't find RTC"));
    while (1);
  }
  
  if (rtc.lostPower()) {
    Serial.println(F("RTC lost power, lets set the compilation time!"));
    // sets the RTC to the date & time of compilation
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
       
  }

  
  //Initialize BME280
  
  Serial.println(F("Initializing BME280 ..."));

  if (!bme.begin(BME280_I2C_ADDRESS)) {
    Serial.println(F("FATTAL ERROR - Couldn't find BME280"));
    while (1);
  }


 //Initialize external EEPROM AT24C32
 Serial.println(F("Initializing EEPROM AT24C32 ..."));

 if (eeprom.begin(twiClock100kHz)){
  Serial.print(F("extEEPROM.begin() failed, status = "));
  while (1);
  }
 
 
  
  

}

//start
void loop() {
  delay(DELAY);  
  take_measure();
  print_measure();
  record_measure();  

  read_command();
  

}

void read_command(){
   String command;
  //get commands via serial line
  while (Serial.available()>0){
    command=Serial.readStringUntil('\n');
    }

  if (command== "measure")
    take_measure();
  if (command=="print measure");
    print_measure();
  
  
  }
void take_measure(){
  //get temperature and humidity
  record.temperature=bme.readTemperature();
  record.humidity=bme.readHumidity();
  
  // get date time:
  record.time=rtc.now().unixtime();

  }

void print_measure(){
  //print results
  print_date_time(record.time);
  Serial.print(" - ");
  print_temp_hum(record.temperature,record.humidity);
  Serial.println();

  }

void record_measure(){
  
  }

void print_all_records(){
  // send values recorded to serial line
  
  
  }

void reset_eeprom(){
  // No need to reset all the memory. write 0 values to first record suffice. Because next address will be zeroed.
  
  }

void print_date_time(time_t now){
  Serial.print(convertto2digits(day(now)));
  Serial.print('/');
  Serial.print(convertto2digits(month(now)));
  Serial.print('/');
  Serial.print(year(now),DEC);//no conversion needed (always 4 digits)
  Serial.print(" - ");
  Serial.print(convertto2digits(hour(now)));
  Serial.print(':');
  Serial.print(convertto2digits(minute(now)));
  Serial.print(':');
  Serial.print(convertto2digits(second(now)));
  
  }

void print_temp_hum(float temperature, float humidity){
  Serial.print(temperature);
  Serial.print(" C");
  Serial.print(" - ");
  Serial.print(humidity);
  Serial.print("% Hum.");
  
  }

String convertto2digits(int number){
  String str="";
  if (number <10) {
    str="0";
    }
  str+=number;
  
  return(str);  
  }  
