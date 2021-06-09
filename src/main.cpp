/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "app.h"
#include "EngineTask.h"

#include "Wire.h"
#include "LiquidCrystal_I2C.h"


#define LED_PIN 2

F_USE_NAMESPACE

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
EngineTask* pEngineTask;

void setup()
{
    Serial.begin(115200);
    Wire.begin(26, 25);
    lcd.begin(16, 2);
    pinMode(LED_PIN, OUTPUT);

    pEngineTask = new EngineTask();
}

void loop()
{
    // Serial.println("Tick");
    // lcd.clear();
    // delay(300);

    // lcd.setCursor(0, 0);
    // lcd.print("Hello, on line 1!");

    digitalWrite(LED_PIN, 1);
    delay(300);

    // lcd.setCursor(0, 1);
    // lcd.print("Hello, on line 2!");

    digitalWrite(LED_PIN, 0);
    delay(300);
}