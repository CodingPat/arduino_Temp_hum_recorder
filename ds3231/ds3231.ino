#include <RTClib.h>
#include <Wire.h>

RTC_DS3231 rtc;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC.");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2017, 1, 22, 15, 33, 0));
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now=rtc.now();
  Serial.print(now.day(),DEC);
  Serial.print('/');
  Serial.print(now.month(),DEC);
  Serial.print('/');
  Serial.print(now.year(),DEC);
  Serial.print(" - ");
  Serial.print(now.hour(),DEC);
  Serial.print(':');
  Serial.print(now.minute(),DEC);
  Serial.print(':');
  Serial.print(now.second(),DEC);
  Serial.print("\n");
  
  
  delay(1000);
}
