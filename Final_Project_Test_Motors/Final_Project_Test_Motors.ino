#include "Arduino.h"
#include "driver/ledc.h"

//Motor 1 
#define MOTOR_PIN_FORWARD 26  
#define MOTOR_PIN_BACKWARD 27
#define Forward_Channel 0
#define Backward_Channel 1
//Motor 2
#define MOTOR2_PIN_FORWARD 14  
#define MOTOR2_PIN_BACKWARD 12
#define Forward2_Channel 2
#define Backward2_Channel 3
//Inputs
#define JOYSTICK_X 32
#define JOYSTICK_Y 33

#define PWM_FREQ 5000
#define PWM_RESOLUTION 8

void setup() {
    Serial.begin(115200);
    pinMode(JOYSTICK_X, INPUT);
    pinMode(JOYSTICK_Y, INPUT);

    //Forward motor 1
    if (ledcAttachChannel(MOTOR_PIN_FORWARD, PWM_FREQ, PWM_RESOLUTION, Forward_Channel) == false){
      Serial.println("The PWM did not get set up");
    }
    else{
      Serial.println("The Forward is good");
    }
    //Backward motor 1
    if (ledcAttachChannel(MOTOR_PIN_BACKWARD, PWM_FREQ, PWM_RESOLUTION, Backward_Channel) == false){
      Serial.println("The PWM did not get set up");
    }
    else{
      Serial.println("The Backward is good");
    }

    //Forwad motor 2
    if (ledcAttachChannel(MOTOR2_PIN_FORWARD, PWM_FREQ, PWM_RESOLUTION, Forward2_Channel) == false){
      Serial.println("The PWM did not get set up");
    }
    else{
      Serial.println("The Forward2 is good");
    }
    //Backward motor 2 
    if (ledcAttachChannel(MOTOR2_PIN_BACKWARD, PWM_FREQ, PWM_RESOLUTION, Backward2_Channel) ==s false){
      Serial.println("The PWM did not get set up");
    }
    else{
      Serial.println("The Backward2 is good");
    }
}

void loop() {
  int xPosition = analogRead(JOYSTICK_X);
  int yPosition = analogRead(JOYSTICK_Y);
  //Serial.println("xPosition: " + String(xPosition));
  //Serial.println("yPosition: " + String(yPosition));

  int Speed = map(xPosition, 0, 4095, -255, 255); //Setting up range to work with pwm output
  int AbsSpeed = abs(Speed); //Converting the speed to an absolute value for easier motor control
  Serial.println("Speed: " + String(Speed));
  Serial.println("AbsSpeed: " + String(AbsSpeed));

  if (Speed >= 36){
    Serial.println("Move Forward");
    ledcWriteChannel(Forward_Channel, AbsSpeed);
    ledcWriteChannel(Backward_Channel, 0);
    ledcWriteChannel(Forward2_Channel, AbsSpeed);
    ledcWriteChannel(Backward2_Channel, 0);
  }
  else if (Speed <= -36){
    Serial.println("Move Backward");
    ledcWriteChannel(Forward_Channel, 0);
    ledcWriteChannel(Backward_Channel, AbsSpeed);
    ledcWriteChannel(Forward2_Channel, 0);
    ledcWriteChannel(Backward2_Channel, AbsSpeed);
  }
  else if (Speed >= -35 and Speed <= 35){
    Serial.println("Stop");
    ledcWriteChannel(Forward_Channel, 0);
    ledcWriteChannel(Backward_Channel, 0);
    ledcWriteChannel(Forward2_Channel, 0);
    ledcWriteChannel(Backward2_Channel, 0);
  }

  delay(100);
}