void setupLCD() {
    lcd.begin();
    lcd.backlight();
}

void displaySecondLine(string line) {
    lcd.cursor(1,0);
    lcd.print(line)
}

void displayFirstLine(string line) {
  lcd.cursor(0,0);
  lcd.print(line)
}

void displaySecondLine(string line, int cursor) {
    lcd.cursor(1,cursor);
    lcd.print(line)
}

void displayFirstLine(string line, int cursor) {
    lcd.cursor(0,cursor);
    lcd.print(line)
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