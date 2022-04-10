#pragma once

#include <BLDC_Motor.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Timer.h>

#define TRIGGER_PIN 27

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define A_EN 7
#define B_EN 8
#define C_EN 9
#define A_IN 10
#define B_IN 11
#define C_IN 12

BLDC_Motor motor = BLDC_Motor(7,8,9,10,11,12);
Timer interruptDebounce = Timer(4);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float sensorVal;

float inputVal;

bool alreadyTriggered;

/** Triggers a short pulse for oscilloscope debugging
 */
void triggerPin();

void incrementMotor();