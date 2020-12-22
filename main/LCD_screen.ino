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
