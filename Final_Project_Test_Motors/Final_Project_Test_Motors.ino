#include "Arduino.h"
#include "driver/ledc.h"

#define MOTOR_PIN_FORWARD 26  // Change this to any suitable GPIO
#define MOTOR_PIN_BACKWARD 27
//Inputs
#define JOYSTICK_X 32
#define JOYSTICK_Y 33



void setup() {
    Serial.begin(115200);
    pinMode(MOTOR_PIN_FORWARD, OUTPUT);
    pinMode(MOTOR_PIN_BACKWARD, OUTPUT);
    pinMode(JOYSTICK_X, INPUT);
    pinMode(JOYSTICK_Y, INPUT);

    Serial.println("ESP32 Motor PWM Control Initialized!");
}

void loop() {
  int xPosition = analogRead(JOYSTICK_X);
  int yPosition = analogRead(JOYSTICK_Y);

  Serial.println("X-Value: " + String(xPosition));
  Serial.println("Y-Value: " + String(yPosition));
  delay(2000);
}