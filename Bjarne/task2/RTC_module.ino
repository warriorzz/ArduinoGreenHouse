RTC_DS3231 rtc;
int count = 0;

void setupRTC() {
  Serial.begin(9600);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),  F(__TIME__)));

  openFile("MESSDATEN.CSV");
  printPart("Tag;Monat;Jahr;Stunden;Minuten;Temperatur;Druck(Pascal);Druck(Bar);Luftfeuchtigkeit");
  printLn();
  closeFile();
}

void loopRTC() {
      DateTime now = rtc.now();
      openFile("MESSDATEN.CSV");
      printPart(now.day());
      writePlaceholder();
      printPart(now.month());
      writePlaceholder();
      printPart((int) now.year());
      writePlaceholder();
      printPart(now.hour() + 1);
      writePlaceholder();
      printPart(now.minute());

      writePlaceholder();
      printTemperatureOnSDCard();
      writePlaceholder();
      printPascalOnSDCard();
      writePlaceholder();
      printBarOnSDCard();
      writePlaceholder();
      printHumidityOnSDCard();

      printLn();
      closeFile();
      readFile();
      closeFile();
}

char getCharArrayFromInt(uint8_t value) {
   char output[50];

   snprintf(output, 50, "%f", value);

   return output;
}
