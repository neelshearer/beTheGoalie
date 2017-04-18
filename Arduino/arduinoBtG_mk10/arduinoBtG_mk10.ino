#include <Arduino.h>
#include "BasicStepperDriver.h"

boolean master = false;
const int changeOverDuration = 30; // in secs
const int gameDuration = 180; // in secs

#define MOTOR_STEPS 200
#define SLEEP 7
#define DIR 8
#define STEP 9
#define RIGHTSTOP 6
#define LEFTSTOP 5
const byte interruptPin = 2;  // goal sensor
#define kickoffReceive 3
#define fulltimeReceive 4
#define kickButton 10
#define kickoffSend 11
#define fulltimeSend 12
#define relayPin 13

// Since microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

int rpm = 300; // default initial rpm [a4988=250, drv8825=300]
int diff = 0;         // difference
int inByte = 0;         // incoming serial byte
float lastXReceive = 0;         // last movement instruction
int moveThreshold = 44; // min degrees needed to trigger a movement
unsigned long lastMarker = 0;  // time of last timer event
boolean changeOver = true;  // whether currently in changeover period
boolean kickoff = false;  // whether a kickoff signal is currently being sensed
boolean fulltime = false;  // whether a fulltime signal is currently being sensed
long lastKick = 0;  // time of last kick
boolean goalState = false;  // whether a goal is currently being sensed

void setup() {
  stepper.setRPM(rpm);
  pinMode(RIGHTSTOP, INPUT_PULLUP);
  pinMode(LEFTSTOP, INPUT_PULLUP);
  pinMode(SLEEP, OUTPUT);
  sleep2();
  pinMode(kickoffReceive, INPUT_PULLUP);
  pinMode(fulltimeReceive, INPUT_PULLUP);
  pinMode(kickoffSend, OUTPUT);
  digitalWrite(kickoffSend, HIGH);
  pinMode(fulltimeSend, OUTPUT);
  digitalWrite(fulltimeSend, HIGH);
  digitalWrite(relayPin, HIGH);
  pinMode(interruptPin, INPUT);
  pinMode(kickButton, INPUT_PULLUP);
  serialSetup();
  wake();
  bounce();
  sleep2();
  //  attachInterrupt(digitalPinToInterrupt(interruptPin), goal, RISING); //digitalPinToInterrupt(interruptPin)

}

void loop() {
//  Serial.println(millis());
  movementLoop();
  serialLoop2();
  delay(10);
  timeCheck();
  kickButtonCheck();
  if (changeOver == false) {
    goalCheck();
  }
}

void kickButtonCheck() {
  //  Serial.println(millis());
  if (!digitalRead(kickButton)) { // if kick button is pressed (pin goes low)
    if ((millis() - lastKick) > 500) { // if its longer thaan 0.5s since last kick
      kickRoutine();
    }
  }
}

void goalCheck() {
  //  Serial.println(goalState);
  //  Serial.println(digitalRead(interruptPin));
  if (goalState == false) {
    if (digitalRead(interruptPin) == HIGH) {
      delay(100);
      if (digitalRead(interruptPin) == HIGH) {
        Serial.println("g");  // send goal
        delay(10);
        goalState = true;
      }
    }
  }
  if (goalState == true) {
    if (digitalRead(interruptPin) == LOW) {
      goalState = false;
    }
  }
}

//long lastGoalTime;

//void goal() {
//  //  Serial.println("interrupt");
//  if (changeOver == false) {
//    long goalTime = millis();
//    //check to see if there was a goal in the last 1000 milliseconds
//    if (goalTime - lastGoalTime > 1000)
//    {
//      if (goalTime - lastKick > 200) {  // check if there was a kick in the last 200 milliseconds
//        //        delayMicroseconds(100000);
//        //        if (digitalRead(interruptPin)) {  // if
//        Serial.println("g");  // send goal
//        delayMicroseconds(10000);
//        //        }
//      }
//      lastGoalTime = goalTime;
//    }
//  }
//}


