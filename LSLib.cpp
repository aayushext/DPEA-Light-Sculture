#include "LSLib.h"

// Priavte Functions and Variables
namespace
{
    const byte knobPin = A5;       // Potentiometer is connected to Pin A5 on the Arduino
    const byte switchPin = A4;     // ON/OFF Switch is connected to Pin A4 on the Arduino
    const int maxKnobValue = 1023; // The Analog to Digital converter maps the analog voltages (0-5V) into 1024 (0-1023) values

    // Define the minimum and maximum brightness values
    const int MIN_BRIGHTNESS = 0;
    const int MAX_BRIGHTNESS = 256;

    // Define the number of steps between minimum and maximum brightness
    const int NUM_STEPS = 100;

    void privateTurnOnAll()
    {
        for (int ledNum = 2; ledNum <= 15; ledNum++)
        {
            digitalWrite(ledNum, HIGH);
        }
    }

    void privateTurnOffAll()
    {
        for (int ledNum = 2; ledNum <= 15; ledNum++)
        {
            digitalWrite(ledNum, LOW);
        }
    }
}

States state = off;

int knobValue = 0;

void setupLightSculpture()
{
    for (int pin = 2; pin < 16; pin++)
    {
        pinMode(pin, OUTPUT);
    }

    pinMode(knobPin, INPUT);
    pinMode(switchPin, INPUT_PULLUP);

    knobValue = analogRead(knobPin);

    Serial.begin(115200);
}

bool getSwitchValue()
{
    return digitalRead(switchPin);
}

void updateMode()
{
    if (analogRead(knobPin) > (knobValue + 5) || analogRead(knobPin) < (knobValue - 5))
    {
        state = changing;
    }

    knobValue = analogRead(knobPin);

    Serial.println(state);

    if (getSwitchValue())
    {
        state = off;
    }

    if (state == changing)
    {
        if (knobValue <= 341)
        {
            state = calm;
        }
        else if (knobValue > 341 && knobValue <= 682)
        {
            state = party;
        }
        else if (knobValue > 682 && knobValue <= 1023)
        {
            state = lamp;
        }
    }
}

void fadeUp(int ledPin, int fadeDuration)
{
    // Calculate the duration of each step in microseconds
    unsigned long stepDuration = fadeDuration * 1000UL / NUM_STEPS;

    // Loop through all the steps
    for (int i = 0; i < NUM_STEPS; i++)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Calculate the current brightness value
        int brightness = map(i, 0, NUM_STEPS, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

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
    // Calculate the duration of each step in microseconds
    unsigned long stepDuration = fadeDuration * 1000UL / NUM_STEPS;

    // Loop through all the steps
    for (int i = 0; i < NUM_STEPS; i++)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Calculate the current brightness value
        int brightness = map(i, 0, NUM_STEPS, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / MAX_BRIGHTNESS;
        unsigned long offTime = stepDuration - onTime;

        privateTurnOnAll();
        delayMicroseconds(onTime);
        privateTurnOffAll();
        delayMicroseconds(offTime);
    }

    privateTurnOnAll();
}

void crossfade(int upPin, int downPin, int fadeDuration)
{
    // Calculate the duration of each step in microseconds
    unsigned long stepDuration = fadeDuration * 1000UL / NUM_STEPS;

    digitalWrite(downPin, HIGH);

    // Loop through all the steps
    for (int i = 0; i < NUM_STEPS; i++)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Calculate the current brightness value
        int brightness = map(i, 0, NUM_STEPS, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / MAX_BRIGHTNESS;
        unsigned long offTime = stepDuration - onTime;

        digitalWrite(upPin, HIGH);
        digitalWrite(downPin, LOW);
        delayMicroseconds(onTime);
        digitalWrite(upPin, LOW);
        digitalWrite(downPin, HIGH);
        delayMicroseconds(offTime);
    }

    digitalWrite(upPin, HIGH);
    digitalWrite(downPin, LOW);
}

void fadeUpArray(int ledPins[], int numPins, int fadeDuration, int delayInBetween = 500)
{
    // Loop through all the steps
    for (int i = 0; i < numPins; i++)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Set the brightness of all the LEDs in the array using the fadeLED function
        fadeUp(ledPins[i], fadeDuration);
        delay(delayInBetween);
    }
}

void fadeDown(int ledPin, int fadeDuration)
{
    // Calculate the duration of each step in microseconds
    unsigned long stepDuration = fadeDuration * 1000UL / NUM_STEPS;

    // Loop through all the steps
    for (int i = NUM_STEPS - 1; i >= 0; i--)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Calculate the current brightness value
        int brightness = map(i, 0, NUM_STEPS, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / MAX_BRIGHTNESS;
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
    // Calculate the duration of each step in microseconds
    unsigned long stepDuration = fadeDuration * 1000UL / NUM_STEPS;

    // Loop through all the steps
    for (int i = NUM_STEPS - 1; i >= 0; i--)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Calculate the current brightness value
        int brightness = map(i, 0, NUM_STEPS, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / MAX_BRIGHTNESS;
        unsigned long offTime = stepDuration - onTime;

        privateTurnOnAll();
        delayMicroseconds(onTime);
        privateTurnOffAll();
        delayMicroseconds(offTime);
    }

    privateTurnOffAll();
}

void fadeDownArray(int ledPins[], int numPins, int fadeDuration, int delayInBetween = 500)
{
    // Loop through all the steps
    for (int i = 0; i < numPins; i++)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Set the brightness of all the LEDs in the array using the fadeLED function
        fadeDown(ledPins[i], fadeDuration);
        delay(delayInBetween);
    }
}

void turnOnAll()
{
    for (int ledNum = 2; ledNum <= 15; ledNum++)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        digitalWrite(ledNum, HIGH);
    }
}

void turnOffAll()
{
    for (int ledNum = 2; ledNum <= 15; ledNum++)
    {
        updateMode();
        if (state == changing)
        {
            return;
        }

        digitalWrite(ledNum, LOW);
    }
}
