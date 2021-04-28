
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

// Variables for automatic irrigation:
int soilMoisture;
const int moistureNorm = 0;  // The moisture we want to keep
const int moistureSensorPin = A0;
const int pumpPin = 12;
const int motorPin = 13;

//Variables for LCD display
LiquidCrystal_I2C lcd(0x27,16,2);

//Variables for SD Card
File file;

void setup() {
  pinMode( moistureSensorPin, INPUT);
  pinMode( motorPin, OUTPUT);
  setupLCD();
  if(setupSDCard()) {
    //TODO
  }
}

void loop() {
  checkMoisture();
  delay(1000);
}

void startPump(){
  //start motor here
}

void stopPump(){
  //stop motor here
}

void checkMoisture(){
  soilMoisture = analogRead(moistureSensorPin);
  soilMoisture = map ( soilMoisture, 550, 0, 0, 100 );
  if ( soilMoisture < moistureNorm ) startPump();
  if ( soilMoisture > moistureNorm ) stopPump();
}

void setupLCD() {
    lcd.begin();
    lcd.backlight();
}

void displaySecondLine(String line) {
    lcd.setCursor(1,0);
    lcd.print(line);
}

void displayFirstLine(String line) {
  lcd.setCursor(0,0);
  lcd.print(line);
}

void displaySecondLine(String line, int cursor) {
    lcd.setCursor(1,cursor);
    lcd.print(line);
}

void displayFirstLine(String line, int cursor) {
    lcd.setCursor(0,cursor);
    lcd.print(line);
}

void setupLCD(bool backlight) {
    lcd.begin();
    if (backlight) {
        lcd.backlight();
    } else {
        lcd.noBacklight();
    }
}

void setBacklight(bool backlight) {
    if (backlight) {
        lcd.backlight();
    } else {
        lcd.noBacklight();
    }
}

File atmFile;
String nameAtm;

bool setupSDCard() {
  return SD.begin(5);
}

void openFile(String name) {
  nameAtm = name;
  atmFile = SD.open(name, FILE_WRITE);
}

void writeLine(String line) {
  atmFile.println(line);
}

void closeFile() {
  atmFile.close();
}
