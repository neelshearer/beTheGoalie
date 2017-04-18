const byte interrupt1Pin = 2;  // goal sensor
const byte interrupt2Pin = 3;  // goal sensor
const byte send1Pin = 6;  // motherboard 1
const byte send2Pin = 7;  // motherboard 2
const byte led1Pin = 4;  // motherboard 1
const byte led2Pin = 5;  // motherboard 2
boolean goal1Flag = false;
boolean goal2Flag = false;
long int lastEvent = 0;

void setup() {
  Serial.begin(9600);
  pinMode(send1Pin, OUTPUT);
  digitalWrite(send1Pin, LOW);
  pinMode(send2Pin, OUTPUT);
  digitalWrite(send2Pin, LOW);
  pinMode(led1Pin, OUTPUT);
  digitalWrite(led1Pin, LOW);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led2Pin, LOW);
  pinMode(interrupt1Pin, INPUT);
  pinMode(interrupt2Pin, INPUT);
  //  attachInterrupt(digitalPinToInterrupt(interrupt1Pin), goal1, RISING); //digitalPinToInterrupt(interruptPin)
  //  attachInterrupt(digitalPinToInterrupt(interrupt2Pin), goal2, RISING); //digitalPinToInterrupt(interruptPin)
}

void loop() {
  delay(10);
  if (millis() - lastEvent > 5000) {
  int sensor1Value = digitalRead(interrupt1Pin);
  int sensor2Value = digitalRead(interrupt2Pin);
    Serial.print(sensor1Value);
    Serial.println(sensor2Value);
    if (sensor1Value == 1 && goal1Flag == false) {
      goal1();
    }
    else if (sensor1Value == 0 && goal1Flag == true) {
      goal1Flag = false;
    }
    else if (sensor2Value == 1 && goal2Flag == false) {
      goal2();
    }
    else if (sensor2Value == 0 && goal2Flag == true) {
      goal2Flag = false;
    }
  }
}

void goal1() {
  lastEvent = millis();
  goal1Flag = true;
  Serial.println("goal 1");
  digitalWrite(send1Pin, HIGH);
  digitalWrite(led1Pin, HIGH);
  delay(1000);
  digitalWrite(send1Pin, LOW);
  digitalWrite(led1Pin, LOW);
  delay(7000);
}
void goal2() {
  lastEvent = millis();
  goal2Flag = true;
  goal1Flag = true;
  Serial.println("goal 2");
  digitalWrite(send2Pin, HIGH);
  digitalWrite(led2Pin, HIGH);
  delay(1000);
  digitalWrite(send2Pin, LOW);
  digitalWrite(led2Pin, LOW);
  delay(7000);
}

