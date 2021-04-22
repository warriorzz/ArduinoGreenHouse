#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <Seeed_BME280.h>
#include <RTClib.h>

// Variables for automatic irrigation:
int soilMoisture;
int nextMeasurement = 0;
const int moistureNorm = 700;  // The moisture we want to keep
const int moistureSensorPin = A0;
const int pumpPin = 10;

//Variables for LCD display
LiquidCrystal_I2C lcd(0x27,16,2);

//Variables for SD Card
File atmFile;
String nameAtm;
const String bmeDataFileName = "data.csv";

//Variables for RTC
RTC_DS3231 rtc;

// Variables for BME
BME280 bme;

void setup() {
  // initalize moisture sensor
  pinMode(moistureSensorPin, INPUT);
  // initialize pump
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
  // initialize BME
  //bme.init();
  
  setupLCD();
  setupSDCard();
  setupRTC();

  openFile(bmeDataFileName);
  writeLine("Time;Pressure (Bar);Pressure (Pascal);Humidity");
  closeFile();
}

void loop() {
  if ( nextMeasurement % 5 == 0 ) checkMoisture();
  
  openFile(bmeDataFileName);
  writeLine(getTimeFormated() + ";" + getPressureBar() + ";" + getPressurePascal() + ";" + getHumidity());
  closeFile();
  
  delay(1000);
  if ( (nextMeasurement+3) % 5 == 0) stopPump(); 
  // The pump should be only activated for a short time (3s)
  nextMeasurement++;
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
  if ( soilMoisture > moistureNorm ) startPump();
  /*if ( soilMoisture < moistureNorm ) stopPump();
  Serial.println(String(map(soilMoisture,253,1019,100,0))+","+String(soilMoisture));
  Serial.println("Grenzwert: "+String(map(moistureNorm,253,1019,100,0)));*/
}

//LCD
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
  nameAtm = name;
  atmFile = SD.open(name, FILE_WRITE);
}

void writeLine(String line) {
  atmFile.println(line);
}

void closeFile() {
  atmFile.close();
}

// RTC
void setupRTC() {
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),  F(__TIME__)));
}

String getTimeFormated() {
  return getCharArrayFromInt(rtc.now().hour())+ String(":") + getCharArrayFromInt(rtc.now().minute()) + String(":") + getCharArrayFromInt(rtc.now().second()); 
}

// BME
float getPressurePascal() {
  return bme.getPressure();
}

float getPressureBar() {
  return bme.getPressure() / 100000;
}

float getHumidity() {
  bme.getHumidity();
}

// General
char getCharArrayFromInt(uint8_t value) {
  char output[50];

   snprintf(output, 50, "%f", value);

   return output;
}
