void keyReleased() {
  boolean scoreBoard=true;
  if (serial==0) {
    scoreBoard=false;
  }
  if (serial==1&&invertPorts==false) {
    scoreBoard=false;
  }
  if (key=='k') {
    kickOff();
    if (scoreBoard) {
      scorePort.write("k\n");
    }
  }
  if (key=='f') {
    fullTime();
    if (scoreBoard) {
      scorePort.write("f\n");
    }
  }
  if (key=='g') {
    goal();
    if (scoreBoard) {
      scorePort.write("g\n");
    }
  }
  if (key=='r') {
    if (goalie<6) {
      goalie++;
    } else {
      goalie=1;
    }
  }
}

