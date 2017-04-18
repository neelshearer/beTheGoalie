#include <Arduino.h>
#include "BasicStepperDriver.h"
#define MOTOR_STEPS 200
#define SLEEP 7
#define DIR 8
#define STEP 9
#define RIGHTSTOP 6
#define LEFTSTOP 5

// Since microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

int rpm = 250; // default initial rpm
int counter=0;

void setup() {
  stepper.setRPM(rpm);
  pinMode(RIGHTSTOP, INPUT_PULLUP);
  pinMode(LEFTSTOP, INPUT_PULLUP);
  pinMode(SLEEP, OUTPUT);
  sleep();
  Serial.begin(9600);
  wake();
  centre();
  sleep();
}

void loop() {
wake();
rightAccel(counter);
sleep();
delay(1000);
wake();
leftAccel(counter);
sleep();
delay(1000);
  
//  Serial.println(digitalRead(LEFTSTOP));
//  Serial.println(digitalRead(RIGHTSTOP));
//
//  wake();
//  stepper.setMicrostep(MICROSTEPS);
//  stepper.rotate(360);
//  stepper.move(-200 * MICROSTEPS);
//  sleep();
//  delay(5000);

//  wake();
//  bounce();
//  sleep();
//  delay(5000);

  //  wake();
  //  rightAccel(1800);
  //  sleep();
  //  delay(1000);
  //  wake();
  //  leftAccel(1800);
  //  sleep();
  //  delay(1000);
}

