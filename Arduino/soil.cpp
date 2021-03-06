
#include <Arduino.h>


int moisturePowerPin = A3;
int sensorPin = A1;    
int moisture = 0;  // variable to store the value coming from the moisture sensor


void soilSetup()
{
  pinMode(moisturePowerPin, OUTPUT);
  digitalWrite(moisturePowerPin, LOW); 
}

void soil()
{
  digitalWrite(moisturePowerPin, HIGH);              // Powers up the moisture sensor for 0.1 seconds to prevent corrosion.
  moisture = (analogRead(sensorPin)*0.120)-9;         // The sensor is calibrated.
  delay (100);
  digitalWrite(moisturePowerPin, LOW);               // Powers down the moisture sensor
  //Serial.print("Soil moisture: "); Serial.print(moisture); Serial.println(" %");
}

