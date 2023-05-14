#include "LSLib.h"

const byte knobPin = A5;       // Potentiometer is connected to Pin A5 on the Arduino
const byte switchPin = A4;     // ON/OFF Switch is connected to Pin A4 on the Arduino
const int maxKnobValue = 1023; // The Analog to Digital converter maps the analog voltages (0-5V) into 1024 (0-1023) values

// Define the minimum and maximum brightness values
const int MIN_BRIGHTNESS = 0;
const int MAX_BRIGHTNESS = 255;

// Calculate the duration of each step in microseconds
unsigned long stepDuration = 1 * 1000UL;

void setupLightSculpture()
{
    for (int pin = 2; pin < 16; pin++)
    {
        pinMode(pin, OUTPUT);
    }

    pinMode(knobPin, INPUT_PULLUP);
    pinMode(switchPin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(knobPin), changed, CHANGE);

    Serial.begin(115200);
}

boolean getSwitchValue()
{
    return digitalRead(switchPin);
}

int getKnobValue()
{
    return analogRead(knobPin);
}

void fadeUp(int ledPin, int fadeDuration)
{
    // Loop through all the steps
    for (int i = 0; i < fadeDuration; i++)
    {

        // Calculate the current brightness value
        int brightness = map(i, 0, fadeDuration, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / MAX_BRIGHTNESS;
        unsigned long offTime = stepDuration - onTime;
        digitalWrite(ledPin, HIGH);
        delayMicroseconds(onTime);
        digitalWrite(ledPin, LOW);
        delayMicroseconds(offTime);
    }

    digitalWrite(ledPin, HIGH);
}

void fadeUpAll(int fadeDuration)
{
    // Loop through all the steps
    for (int i = 0; i < fadeDuration; i++)
    {

        // Calculate the current brightness value
        int brightness = map(i, 0, fadeDuration, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / MAX_BRIGHTNESS;
        unsigned long offTime = stepDuration - onTime;

        turnOnAll();
        delayMicroseconds(onTime);
        turnOffAll();
        delayMicroseconds(offTime);
    }

    turnOnAll();
}

void fadeUpAllSpecific(int startPin, int endPin, int fadeDuration)
{
    // Loop through all the steps
    for (int i = 0; i < fadeDuration; i++)
    {

        // Calculate the current brightness value
        int brightness = map(i, 0, fadeDuration, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

        // Loop through all the LED pins
        // for (int pin = startPin; pin <= endPin; pin++)
        // {
        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / MAX_BRIGHTNESS;
        unsigned long offTime = stepDuration - onTime;
        // digitalWrite(pin, HIGH);
        turnOnAll();
        delayMicroseconds(onTime);
        // digitalWrite(pin, LOW);
        turnOffAll();
        delayMicroseconds(offTime);
        // }
    }

    turnOnAll();
}

void fadeUpArray(int ledPins[], int numPins, int fadeDuration)
{
    // Loop through all the steps
    for (int i = 0; i < numPins; i++)
    {

        // Set the brightness of all the LEDs in the array using the fadeLED function
        fadeUp(ledPins[i], fadeDuration);
    }
}

void fadeDown(int ledPin, int fadeDuration)
{
    // Loop through all the steps
    for (int i = MAX_BRIGHTNESS; i >= MIN_BRIGHTNESS; i--)
    {

        // Calculate the current brightness value
        int brightness = map(i, MIN_BRIGHTNESS, MAX_BRIGHTNESS, 0, fadeDuration);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / fadeDuration;
        unsigned long offTime = stepDuration - onTime;
        digitalWrite(ledPin, HIGH);
        delayMicroseconds(onTime);
        digitalWrite(ledPin, LOW);
        delayMicroseconds(offTime);
    }

    digitalWrite(ledPin, LOW);
}

void fadeDownAll(int fadeDuration)
{

    // Loop through all the steps
    for (int i = MAX_BRIGHTNESS; i >= MIN_BRIGHTNESS; i--)
    {

        // Calculate the current brightness value
        int brightness = map(i, MIN_BRIGHTNESS, MAX_BRIGHTNESS, 0, fadeDuration);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / fadeDuration;
        unsigned long offTime = stepDuration - onTime;
        turnOnAll();
        delayMicroseconds(onTime);
        turnOffAll();
        delayMicroseconds(offTime);
    }

    turnOffAll();
}

void fadeDownArray(int ledPins[], int numPins, int fadeDuration)
{
    // Loop through all the steps
    for (int i = 0; i < numPins; i++)
    {

        fadeDown(ledPins[i], fadeDuration);
    }
}

void turnOnAll()
{
    for (int ledNum = 2; ledNum <= 15; ledNum++)
    {

        digitalWrite(ledNum, HIGH);
    }
}

void turnOffAll()
{
    for (int ledNum = 2; ledNum <= 15; ledNum++)
    {

        digitalWrite(ledNum, LOW);
    }
}