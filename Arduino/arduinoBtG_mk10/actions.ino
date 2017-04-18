const int minDegrees = 2; // 2, min degrees needed for a movement, from testing
const int degInc = 12; // degrees per iteration (resolution, of sorts - 12 is good)
const float incRpm = 1.1; //[a4988=0.8, drv8825=1.5] or (1000 - 250) / 600; // (max Rpm [1600] - initial Rpm[320]) / ref degrees disp[600], from testing)
//const int maxTravel = 300; //in mm
//const float degreesPermm = 7.5; // 5.341 or 10

int counter=0;

void movementLoop() {
  if (inByte == 255) {
    kickRoutine();
    inByte=lastXReceive;  //  meant to stop the goalie repeatedly kicking
  }
  else
  {
    float xReceive = map(inByte, 0, 254, 0, counter);
    diff = xReceive - lastXReceive;
    if (diff % 2 != 0) {
      diff = diff - 1;
    }
    if (diff > moveThreshold || diff < -moveThreshold) {
//      Serial.println(diff);
      wake();
      if (diff >= 300) {
//        Serial.println("rightAccel");
        rightAccel(diff);
      }
      else if (1 < diff && diff < 300) {
//        Serial.println("right");
        setRpm(250);
        right(diff);
      }
      else if (diff <= -300) {
//        Serial.println("leftAccel");
        leftAccel(-diff);
      }
      else if (-1 > diff && diff > -300) {
//        Serial.println("left");
        setRpm(250);
        left(-diff);
      }
      //    Serial.println(diff);
      sleep2();
      lastXReceive = xReceive;
    }
  }
}

void kickRoutine() {
  //  Serial.println("KICK");
//  detachInterrupt(digitalPinToInterrupt(interruptPin));
  lastKick=millis();
  digitalWrite(relayPin, LOW);
  delay(200);
  digitalWrite(relayPin, HIGH);
//  delay(1000);
//  attachInterrupt(digitalPinToInterrupt(interruptPin), goal, RISING);
}

void rightAccel(int rightDeg) {
  setRpm(250);
  int sustain = max(0, rightDeg - 1200);
  int rampUp = (rightDeg - sustain) / 2;
  int rampDown = (rightDeg - sustain) / 2;
  for (int i = 0; i < (rampUp / degInc); i++) {
    setRpm(rpm);
    right(degInc);
    rpm = rpm + (incRpm * degInc);
  }
  for (int i = 0; i < (sustain / degInc); i++) {
    setRpm(rpm);
    right(degInc);
  }
  for (int i = 0; i < (rampDown / degInc); i++) {
    setRpm(rpm);
    right(degInc);
    rpm = rpm - (incRpm * degInc);
  }
}

void leftAccel(int leftDeg) {
  setRpm(250);
  int sustain = max(0, leftDeg - 1200);
  int rampUp = (leftDeg - sustain) / 2;
  int rampDown = (leftDeg - sustain) / 2;
  for (int i = 0; i < (rampUp / degInc); i++) {
    setRpm(rpm);
    left(degInc);
    rpm = rpm + (incRpm * degInc);
  }
  for (int i = 0; i < (sustain / degInc); i++) {
    setRpm(rpm);
    left(degInc);
  }
  for (int i = 0; i < (rampDown / degInc); i++) {
    setRpm(rpm);
    left(degInc);
    rpm = rpm - (incRpm * degInc);
  }
}

void right(int xDeg) {
  for (int i = 0; i < xDeg; i = i + minDegrees) {
    if (digitalRead(RIGHTSTOP) == LOW) {
      break;
    }
    stepper.rotate(minDegrees);
  }
}

void left(int xDeg) {
  for (int i = 0; i < xDeg; i = i + minDegrees) {
    if (digitalRead(LEFTSTOP) == LOW) {
      break;
    }
    stepper.rotate(-minDegrees);
  }
}


void bounce() {
  while (digitalRead(RIGHTSTOP) == HIGH) {
    right(minDegrees);
    counter=counter+minDegrees;
  }
  counter=0;
  while (digitalRead(LEFTSTOP) == HIGH) {
    left(minDegrees);
    counter=counter+minDegrees;
  }
  Serial.println(counter);
}

void centre(){
  bounce();
  right(counter/2);
}

void sleep2() {
  digitalWrite(SLEEP, LOW);
  delay(1);
}

void wake() {
  digitalWrite(SLEEP, HIGH);
  delay(1);
}

void zero() {
  setRpm(120);
  while (digitalRead(LEFTSTOP) == HIGH) {
    stepper.rotate(-minDegrees);
  }
  right(53);
}

void setRpm(int r) {
  rpm = r;
  stepper.setRPM(r);
}



