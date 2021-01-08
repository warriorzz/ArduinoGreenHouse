float getTemp(){        // read temperature in degrees Celcius
  float reading = analogRead(sensorPin);
  return (reading*500)/1023 ;
}
