#include <Wire.h>
#include <SPI.h>
#include <SD.h>

void setup(){
  setupSDCard();
  openFile("test.txt");
  writeLine("Test");
  closeFile();
}

void loop(){
   
}
