#include "Arduino.h"
#include "driver/ledc.h"

//Motor 1 
#define MOTOR1_Speed 12  
#define MOTOR_PIN_FORWARD 27  
#define MOTOR_PIN_BACKWARD 14
#define MOTOR_Speed_Channel 0

//Motor 2
#define MOTOR2_Speed 33  
#define MOTOR2_PIN_FORWARD 25  
#define MOTOR2_PIN_BACKWARD 26
#define MOTOR2_Speed_Channel 1

//Inputs
#define JOYSTICK_X 32
#define JOYSTICK_Y 35

#define PWM_FREQ 5000
#define PWM_RESOLUTION 8

void setup() {
    Serial.begin(115200);
    pinMode(JOYSTICK_X, INPUT);
    pinMode(JOYSTICK_Y, INPUT);

    //Motor 1 Pin Setup
    pinMode(MOTOR_PIN_FORWARD, OUTPUT);
    pinMode(MOTOR_PIN_BACKWARD, OUTPUT);
    //PWM Speed Control for Motor 2
    if (ledcAttachChannel(MOTOR1_Speed, PWM_FREQ, PWM_RESOLUTION, MOTOR_Speed_Channel) == false){
      Serial.println("The PWM did not get set up");
    }
    else{
      Serial.println("The Forward is good");
    }

    //Motor 2 Pin Setup
    pinMode(MOTOR2_PIN_FORWARD, OUTPUT);
    pinMode(MOTOR2_PIN_BACKWARD, OUTPUT);
    //PWM Speed Control for Motor 2
    if (ledcAttachChannel(MOTOR2_Speed, PWM_FREQ, PWM_RESOLUTION, MOTOR_Speed_Channel) == false){
      Serial.println("The PWM did not get set up");
    }
    else{
      Serial.println("The Forward is good");
    }
}

void loop() {
  int xPosition = analogRead(JOYSTICK_X);
  int yPosition = analogRead(JOYSTICK_Y);
  //Serial.println("xPosition: " + String(xPosition));
  //Serial.println("yPosition: " + String(yPosition));

  int Speed = map(xPosition, 0, 4095, -255, 255); //Setting up range to work with pwm output
  int AbsSpeed = abs(Speed); //Converting the speed to an absolute value for easier motor control
  Serial.println("xSpeed: " + String(Speed));
  //Serial.println("AbsSpeed: " + String(AbsSpeed));

  int ySpeed = map(yPosition, 0, 4095, -255, 255); //Setting up range to work with pwm output
  int yAbsSpeed = abs(ySpeed); //Converting the speed to an absolute value for easier motor control
  Serial.println("ySpeed: " + String(ySpeed));
  //Serial.println("AbsSpeed: " + String(yAbsSpeed));

  if (Speed >= 36 and ySpeed >= -40 and ySpeed <= 40){ //The and ySpeed >= -35 and ySpeed <= 35 is no left or right movement
    Serial.println("Move Forward");
    //Outputs for Motor 1
    ledcWriteChannel(MOTOR_Speed_Channel, AbsSpeed); //PWM to adjust speed of motors
    digitalWrite(MOTOR_PIN_FORWARD, HIGH);
    digitalWrite(MOTOR_PIN_BACKWARD, LOW);

    //Outputs for Motor 2
    ledcWriteChannel(MOTOR2_Speed_Channel, AbsSpeed);
    digitalWrite(MOTOR2_PIN_FORWARD, HIGH);
    digitalWrite(MOTOR2_PIN_BACKWARD, LOW);
  }
  else if (Speed <= -36 and ySpeed >= -40 and ySpeed <= 40){
    Serial.println("Move Backward");
    //Outputs for Motor 1
    ledcWriteChannel(MOTOR_Speed_Channel, AbsSpeed); //PWM to adjust speed of motors
    digitalWrite(MOTOR_PIN_FORWARD, LOW);
    digitalWrite(MOTOR_PIN_BACKWARD, HIGH);

    //Outputs for Motor 2
    ledcWriteChannel(MOTOR2_Speed_Channel, AbsSpeed);
    digitalWrite(MOTOR2_PIN_FORWARD, LOW);
    digitalWrite(MOTOR2_PIN_BACKWARD, HIGH);
  }
  else if (Speed >= -35 and Speed <= 35 and ySpeed >= -35 and ySpeed <= 35){
    Serial.println("Stop");
    //Outputs for Motor 1
    ledcWriteChannel(MOTOR_Speed_Channel, 0); //PWM to adjust speed of motors
    digitalWrite(MOTOR_PIN_FORWARD, LOW);
    digitalWrite(MOTOR_PIN_BACKWARD, LOW);

    //Outputs for Motor 2
    ledcWriteChannel(MOTOR2_Speed_Channel, 0);
    digitalWrite(MOTOR2_PIN_FORWARD, LOW);
    digitalWrite(MOTOR2_PIN_BACKWARD, LOW);
  }
  else if (ySpeed >= 36 and Speed >= -40 and Speed <= 40){ 
    Serial.println("Move Right");
    //Outputs for Motor 1
    ledcWriteChannel(MOTOR_Speed_Channel, yAbsSpeed); //PWM to adjust speed of motors
    digitalWrite(MOTOR_PIN_FORWARD, HIGH);
    digitalWrite(MOTOR_PIN_BACKWARD, LOW);

    //Outputs for Motor 2
    ledcWriteChannel(MOTOR2_Speed_Channel, yAbsSpeed);
    digitalWrite(MOTOR2_PIN_FORWARD, LOW);
    digitalWrite(MOTOR2_PIN_BACKWARD, HIGH);
  }
  else if (ySpeed <= -36 and Speed >= -40 and Speed <= 40){ 
    Serial.println("Move Left");
    //Outputs for Motor 1
    ledcWriteChannel(MOTOR_Speed_Channel, yAbsSpeed); //PWM to adjust speed of motors
    digitalWrite(MOTOR_PIN_FORWARD, LOW);
    digitalWrite(MOTOR_PIN_BACKWARD, HIGH);

    //Outputs for Motor 2
    ledcWriteChannel(MOTOR2_Speed_Channel, yAbsSpeed);
    digitalWrite(MOTOR2_PIN_FORWARD, HIGH);
    digitalWrite(MOTOR2_PIN_BACKWARD, LOW);
  }
  

  delay(100);
}