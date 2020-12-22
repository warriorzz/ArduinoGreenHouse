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
