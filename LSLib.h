#pragma once

#include <Arduino.h>

void setupLightSculpture();
boolean getSwitchValue();
int getKnobValue();

void updateMode();
void setChangedFalse();

/*All Fade Up Function*/
void fadeUp(int ledPin, int fadeDuration);
void fadeUpAll(int fadeDuration);
void fadeUpArray(int ledPins[], int numPins, int fadeDuration);

/*All Fade Down Function*/
void fadeDown(int ledPin, int fadeDuration);
void fadeDownAll(int fadeDuration);
void fadeDownArray(int ledPins[], int numPins, int fadeDuration);

void turnOnAll();
void turnOffAll();