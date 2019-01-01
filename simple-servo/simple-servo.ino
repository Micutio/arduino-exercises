//www.elegoo.com
//2016.12.08
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int posValue = 0;    // variable to store the servo position
int posTarget, posInc;
int delayValue;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  posTarget = random(0, 180);
  delayValue = random(5, 25);

  if (posValue < posTarget) {
    posInc = 1;
  } else {
    posInc = -1;
  }

  while (posValue != posTarget) {
    posValue += posInc;
    myservo.write(posValue);
    delay(delayValue);
  }


//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
}
