#include "LSLib.h"

// Priavte Functions and Variables
namespace
{
    const byte knobPin = A5;       // Potentiometer is connected to Pin A5 on the Arduino
    const byte switchPin = A4;     // ON/OFF Switch is connected to Pin A4 on the Arduino
    const int maxKnobValue = 1023; // The Analog to Digital converter maps the analog voltages (0-5V) into 1024 (0-1023) values

    // Define the minimum and maximum brightness values
    const int MIN_BRIGHTNESS = 0;
    const int MAX_BRIGHTNESS = 150;

    // Calculate the duration of each step in microseconds
    unsigned long stepDuration = 1000UL;

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

    void changeState()
    {
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
}

States state = off;

int knobValue = 0;

void setupLightSculpture()
{
    for (int pin = 2; pin < 16; pin++)
    {
        pinMode(pin, OUTPUT);
    }

    pinMode(knobPin, INPUT_PULLUP);
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
    if (analogRead(knobPin) > (knobPin + 4) || analogRead(knobPin) < (knobPin - 4))
    {
        state = changing;
    }

    knobValue = analogRead(knobPin);

    changeState();

    // Serial.println(state);
    // Serial.println(knobValue);
}

void fadeUp(int ledPin, int fadeDuration)
{
    // Loop through all the steps
    for (int i = 0; i < fadeDuration; i++)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

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
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Calculate the current brightness value
        // int brightness = (i - 0) * (MAX_BRIGHTNESS - MIN_BRIGHTNESS);
        int brightness = map(i, 0, fadeDuration, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / MAX_BRIGHTNESS;
        unsigned long offTime = stepDuration - onTime;

        Serial.println(offTime);

        privateTurnOnAll();
        delayMicroseconds(onTime);
        privateTurnOffAll();
        delayMicroseconds(offTime);
    }

    //     long map(long x, long in_min, long in_max, long out_min, long out_max)
    // {
    //   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    // }

    privateTurnOnAll();
}

void fadeUpAllSpecific(int startPin, int endPin, int fadeDuration)
{
    // Loop through all the steps
    for (int i = 0; i < fadeDuration; i++)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

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
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Set the brightness of all the LEDs in the array using the fadeLED function
        fadeUp(ledPins[i], fadeDuration);
    }
}

void fadeDown(int ledPin, int fadeDuration)
{
    // Loop through all the steps
    for (int i = MAX_BRIGHTNESS; i >= MIN_BRIGHTNESS; i--)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

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
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }

        // Calculate the current brightness value
        int brightness = map(i, MIN_BRIGHTNESS, MAX_BRIGHTNESS, 0, fadeDuration);

        // Set the LED brightness using a timer-based approach
        unsigned long onTime = (unsigned long)brightness * stepDuration / fadeDuration;
        unsigned long offTime = stepDuration - onTime;

        privateTurnOnAll();
        delayMicroseconds(onTime);
        privateTurnOffAll();
        delayMicroseconds(offTime);
    }

    privateTurnOffAll();
}

void fadeDownArray(int ledPins[], int numPins, int fadeDuration)
{
    // Loop through all the steps
    for (int i = 0; i < numPins; i++)
    {
        updateMode();
        if (state == changing || state == off)
        {
            return;
        }
        fadeDown(ledPins[i], fadeDuration);
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
        if (state == changing || state == off)
        {
            return;
        }

        digitalWrite(ledNum, LOW);
    }
}