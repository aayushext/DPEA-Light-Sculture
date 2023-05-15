#ifndef LSLIB_H
#define LSLIB_H

#pragma once

#include <Arduino.h>

enum States
{
    off,
    changing,
    calm,
    party,
    lamp
};

extern States state;
extern int knobValue;

void setupLightSculpture();

bool getSwitchValue();

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

void updateMode();

#endif