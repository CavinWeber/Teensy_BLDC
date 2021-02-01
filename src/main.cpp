#include <main.h>

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(TRIGGER_PIN, OUTPUT);
  delay(100);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(1,0);
  display.setTextSize(2);
  display.println("Testing!");
  // display.display();
  alreadyTriggered = false;
  sensorVal = 0;
  inputVal = 0;
  // analogReadAveraging(10);
  attachInterrupt(38, incrementMotor, CHANGE);
}

void loop() {
  sensorVal = analogRead(A17);
  inputVal = analogRead(A3);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(inputVal);
  display.display();

  motor.setPower(inputVal / 4);

  // motor.turnClockwise();
  // delay(500);
  // motor.stopMotor();
  // delay(500);
}

void incrementMotor()
{

    if (interruptDebounce.isTriggered())
  {
     triggerPin();
     motor.turnClockwise();
     interruptDebounce.reset();
  }

}

void triggerPin()
{

      digitalWriteFast(TRIGGER_PIN, HIGH);
      delayMicroseconds(1);
      digitalWriteFast(TRIGGER_PIN, LOW);
  

}


