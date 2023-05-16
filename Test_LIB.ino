#include "Arduino.h"
#include "LSLib.h"

void setup()
{
  setupLightSculpture();
}

int myLEDPins[] = {11, 12, 13, 14}; // Array of LED pins
int myNumPins = 3;                  // Number of LED pins in the array
int myFadeDuration = 500;           // 5 seconds

void loop()
{
  if (getSwitchValue())
  {
    turnOffAll();
  }
  else if (state == calm)
  {
    // state = calm;
    calmMode();
  }
  // else if (knobValue > 341 && knobValue <= 682)
  else if (state == party)
  {
    // state = party;
    partyMode();
  }
  // else if (knobValue > 682 && knobValue <= 1023)
  else if (state == lamp)
  {
    // state = lamp;
    turnOnAll();
  }
}

void calmMode()
{
  fadeUpAll(myFadeDuration);
  delay(1000);
  fadeDownAll(myFadeDuration);
  delay(1000);
  fadeUp(4, myFadeDuration);
  delay(1000);
  fadeDown(4, myFadeDuration);
  delay(1000);
  fadeUpArray(myLEDPins, sizeof(myLEDPins), myFadeDuration);
  delay(1000);
  fadeDownArray(myLEDPins, sizeof(myLEDPins), myFadeDuration);
  delay(1000);
}

void partyMode()
{
  turnOnAll();
  delay(250);
  turnOffAll();
  delay(250);
}