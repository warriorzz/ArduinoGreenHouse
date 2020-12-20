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
