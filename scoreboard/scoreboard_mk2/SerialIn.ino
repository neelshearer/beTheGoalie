String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void serialSetup() {

  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void serialCheck() {
  // print the string when a newline arrives:
  if (stringComplete) {
    //    Serial.println(inputString);
    String key = inputString;
    //    Serial.println(key);
    if (key.equals("t\n")) {
      test();
    }
    if (key.equals("g\n")) {
      goalScroll(3);
    }
    if (key.equals("h\n")) {
      goalZoom();
    }
    if (key.equals("b\n")) {
      black();
    }
    if (key.equals("y\n")) {
      yellow();
    }
    if (key.equals("f\n")) {
      fullTime();
    }
    if (key.equals("k\n")) {
//      Serial.println("YES");
      kickOff();
    }
    if (key.equals("s\n")) {
      score++;
    }
    if (key.equals("c\n")) {
      changeOver();
    }
    // clear the string:
    inputString = "";
    key = ' ';
    stringComplete = false;
  }

}

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
