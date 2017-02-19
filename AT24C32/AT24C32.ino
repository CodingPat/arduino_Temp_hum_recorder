#include <Wire.h>
#include <extEEPROM.h>

//define baudrate for serial communications
#define BAUDRATE 9600

//create external eeprom AT24c32 object
extEEPROM eeprom(kbits_32,1,32,0x57);//32K, 1 eeprom externe, taille de page=32 bytes (datasheet AT24C32),I2C address 


//setup
void setup() {
 
  Serial.begin(BAUDRATE);

    
 //Initialize external EEPROM AT24C32
 
 Serial.print(F("Initializing EEPROM AT24C32 ..."));

 if (eeprom.begin(twiClock100kHz)){
  Serial.print(F("Initialization extEEPROM failed"));
  while (1);
 }
 else{
  Serial.println(" OK");
 }
 
}

//start
void loop() {
  unsigned int nr_bytes=eeprom.length();
  Serial.print("#bytes of external eeprom : ");
  Serial.println(nr_bytes,DEC);
  
  test();
  
  
  while(1){}

}

void test(){
  //write first 20 addresses with values 0..19
  int value,nr_errors=0;
  
  for(int i=0;i<20;i++){
    eeprom.write(i,i);  
    }

  for(int i=0;i<20;i++){
    value=eeprom.read(i);
    Serial.print("Address ");
    Serial.print(i,DEC);
    Serial.print(" - ");
    Serial.print(value,DEC);
    Serial.println();
    
    if(!(value==i)){
      Serial.print("Error value ");
      Serial.println(value,DEC);
      nr_errors++;
      
      }  
     
    }

   
   if (nr_errors==0) {
    Serial.println("######### TEST COMPLETED WITHOUT ERRORS ###########");
    }
   else
   {
    Serial.println("######### TEST FAILED ! ###########################");
    }

   Serial.print("#Errors : ");
   Serial.println(nr_errors,DEC);


  }




