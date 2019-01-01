//www.elegoo.com
//2016.12.08

int buzzer = 12; // the pin of the active buzzer

void setup() {
  pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
}

int freqTarget, freqInc;
int freqValue = 100;

void loop() {
  unsigned char i;
 
  while (1) {

    freqTarget = random(0, 10);

    if (freqValue < freqTarget) {
      freqInc = 1;
    } else {
      freqInc = -1;
    }

    while (freqValue != freqTarget) {
      freqValue += freqInc;
      
      digitalWrite(buzzer, HIGH);
      delay(freqValue); // wait for 1ms
      digitalWrite(buzzer, LOW);
      delay(freqValue); // wait for 1ms
    }
    
    // output another frequency
//    for (i = 0; i < 100; i++) {
//      digitalWrite(buzzer, HIGH);
//      delay(2); // wait for 2ms
//      digitalWrite(buzzer, LOW);
//      delay(2); // wait for 2ms
//    }
  }
}
