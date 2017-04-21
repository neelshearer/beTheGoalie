/* 
 By Roy Shearer, Zero One, winter 2017, based on:
 --------------------------------------------------------------------------
 * SimpleOpenNI User Test
 * --------------------------------------------------------------------------
 * Processing Wrapper for the OpenNI/Kinect 2 library
 * http://code.google.com/p/simple-openni
 * --------------------------------------------------------------------------
 * prog:  Max Rheiner / Interaction Design / Zhdk / http://iad.zhdk.ch/
 * date:  12/12/2012 (m/d/y)
 * ----------------------------------------------------------------------------
 */

String team="red";
int zMax = 3800; //3800
int zMin = 2800;  //2800
//int xMax = 1100; //1100  // 
//int xMin = -xMax;
int xMinSend = 320-100;  // used to filter out users and map com2d.x as it is sent as xInt to table, and to draw graphic limits
int xMaxSend = 320+100;
//int xMinDraw = 220;  // 
//int xMaxDraw = 640-xMinDraw;
int kickThreshold=220;
int goalieCount=0;

int scaleFactor=0;
boolean kick=false;
int serial=0;
boolean kinect=false;
PFont font1;
PFont font2;
PFont font3;
PFont font4;
PFont font5;
PImage photo;

void setup()
{
  size(1920, 1080);
  scaleFactor=width/640;
  scaleFactor=1;
  kinectSetup();
  serialSetup();
  drawSetup();
  soundSetup();
}

void draw()
{
  drawBackgrounds();
  scale(scaleFactor); // if appropriate
  if (kinect) {
    kinectData(); // get the data from the kinect and manipulate it
  }
  drawKinectView(); // draw results to screen
  filterUsers(); // filter out users out of window and pick target user
  drawStatus(); // draw results to screen
  drawEvent(); // draw events from table to screen (Kickoff/Full Time/Goal)
  targetUser(); // get the data from the target user and send to serial
//  readRoutine();
}

void onNewUser(SimpleOpenNI curContext, int userId)
{
  println("onNewUser - userId: " + userId);
  println("\tstart tracking skeleton");

  curContext.startTrackingSkeleton(userId);
}

void onLostUser(SimpleOpenNI curContext, int userId)
{
  println("onLostUser - userId: " + userId);
  targetUser=0;
}

void onVisibleUser(SimpleOpenNI curContext, int userId)
{
  //println("onVisibleUser - userId: " + userId);
}

