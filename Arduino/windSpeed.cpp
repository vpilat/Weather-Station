#include <Arduino.h>
#include "counters.h"

int frequency;
float correction =0;
double runningTotal =0;

float knots =0.00;
float knotsMax =0.00;
float knotsAv =0.00;

float knotsDec =0.1;
float knotsMaxDec =0.1;
float knotsAvDec =0.1;

int frequencyInt;
int knotsInt;
int knotsAvInt;
int knotsMaxInt; 

int knotsDecInt;
int knotsMaxDecInt;
int knotsAvDecInt;

float previousKnots =0;

float calibration = 1.0047;    // (46.62 / 46.4)

void windSpeedSetup()
{
  
}
    
void windSpeed()
{
  frequency = 500000/pulseIn(5,HIGH,5000000);
  if (frequency < 0){frequency=0;}    
  int correction =0;
  int adjustments();
  
  knots = (frequency * calibration /10) + correction;
  if (z==-1)
  {
    previousKnots = knots;
  }
  if (knots < 10)                            // Filter out some weird readings at low speeds.
  {
    if( (knots/previousKnots) > 2)
    {
      knots = previousKnots;
      Serial.println("..... ERROR DETECTED !! .....");
      tone(3,1000,10000);
      delay(10000);
    }
    previousKnots = knots;
  }
  
  z++;

  if (knots > knotsMax)
  {
    knotsMax = knots;
  }
  
  runningTotal = runningTotal + knots;
  if(z==1)
  {
    runningTotal = knots;                              // Reset running total and max wind gust (knotsMax).
    knotsMax = knots;
  }
  
  knotsAv = runningTotal / z;
  if(knots > 0)
  {
    int beepFreq = ((int)knots * 10)+300;
    //Serial.print("beepFreq: ");Serial.println(beepFreq); 
    //tone(3,beepFreq,150);
  }
  Serial.print("Z: ");Serial.print(z);  
  Serial.print("    Knots: ");Serial.print(knots);
  Serial.print("    Previous knots: ");Serial.println(previousKnots);
  //Serial.print("    Av wind speed: ");Serial.print(knotsAv);  
  //Serial.print("    Max wind gust: ");Serial.println(knotsMax);   
  //Serial.print("   Running total: ");Serial.println(runningTotal);
  //Serial.print("Z: ");Serial.println(z);
}
void adjustments()
{   
    if ((frequency >=1) && (frequency <=100)) {correction = 0.20;}
    if ((frequency >100) && (frequency <=200)) {correction = 0.10;}
    if ((frequency >200) && (frequency <=300)) {correction = -0.25;}
    if ((frequency >300) && (frequency <=400)) {correction = -0.60;}
    if ((frequency >400) && (frequency <=500)) {correction = -1;}
    if ((frequency >500) && (frequency <=600)) {correction = -1.4;}
    if ((frequency >600) && (frequency <=700)) {correction = -1.75;}
    if ((frequency >700) && (frequency <=800)) {correction = -2;}
    if ((frequency >800) && (frequency <=900)) {correction = -2.20;}
    if ((frequency >900) && (frequency <=1000)) {correction = -2.35;}
    if ((frequency >1000) && (frequency <=1100)) {correction = -2.40;}
    if ((frequency >1100) && (frequency <=1200)) {correction = -2.50;}
    if ((frequency >1200) && (frequency <=1300)) {correction = -2.50;}
    if ((frequency >1300) && (frequency <=1400)) {correction = -2.50;}
    if ((frequency >1400) && (frequency <=1500)) {correction = -2.45;}
    if ((frequency >1500) && (frequency <=1600)) {correction = -2.40;}  
}
