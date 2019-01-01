// Michael Wagner
// 30-12-2018

// An ultrasonic sensor provides the distance to the nearest object in front of it.
// An RGB LED is then used to convert the length intolight signals (red - too close ... green - far away).

#include "SR04.h"

// Ultrasonic sensor definitions
#define TRIG_PIN 12
#define ECHO_PIN 11

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long dist;
double max_dist = 200.0;
double min_dist = 2.0;

// RGB LED definitions
#define RED 6
#define GREEN 5
#define BLUE 3

int red_val = 0;
int green_val = 0;
int blue_val = 0;

void dist_to_rgb() {
  // Normalize current distance
  double normalized = (dist - min_dist) / (max_dist - min_dist);
  double r = 0.0;
  double g = 0.0;
  double b = 0.0;
  // TODO: Could it be better to cache all the division operations here?
  if (normalized >= 0.0 && normalized <= 1.0/8.0) {
      b = 4 * normalized + 0.5;
  } else if (normalized > 1.0/8.0 && normalized <= 3.0/8.0) {
      g = 4 * normalized - 0.5;
      b = 1;
  } else if (normalized > 3.0/8.0 && normalized <= 5.0/8.0) {
      r = 4 * normalized - 1.5;
      g = 1;
      b = -4 * normalized + 2.5;
  } else if (normalized > 5.0/8.0 && normalized <= 7.0/8.0) {
      r = 1;
      g = -4 * normalized + 3.5;
  } else if (normalized > 7.0/8.0 && normalized <= 1.0) {
      r = -4 * normalized + 4.5;
  } else {
      r = 0.8;
      g = 0.8;
      b = 0.8;
  }

  Serial.print("normalized ");
  Serial.println(normalized);
  Serial.print("r ");
  Serial.println(r * 255);
  Serial.print("g ");
  Serial.println(g * 255);
  Serial.print("b ");
  Serial.println(b * 255);
  analogWrite(RED, b * 255);
  analogWrite(GREEN, g * 255);
  analogWrite(BLUE, r * 255);
}

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  Serial.begin(9600);
  delay(1000);
}

void loop() {
  dist = sr04.Distance();
  Serial.print(dist);
  Serial.println("cm");

  dist_to_rgb();
  delay(50);
}
