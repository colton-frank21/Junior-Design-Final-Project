#include "Arduino.h"
#include "driver/ledc.h"

#define MOTOR_PIN 26  // Change this to any suitable GPIO
#define Button_PIN 5
#define Output_PIN 18



void setup() {
    Serial.begin(115200);
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(Button_PIN, INPUT);
    pinMode(Output_PIN, OUTPUT);

    Serial.println("ESP32 Motor PWM Control Initialized!");
}

void loop() {
  digitalWrite(Output_PIN, HIGH);

  if (digitalRead(Button_PIN) == HIGH){
    Serial.println("Motor Speed: ON");
    digitalWrite(MOTOR_PIN, HIGH);
    Serial.println("Input = " + String(digitalRead(Button_PIN)));
    Serial.println("Output = " + String(ledcRead(MOTOR_PIN))); 
  }
  else if (digitalRead(Button_PIN) == LOW){
    Serial.println("Motor Speed: off");
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("Input = " + String(digitalRead(Button_PIN)));
    Serial.println("Output = " + String(ledcRead(MOTOR_PIN)));
  }
}