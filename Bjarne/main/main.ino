#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <Seeed_BME280.h>
#include <RTClib.h>

// Variables for automatic irrigation:
int soilMoisture;
const int moistureNorm = 0;  // The moisture we want to keep
const int moistureSensorPin = A0;
const int pumpPin = 10;

//Variables for LCD display
LiquidCrystal_I2C lcd(0x27,16,2);

//Variables for SD Card
File atmFile;
String nameAtm = String("_DATA.CSV");

//Variables for RTC
RTC_DS3231 rtc;

// Variables for BME
BME280 bme;

void setup() {
  Serial.begin(9600);
  // initialize moisture sensor
  pinMode(moistureSensorPin, INPUT);
  // initialize pump
  pinMode(pumpPin, OUTPUT);
  // initialize BME
  bme.init();
  
  setupLCD();
  if (!setupSDCard()) {
    Serial.println("Error! Could not initialize SD card");
  }
  setupRTC();

  openFile(nameAtm);
  writeLine("Time;Pressure (Bar);Pressure (Pascal);Humidity;Temperature");
  closeFile();
}

void loop() {
  checkMoisture();

  openFile(nameAtm);
  writeLine(getTimeFormatted() + ";" + getPressureBar() + ";" + getPressurePascal() + ";" + getHumidityString() + ";" + getTemperatureString());
  closeFile();
  delay(1000);
}

//Automatic irrigation
void startPump(){
  digitalWrite(pumpPin, HIGH);
}

void stopPump(){
  digitalWrite(pumpPin, LOW);
}

void checkMoisture(){
  soilMoisture = analogRead(moistureSensorPin);
  if ( soilMoisture < moistureNorm ) startPump();
  if ( soilMoisture > moistureNorm ) stopPump();
}

//LCD
void setupLCD() {
    setupLCD(true);
}

void displaySecondLine(String line) {
    lcd.setCursor(1,0);
    lcd.print(line);
}

void displayFirstLine(String line) {
  lcd.setCursor(0,0);
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

// SD-Card
bool setupSDCard() {
  return SD.begin(5);
}

void openFile(String name) {
  atmFile = SD.open(name, FILE_WRITE);
  if (!atmFile) {
      Serial.println("Failed to open File " + nameAtm + "!");
  }
}

void writeLine(String line) {
  atmFile.println(line);
}

void writePart(String line) {
  atmFile.print(line);
}

void closeFile() {
  atmFile.close();
}

// RTC
void setupRTC() {
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),  F(__TIME__)));
}

String getTimeFormatted() {
  Serial.println(String(rtc.now().hour())+ String(":") + String(rtc.now().minute()) + String(":") + String(rtc.now().second()));
  return String(rtc.now().hour()) + String(":") + String(rtc.now().minute()) + String(":") + String(rtc.now().second()); 
}

void setFileName() {
  /*Serial.println(randomString() + String("_DATA.CSV"));
  String string = randomString();
  string.concat("_DATA.CSV");
  nameAtm = string;*/
}

// BME
String getPressurePascal() {
  return String(bme.getPressure());
}

String getPressureBar() {
  return String((float) bme.getPressure() / (float) 100000);
}

String getHumidityString() {
  return String(bme.getHumidity());
}

String getTemperatureString() {
  return String(bme.getTemperature());
}

// General 
String randomString(){
    String pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    String randomString = "";
    for (int i = 0; i < 10; i++) {
        int randomInt = random(pool.length() - 1L);
        randomString += pool.substring(randomInt, randomInt + 1);
    }
    return randomString;
}
