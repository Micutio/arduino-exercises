//www.elegoo.com
//2016.12.8

// Define Pins
#define RED 6
#define GREEN 3
#define BLUE 5
//#define delayTime 10 // fading time between colors

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}


// define variables
int redValue = 0;
int redTarget, redInc;
int greenValue = 0;
int greenTarget, greenInc;
int blueValue = 0;
int blueTarget, blueInc;

int delayTime;

// main loop
void loop() {

//  redValue = 0;
//  greenValue = 0;
//  blueValue = 0;
  redTarget = random(0, 3) * 125;
  greenTarget = random(0, 3) * 125;
  blueTarget = random(0, 3) * 125;
  delayTime = random(1, 8);

  if (redValue < redTarget) {
    redInc = 1;
  } else {
    redInc = -1;
  }

  if (greenValue < greenTarget) {
    greenInc = 1;
  } else {
    greenInc = -1;
  }

  if (blueValue < blueTarget) {
    blueInc = 1;
  } else {
    blueInc = -1;
  }

  while (redValue != redTarget || greenValue != greenTarget || blueValue != blueTarget) {
    if (redValue != redTarget) {
      redValue += redInc;
    }
    
    if (greenValue != greenTarget) {
      greenValue += greenInc;
    }
    
    if (blueValue != blueTarget) {
      blueValue += blueInc;
    }
    
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    analogWrite(BLUE, blueValue);
    delay(delayTime);
  }  
}
