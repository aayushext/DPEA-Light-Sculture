#include "Arduino.h"
#include "LSLib.h"

void setup()
{
  setupLightSculpture();
}

int myLEDPins[] = {11, 12, 13, 14}; // Array of LED pins
int myNumPins = 3;                  // Number of LED pins in the array
int myFadeDuration = 5000;          // 5 seconds

void loop()
{
  if (getSwitchValue())
  {
    turnOffAll();
  }
  else if (getKnobValue() <= 341)
  {
    calmMode();
  }
  else if (getKnobValue() > 341 && getKnobValue() <= 682)
  {
    partyMode();
  }
  else if (getKnobValue() > 682 && getKnobValue() <= 1023)
  {
    turnOnAll();
  }
}

void calmMode()
{
  fadeUpAll(2500);
  delay(1000);
  fadeDownAll(2500);
  delay(1000);
  fadeUp(4, myFadeDuration);
  delay(1000);
  fadeDown(4, myFadeDuration);
  delay(1000);
  fadeUpArray(myLEDPins, sizeof(myLEDPins), 1000);
  delay(1000);
  fadeDownArray(myLEDPins, sizeof(myLEDPins), 1000);
  delay(1000);
  setChangedFalse();
}

void partyMode()
{
  turnOnAll();
  delay(250);
  turnOffAll();
  delay(250);
}
