void timeCheck() {
  if (master == true) {  // only if in master mode
    timeCheckMaster();
  }
  else {  // else, in slave mode
    timeCheckSlave();
  }
}

void timeCheckMaster() {
  float diff = (millis() - lastMarker) / 1000 ; // measure time since last event
  if (changeOver == true) {  // if currently in changeOver
    if (diff > changeOverDuration) {  // and if time since last event exceeds threshold
      lastMarker = millis();  // reset event marker
      triggerKickoff();  // trigger kickoff routine
    }
  }
  else if (diff > gameDuration) {  // else if not currently in changeOver
    lastMarker = millis();  // reset event marker
    triggerFulltime();  // trigger fulltime routine
  }
}

void timeCheckSlave() {
  //  Serial.print(digitalRead(fulltimeReceive));
  //  Serial.println(digitalRead(kickoffReceive));
  if (!digitalRead(kickoffReceive)) {  // if kickoff pin is low
    if (kickoff == false) {  // and not already in kickoff state
      triggerKickoff();  // triger kickoff routine
      kickoff = true;  // set kickoff state to true
    }
  }
  else {  // else if kickoff pin is high
    kickoff = false;  // set kickoff state to false
  }
  if (!digitalRead(fulltimeReceive)) {  // if fulltime pin is low
    if (fulltime == false) { // and not already in fulltime state
      triggerFulltime();  // trigger fulltime routine
      fulltime = true;  // set fulltime state to true
    }
  }
  else {  // else if fulltime pin is high
    fulltime = false;  // set fulltime state to false
  }
}

void triggerKickoff() {
  delay(1000);  // dramatic pause
  Serial.println("k");  // trigger serial send
  if (master) {  // only if this is the master device
    digitalWrite(kickoffSend, LOW);  // send kickoff pin low
    delay(500);
    digitalWrite(kickoffSend, HIGH);
  }
  changeOver = false;  // set changeover state to false
}

void triggerFulltime() {
  Serial.println("f");  // trigger serial send
  if (master) {  // only if this is the master device
    digitalWrite(fulltimeSend, LOW);  // send fulltime pin low
    delay(500);
    digitalWrite(fulltimeSend, HIGH);
  }
  changeOver = true;  // set changeover state to true
  wake();
  bounce();  // reset goalies
  sleep2();
  delay(1000);  // dramatic pause
}

