BME280 bme280;

void setupBME() {
    bme280.init();
}

void printTemperatureOnSDCard() {
    float temperature = bme280.getTemperature();
    char output[50];

    snprintf(output, 50, "%f", temperature);

    printPart(output);
}

void printBarOnSDCard() {
    float temperature = bme280.getPressure() / 100000;
    char output[50];

    snprintf(output, 50, "%f", temperature);

    printPart(output);
}

void printPascalOnSDCard() {
    float temperature = bme280.getPressure();
    char output[50];

    snprintf(output, 50, "%f", temperature);

    printPart(output);
}

void printHumidityOnSDCard() {
    float humidity = bme280.getHumidity();
    char output[50];

    snprintf(output, 50, "%f", humidity);

    printPart(output);
}
