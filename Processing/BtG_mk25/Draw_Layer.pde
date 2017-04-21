int lastK=0;
int lastF=0;
int lastG=0;
int statsX=width/2;
int statsYinit=250;
int statsY=statsYinit;

void drawSetup() {
  stroke(0, 0, 255);
  strokeWeight(3);
  smooth();
  font1 = loadFont("BungeeInline-Regular-50.vlw");
  font2 = loadFont("BungeeHairline-Regular-50.vlw");
  font3 = loadFont("BungeeShade-Regular-50.vlw");
  font4 = loadFont("BungeeOutline-Regular-50.vlw");
  font5 = loadFont("Bungee-Regular-50.vlw");
  photo = loadImage("photo4.jpg");
  textFont(font1, 50);
  strokeCap(SQUARE);
  noStroke();
  background(64, 0, 0);
  image(photo, 0, 0, width, 1280); // background image
  if (team.equals("red")) {
    fill(200, 0, 0, 150);
  } else {
    fill(0, 0, 200, 150);
  }
  rect(50, 50, width-100, height-100, 40); // main box
  
  textAlign(RIGHT);
  fill(255, 127);
  textFont(font5, 70);
  text("Game stats", width-200, 150);
  fill(255);  // errors
  textFont(font5, 18);
  textAlign(LEFT);
  if (serial==0) {
    text("No serial ports.", 350, 30);
  }
  if (serial==1) {
    text("Only one serial port.", 350, 30);
  }
  if (invertPorts) {
    text("Ports inverted.", 50, 30);
  } else {
    text("Ports OK.", 50, 30);
  }
  if (!kinect) {
    text("No kinect.", 650, 30);
  }
}

void drawBackgrounds() {
  noStroke();
  statsY=statsYinit;
//  fill(0, 127);
  textAlign(RIGHT);
  fill(255, 200);
  textFont(font5, 70);
//  text("Game stats", width-200, 150);
  fill(0, 127);
  for (int i=0; i<4; i++) {
    rect((width/2)-25, (100 * i)+statsY-45, 800, 70, 35);
  } 
  if (team.equals("red")) {
    fill(200, 0, 0);
  } else {
    fill(30, 30, 255);
  }

  for (int i=0; i<4; i++) {
    rect((width/2)-35, (100 * i)+statsY-55, 800, 70, 35);
  }
  fill(255, 127);
  rect((width/2)-35, (480)+statsY-45, 810, 220, 45);
  fill(0, 100, 0);
  rect((width/2)-25, (500)+statsY-55, 790, 200, 35);
  textFont(font5, 40);
  textAlign(LEFT);
  fill(255, 127);
  text("Ref says:", (width/2), (550)+statsY-55);
}

void drawKinectView() {
  if (kinect) {
    image(depthImage, 100, 100);  // draw trimmed image to screen
  } else {
    fill(127);
    rect(100, 100, 640, 480);
  }
  fill(0, 200);
  noStroke();
  rect(100, 100, xMinSend, 480);  // left cutoff box
  rect(xMaxSend+100, 100, 640-xMaxSend, 480);  // right cutoff box
  fill(64);
  rect(100, 580, 640, 250); // lower left box
}

void drawKinectLayer(float xLine, int xInt) {  // (com2d.x, xInt)
  xLine=constrain(xLine, 5, 635);
  stroke(255);
  strokeWeight(5);
  line(xLine+100, 100, xLine+100, 829); // draw line from com2d.x
  fill(255);
  textFont(font5, 50);
  textAlign(LEFT);
  //  xLine=xLine/1000;
  text(xLine+"", 150, 650);  // com2d.x
  text(xInt, 150, 750);  // xInt as sent (com2d.x after mapping)
}

void drawCoM() {
  drawPlayerLabel(com2d.x, com2d.y, targetUser);
}

void drawPlayerLabel(float x, float y, int targetUser) {
  x=constrain(x, 5, 634);  
  y=constrain(y, 5, 475);  
  x=x+100;
  y=y+100;
  stroke(255);
  strokeWeight(1);
  beginShape(LINES);  // draw CoM to screen
  vertex(x, y - 5);  
  vertex(x, y + 5);
  vertex(x - 5, y);
  vertex(x + 5, y);
  endShape();
  fill(255);
  textFont(font5, 30);
  String goalie=goalies[targetUser-1];
  float w=textWidth(goalie);
  int xOffLine=60;
  int xOffText=10;
  int yOffLine=60;
  int yOffText=10;
  if ((x+70+w)>740) {
    xOffLine=xOffLine*-1;
    xOffText=xOffText*-1;
    w=w*-1;
    textAlign(RIGHT);
  }
  if (y<200) {
    yOffLine=yOffLine*-1;
  }
  float xLimit=x+xOffLine+xOffText;
  float yLimit=y-yOffLine-yOffText-30;
  text(goalie, x+xOffLine+xOffText, y-yOffLine-yOffText);  // display userId off CoM
  beginShape(LINES);  // draw annotation line to screen
  vertex(x, y);  
  vertex(x+xOffLine, y-yOffLine);
  vertex(x+xOffLine, y-yOffLine);
  vertex(xLimit+w, y-yOffLine);
  //  vertex(xLimit, y-60);
  //  vertex(xLimit, yLimit);
  endShape();
}

void drawStatus() {
  fill(255);
  textFont(font1, 40);
  textAlign(LEFT);
  int i=statsY;
  text("People on camera: "+userList.length, width/2, i);
  i=i+100;  
  text("Goalies: "+goalieCount, width/2, i);  
  if (targetUser>0) {
    i=i+100;  
    text("Closest goalie: "+goalies[targetUser-1], width/2, i); 
    i=i+100;  
    text("Distance to "+goalies[targetUser-1]+": "+blackList[targetUser-1], width/2, i);
    i=i+100;  
    //    if (kick==true) {
    //      text("Kicking", width/2, i);
    //    } else {
    //      text("Not kicking", width/2, i);
    //    }
  }
  if (!kinect) {    
    i=i+100;  
    text("(closest goalie)", width/2, i); 
    i=i+100;  
    text("(distance to)", width/2, i); 
    i=i+100;  
    //    text("(kicking)", width/2, i);
  }
  statsY=i;
  textSize(20);
}

void drawEvent() {
  fill(255);
  textFont(font1, 80);
  textAlign(CENTER);
  statsY=650+190;
  if (millis()-lastK<5000) {
    text("Kickoff!", width/2+380, statsY);
  } else if (millis()-lastF<5000) {
    text("Full Time.", width/2+380, statsY);
  } else if (millis()-lastG<5000) {
    text("GOAL!!!", width/2+380, statsY);
  }
  if (serial==0) {
    //    text("Kickoff!", width/2+380, statsY);
//    text("TIMER", width/2+380, statsY);
    //    text("GOAL!!!", width/2+380, statsY);
  }
}

void drawAlert(int data) {
  fill(255);
  textSize(50);
  text("ALERT: "+data, width/2, 900);
  textSize(20);
}

// draw the skeleton with the selected joints
void drawSkeleton(int userId)
{
  stroke(userClr[ (userList[targetUser-1] - 1) % userClr.length ] );  // set stroke colour
  stroke(255);
  translate(100, 100);
  // to get the 3d joint data
  context.drawLimb(userId, SimpleOpenNI.SKEL_HEAD, SimpleOpenNI.SKEL_NECK);

  context.drawLimb(userId, SimpleOpenNI.SKEL_NECK, SimpleOpenNI.SKEL_LEFT_SHOULDER);
  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_SHOULDER, SimpleOpenNI.SKEL_LEFT_ELBOW);
  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_ELBOW, SimpleOpenNI.SKEL_LEFT_HAND);

  context.drawLimb(userId, SimpleOpenNI.SKEL_NECK, SimpleOpenNI.SKEL_RIGHT_SHOULDER);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_SHOULDER, SimpleOpenNI.SKEL_RIGHT_ELBOW);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_ELBOW, SimpleOpenNI.SKEL_RIGHT_HAND);

  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_SHOULDER, SimpleOpenNI.SKEL_TORSO);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_SHOULDER, SimpleOpenNI.SKEL_TORSO);

  context.drawLimb(userId, SimpleOpenNI.SKEL_TORSO, SimpleOpenNI.SKEL_LEFT_HIP);
  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_HIP, SimpleOpenNI.SKEL_LEFT_KNEE);
  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_KNEE, SimpleOpenNI.SKEL_LEFT_FOOT);

  context.drawLimb(userId, SimpleOpenNI.SKEL_TORSO, SimpleOpenNI.SKEL_RIGHT_HIP);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_HIP, SimpleOpenNI.SKEL_RIGHT_KNEE);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_KNEE, SimpleOpenNI.SKEL_RIGHT_FOOT);
}

