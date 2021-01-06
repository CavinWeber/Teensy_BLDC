#include <Arduino.h>
#include <main.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float sensorVal;

bool alreadyTriggered;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(1,0);
  display.setTextSize(2);
  display.println("Testing!");
  display.display();
  alreadyTriggered = false;
  sensorVal = 0;
}

void loop() {
  sensorVal = analogRead(A17);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(sensorVal);
  display.display();
  // motor.stopMotor();
  if (sensorVal < 200){
    if (!alreadyTriggered){
      alreadyTriggered = true;
      motor.turnCounterclockwise();
    }
  }
  else
  {
    alreadyTriggered = false;
  }
  // delay(300);
  
  /*
  spin1Analog(200);
  delay(80);
  stopSpin();
  delay(1000);
  spin2Analog(200);
  delay(80);
  stopSpin();
  delay(1000);
  */
}


/*
void spin1(){
  digitalWrite(A_EN, HIGH);
  digitalWrite(A_IN, HIGH);
  digitalWrite(B_EN, HIGH);
  digitalWrite(B_IN, LOW);
}

void spin2(){
  digitalWrite(B_EN, HIGH);
  digitalWrite(B_IN, HIGH);
  digitalWrite(A_EN, HIGH);
  digitalWrite(A_IN, LOW);
}


void spin1Analog(int s){
  digitalWrite(A_EN, HIGH);
  analogWrite(A_IN, s);
  digitalWrite(B_EN, HIGH);
  digitalWrite(B_IN, LOW);
  analogWrite(B_IN, LOW);
}

void spin2Analog(int s){
  digitalWrite(B_EN, HIGH);
  analogWrite(B_IN, s);
  digitalWrite(A_EN, HIGH);
  digitalWrite(A_IN, LOW);
  analogWrite(A_IN, LOW);
}

void stopSpin(){
  digitalWrite(B_EN, LOW);
  digitalWrite(B_IN, LOW);
  digitalWrite(A_EN, LOW);
  digitalWrite(A_IN, LOW);
  analogWrite(A_IN, LOW);
  analogWrite(B_IN, LOW);
}
*/