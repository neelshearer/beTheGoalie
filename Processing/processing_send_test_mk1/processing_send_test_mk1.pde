import processing.serial.*;

Serial myPort;  // Create object from Serial class

void setup() {
  size(640, 640);
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 115200);
}

void draw() {
  serialSend(mouseX);
}

void serialEvent(Serial myPort) {
  readRoutine();
}

void serialSend(float xFloat) {
  float x=map(xFloat, 0, 640, 0, 254);
  int x2=int(x);
//  println(x2);
  myPort.write(x2);
}

void keyReleased() {
  if(key==' '){
    myPort.write(255);
  }
}

