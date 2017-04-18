const int minDegrees = 2; // min degrees needed for a movement, from testing
const int degInc = 12; // degrees per iteration (resolution, of sorts - 12 is good)
const float incRpm = (1400 - 250) / 600; // (max Rpm - initial Rpm) / ref degrees disp, from testing)


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
  Serial.println(counter);
  counter=0;
  while (digitalRead(LEFTSTOP) == HIGH) {
    left(minDegrees);
    counter=counter+minDegrees;
  }
  Serial.println(counter);
}

void centre(){
  bounce();
//  right(counter/2);
}

void zero() {
  setRpm(120);
  while (digitalRead(LEFTSTOP) == HIGH) {
    stepper.rotate(-minDegrees);
  }
}

void wake() {
  digitalWrite(SLEEP, HIGH);
  delay(1);
}

void sleep() {
  digitalWrite(SLEEP, LOW);
  delay(1);
}

void setRpm(int r) {
  rpm = r;
  stepper.setRPM(r);
}

