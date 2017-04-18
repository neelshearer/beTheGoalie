import ddf.minim.*;

Minim minim;
AudioPlayer goalSound;
AudioPlayer goalSound2;
AudioPlayer goalSound3;
AudioPlayer goalSound4;
AudioPlayer fullTimeSound;
AudioPlayer kickOffSound;

void soundSetup() {  
  // we pass this to Minim so that it can load files from the data directory
  minim = new Minim(this);

  // loadFile will look in all the same places as loadImage does.
  // this means you can find files that are in the data folder and the 
  // sketch folder. you can also pass an absolute path, or a URL.
  goalSound = minim.loadFile("goal.wav");
  goalSound2 = minim.loadFile("goal2.wav");
  goalSound3 = minim.loadFile("goal3.wav");
  goalSound4 = minim.loadFile("goal4.wav");
  kickOffSound = minim.loadFile("kickOff.wav");
  fullTimeSound = minim.loadFile("fullTime.wav");
  //  goalSound = minim.loadFile("goal.wav");
}

void    kickOffSound() {
  kickOffSound.cue(0);
  kickOffSound.play();
}

void    fullTimeSound() {
  fullTimeSound.cue(0);
  fullTimeSound.play();
}

void    goalSound() {
  int r=int(random(4));
  switch(r) {
  case 0:
    goalSound.cue(0);
    goalSound.play();
    break;

  case 1:
    goalSound2.cue(0);
    goalSound2.play();
    break;

  case 2:
    goalSound3.cue(0);
    goalSound3.play();
    break;

  case 3:
    goalSound4.cue(0);
    goalSound4.play();
    break;
  }
}

