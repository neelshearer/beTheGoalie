const int gameDuration = 180; // game time in seconds
const int changeOverDuration = 30; // changeover time in seconds
int score = 0;
long lastEvent = 0;
boolean changeOverState = true;
boolean changeOverFlag = false;
const int mclrPin=2;

void setup()
{
  //  size(200, 200);
  //  String portName = Serial.list()[1];
  //  myPort = new Serial(this, portName, 115200);
  pinMode(mclrPin,OUTPUT);
  digitalWrite(mclrPin, LOW);
  delay(100);
  digitalWrite(mclrPin, HIGH);
  serialSetup();
  delay(1000);
  Serial.print("configpanel 64 32 0 2 \r");  //  setup panel
  black();
}

void loop() {
  serialCheck();
  delay(1000);
  if (changeOverState == false) {
    play2();
    delay(100);
  } else {
    changeOver();
    delay(100);
  }
}

void play() {
//  long clock = millis() - lastEvent;
  Serial.print("circlef 0 24 16 17\r");
  Serial.print("circlef 0 31 16 17\r");
  Serial.print("circlef 0 40 16 17\r");
  if (score < 10) {
    Serial.print("font 14\rtext 3 26 30 \""); Serial.print(score); Serial.print("\"\rpaint\r");
  } else {
    Serial.print("font 14\rtext 3 20 30 \""); Serial.print(score); Serial.print("\"\rpaint\r");
  }
}

void play2() {
  int clock = constrain(gameDuration - int((millis() - lastEvent) / 1000), 0, gameDuration);
  int mins = clock / 60;
  int secs = clock % 60;
  //  Serial.print("circlef 0 24 16 17\r");
  //  Serial.print("circlef 0 31 16 17\r");
  Serial.print("circlef 0 7 16 6\r");  // clock background
  Serial.print("rect 0 7 22 31 13\r");  // clock background
  //  Serial.print("rect 3 7 21 31 11\r");
  Serial.print("circlef 0 49 16 14\r");  // score background
  Serial.print("font 3\rtext 3 8 19 \"");
  Serial.print(mins);
  Serial.print(":");
  if (secs < 10) {
    Serial.print("0");
  }
  Serial.print(secs);
  Serial.print("\"\r");
  if (score < 10) {
    Serial.print("font 10\rtext 3 45 23 \""); Serial.print(score); Serial.print("\"\rpaint\r");
  } else {
    Serial.print("font 10\rtext 3 40 23 \""); Serial.print(score); Serial.print("\"\rpaint\r");
  }
}

void changeOver() {
  int countdown = constrain(int(changeOverDuration - ((millis() - lastEvent) / 1000)), 0, changeOverDuration);
  //  Serial.println(countdown);
  if (changeOverFlag == false) {
    yellow();
    int x = 3;
    int y = 14;
    Serial.print("font 9\r");
    Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"NEXT\"\r");
    y = y + 13;
    Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"GAME\"\rpaint\r");
    changeOverFlag = true;
  }
  if (countdown > 9) {
    Serial.print("rect 0 38 32 32 32\rtext 3 42 21 \""); Serial.print(countdown); Serial.print("\"\rpaint\r");
  } else {
    Serial.print("rect 0 38 32 32 32\rtext 3 47 21 \""); Serial.print(countdown); Serial.print("\"\rpaint\r");
  }
  //  println(countdown);
}

void fullTime() {
  lastEvent = millis();
  yellowWipeCentre();
  yellowBorder();
  int x = 15;
  int y = 14;
  Serial.print("font 9\r");
  Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"G\"\rpaint\r");
  delay(400);
  Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"GA\"\rpaint\r");
  delay(400);
  Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"GAM\"\rpaint\r");
  delay(400);
  Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"GAME\"\rpaint\r");
  delay(400);
  y = y + 13;
  Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"O\"\rpaint\r");
  delay(400);
  Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"OV\"\rpaint\r");
  delay(400);
  Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"OVE\"\rpaint\r");
  delay(400);
  Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"OVER\"\rpaint\r");
  delay(400);
  for (int i = 0; i < 6; i++) {
    yellowBorder();
    Serial.print("font 9\rtext 3 "); Serial.print(x); Serial.print(" "); Serial.print((y - 13)); Serial.print(" \"GAME\"\r");
    Serial.print("text 3 "); Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" \"OVER!\"\rpaint\r");
    delay(400);
    black();
    play();
    delay(400);
  }
  black();
  delay(1000);
  score = 0;
  changeOverState = true;
}

void kickOff() {
  changeOverState = false;
  changeOverFlag = false;
  lastEvent = millis();
  for (int i = 1; i < 62; i++) { // expanding red rect
    Serial.print("rect 2 "); Serial.print((33 - i / 2)); Serial.print(" "); Serial.print((15 + i / 4)); Serial.print(" "); Serial.print(i); Serial.print(" "); Serial.print(i / 2); Serial.print("\rpaint\r");
    delay(10);
  }
  Serial.print("rect 2 "); Serial.print(0); Serial.print(" "); Serial.print(31); Serial.print(" "); Serial.print(64); Serial.print(" "); Serial.print(32); Serial.print("\rpaint\r");
  for (int i = 1; i < 60; i++) { // expanding black rect
    Serial.print("rect 3 "); Serial.print((33 - i / 2)); Serial.print(" "); Serial.print((15 + i / 4)); Serial.print(" "); Serial.print(i); Serial.print(" "); Serial.print(i / 2); Serial.print("\rpaint\r");
    delay(10);
  }
  Serial.print("rect 3 "); Serial.print(1); Serial.print(" "); Serial.print(30); Serial.print(" "); Serial.print(62); Serial.print(" "); Serial.print(30); Serial.print("\rpaint\r");
  for (int i = 1; i < 58; i++) { // expanding yellow rect
    Serial.print("rect 0 "); Serial.print((33 - i / 2)); Serial.print(" "); Serial.print((15 + i / 4)); Serial.print(" "); Serial.print(i); Serial.print(" "); Serial.print(i / 2); Serial.print("\rpaint\r");
    delay(10);
  }
  Serial.print("rect 0 "); Serial.print(2); Serial.print(" "); Serial.print(29); Serial.print(" "); Serial.print(60); Serial.print(" "); Serial.print(28); Serial.print("\rpaint\r");
  for (int i = 0; i < 9; i++) {
    yellow();
    delay(100);
    Serial.print("font 10\rtext 3 8 23 \"PLAY!\"\rpaint\r");
    delay(100);
  }
  delay(1000);
  for (int i = 0; i < 31; i++) {
    //    Serial.print("rect 0 ");Serial.print(8);Serial.print(" ");Serial.print((31-i));Serial.print(" ");Serial.print(50);Serial.print(" ");Serial.print(32);Serial.print("\r");  // yellow rect
    Serial.print("rect 0 0 32 64 33\r"); // fill yellow
    Serial.print("font 10\rtext 3 8 "); Serial.print((23 - i)); Serial.print(" \"PLAY!\"\r");
    Serial.print("rect 3 "); Serial.print(0); Serial.print(" "); Serial.print((63 - i)); Serial.print(" "); Serial.print(64); Serial.print(" "); Serial.print(32); Serial.print("\rpaint\r"); // black rect
    delay(50);
  }
  black();
}

void black() {
  Serial.print("rect 3 0 32 64 33\rpaint\r");  // fill black
}

void yellow() {
  Serial.print("rect 0 0 32 64 33\rpaint\r"); // fill yellow
}

void yellowBorder() {
  Serial.print("rect 2 0 31 64 32\rpaint\r");  // fill black
  Serial.print("rect 3 1 30 62 30\rpaint\r");  // fill black
  Serial.print("rect 0 2 29 60 28\rpaint\r");  // fill black
}

void yellowWipeCentre() {
  for (int i = 0; i <= 32; i++) { // yellow wipe left
    Serial.print("rect 0 "); Serial.print((32 - (i))); Serial.print(" 32 "); Serial.print(2 * i); Serial.print(" 33\rpaint\r");
    delay(100);
  }
}

void blackWipe() {
  for (int i = 0; i <= 64; i++) { // black wipe left
    Serial.print("rect 3 "); Serial.print((64 - (i))); Serial.print(" 32 64 33\rpaint\r");
    delay(10);
  }
}

void yellowWipe() {
  for (int i = 0; i <= 64; i++) { // black wipe left
    Serial.print("rect 3 "); Serial.print((64 - (i))); Serial.print(" 32 64 33\rpaint\r");
    delay(10);
  }
}

void goalScroll(int j) {
  Serial.print("font 14\rscrollspeed 10\r");  //setup scrolling
  yellowWipe();
  for (int i = 0; i < j; i++) { // scroll goal j times
    Serial.print("scroll 3 0 30 64 \"GOAL!!!\"\r");  // scroll goal
    delay(1600);
  }
  blackWipe();
  score++;
}

void goalZoom() {
  for (int i = 0; i < 32; i++) { // expanding yellow circle
    Serial.print("circlef 0 32 16 "); Serial.print(i); Serial.print("\rpaint\r");
    delay(10);
  }
  Serial.print("rect 0 0 32 64 33\rpaint\r"); // fill yellow
  for (int i = 0; i < 32; i++) { // expanding black circle
    Serial.print("circlef 3 32 16 "); Serial.print(i); Serial.print("\rpaint\r");
    delay(10);
  }
  Serial.print("rect 3 0 32 64 33\rpaint\r"); // fill black
  for (int i = 0; i < 32; i++) { // expanding yellow circle
    Serial.print("circlef 0 32 16 "); Serial.print(i); Serial.print("\rpaint\r");
    delay(10);
  }
  yellow();
  Serial.print("font 2\rtext 3 22 18 \"GOAL\"\rpaint\r");
  delay(200);
  yellow();
  Serial.print("font 8\rtext 3 18 20 \"GOAL\"\rpaint\r");
  delay(200);
  yellow();
  Serial.print("font 11\rtext 3 12 22 \"GOAL\"\rpaint\r");
  delay(200);
  yellow();
  Serial.print("font 12\rtext 3 1 27ghh \"GOAL\"\rpaint\r");
  delay(200);
  for (int i = 0; i < 3; i++) { // flash Goal
    yellow();
    delay(200);
    Serial.print("font 12\rtext 3 1 27 \"GOAL\"\rpaint\r");
    delay(200);
  }
  yellow();
  Serial.print("font 11\rtext 3 12 22 \"GOAL\"\rpaint\r");
  delay(200);
  yellow();
  Serial.print("font 8\rtext 3 18 20 \"GOAL\"\rpaint\r");
  delay(200);
  yellow();
  Serial.print("font 2\rtext 3 22 18 \"GOAL\"\rpaint\r");
  delay(200);
  for (int i = 32; i > 0; i--) { // shrinking yellow circle
    black();
    Serial.print("circlef 0 32 16 "); Serial.print(i); Serial.print("\rpaint\r");
    delay(10);
  }
  for (int i = 32; i > 0; i--) { // shrinking black circle
    yellow();
    Serial.print("circlef 3 32 16 "); Serial.print(i); Serial.print("\rpaint\r");
    delay(10);
  }
  for (int i = 32; i > 0; i--) { // shrinking yellow circle
    black();
    Serial.print("circlef 0 32 16 "); Serial.print(i); Serial.print("\rpaint\r");
    delay(10);
  }
  black();
  score++;
}

void test() {
  Serial.print("");
  delay(10);
  Serial.print("font 2\rtext 3 32 16 \"GOAL\"\rpaint\r");
  delay(10);
  Serial.print("");
}
