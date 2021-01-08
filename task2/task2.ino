#include <Wire.h>
#include <SPI.h>
#include <SD.h>

const int sensorPin = A1;   // Temperature sensor pin
File atmFile;
String nameAtm;

void setup(){
  Serial.begin(9600);
  setupSDCard();
  SD.remove("tempLog.txt");
  openFile("tempLog.txt");
  writeLine("------   NEXT TAKE  ------");
  closeFile();
}

void loop(){
   float timeStamp = getTime() / 1000;
   float tempC = getTemp();
   
   openFile("tempLog.txtxe");
   if ( atmFile ){
     atmFile.print(timeStamp);
     atmFile.print(" : ");
     atmFile.print(tempC);
     atmFile.println("°C");
     closeFile();
   }
   else Serial.println("Error accessing the card.")

   Serial.print(timeStamp);
   Serial.print(" : ");
   Serial.print(tempC);
   Serial.println("°C");

   delay(5000);
}
