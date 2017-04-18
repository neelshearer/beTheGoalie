String inputString="default";      // Data received from the serial port
// int val;  //if requiring an integer ultimately
String lastInputString="default";

void readRoutine() {
  lastInputString=inputString;  // update the memeory of the previous string
  if ( myPort.available() > 0) {  // If data is available,
    inputString = myPort.readStringUntil('\n');         // read it and store it in inputString
    if (inputString!=null) {  //if inputString contains data
      inputString=trim(inputString);  //trim it
      //     val=int(inputString); //converts numeric string to integer
      if (inputString.equals(lastInputString)) {
      } else { //and has not changed since the last time
        testRoutine(inputString);  // do the test routine
             println(inputString);
      }
    }
  }
}

void testRoutine(String inString) {
  if (inString.equals("k")) {
    println("Kickoff!");
  }
  if (inString.equals("f")) {
    println("Full Time.");
  }
  if (inString.equals("g")) {
    println("Goal!!!");
  }
}

