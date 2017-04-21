import processing.serial.*;

Serial myPort;  // Create object from Serial class
Serial scorePort;  // Create object from Serial class
String inputString="default";      // Data received from the serial port
String lastInputString="default";
int goalie=0;
boolean invertPorts=false;

void serialSetup() {
  println("Initializing Serial library...");
  String [] portList=Serial.list();
  printArray(portList);
  if (portList.length>1) {
    serial=1;
    String portName = Serial.list()[1];
    myPort = new Serial(this, portName, 115200);
    println("Serial port "+portName+" opened, checking to see if it is the table...");
    delay(2000);
    int inByte = myPort.read();
    // if this is the first byte received, and it's an A,
    // clear the serial buffer and note that you've
    // had first contact from the microcontroller. 
    // Otherwise, add the incoming byte to the array:
    if (inByte == 'A') { 
      myPort.clear();          // clear the serial port buffer
      println("Table detected on "+portName+", sending it table commands (myPort).\n-----------");
      myPort.write('A');       // ask for more
    } else {
      // Close the port
      myPort.stop();
      invertPorts=true;
      println("Table not detected on "+portName+", closing the port.");
      String scorePortNameInv = portName;
      scorePort = new Serial(this, scorePortNameInv, 115200);
      println("Serial port "+scorePortNameInv+" opened, sending it scoreboard commands (scorePort).\n-----------");
    }
  } else {
    println("No serial ports found. \nContinuing without serial.\n-----------");
    goalie=int(random(1, 7));
  }
  if (portList.length>2) {
    serial=2;
    if (invertPorts==false) {
      String scorePortName = Serial.list()[2];
      scorePort = new Serial(this, scorePortName, 115200);
      println("Serial port "+scorePortName+" opened, sending it scoreboard commands (scorePort).\n-----------");
    } else {
      String portNameInv = Serial.list()[2];
      myPort = new Serial(this, portNameInv, 115200);
      println("Serial port "+portNameInv+" opened, sending it table commands (myPort).\n-----------");
      myPort.write('A');       // ask for more
    }
  }
}

void serialEvent(Serial myPort) {
  readRoutine();
}

void readRoutine() {
  lastInputString=inputString;  // update the memeory of the previous string
  if ( myPort.available() > 0) {  // If data is available,
    String tempInputString = myPort.readStringUntil('\n');         // read it and store it in inputString
    if (tempInputString!=null) {  //if inputString contains data
      inputString=trim(tempInputString);  //trim it
      //      if (inputString.equals(lastInputString)) {
      //      } else { //and has not changed since the last time
      testRoutine(inputString);  // do the test routine
      //      }
    }
  }
}

void serialSend(int x) {
  myPort.write(x);
}

void testRoutine(String inString) {
  println(inString);
  if (inString.equals("k")) {
    kickOff();
  }
  if (inString.equals("f")) {
    fullTime();
  }
  if (inString.equals("g")) {
    goal();
  }
}

void sendDummy() {
  if (serial!=0) {
    serialSend(constrain(xInt, 0, 254));
    println(xInt);
  }
}

