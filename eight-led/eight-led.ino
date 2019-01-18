// www.elegoo.com
// 2016.12.9

int tDelay = 200;
int lightPin = 0;
int dataPin = 12;  // (12) DS [S1] on 74HC595
int latchPin = 11; // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;  // (9) SH_CP [SCK] on 74HC595

// Hold the pattern in which the leds are currently turned on or off.
byte leds = 0;

void updateShiftRegister() {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
}

void cycleLEDs() {
    leds = 0;
    updateShiftRegister();
    delay(tDelay);
    for (int i = 0; i < 8; i++) {
        bitSet(leds, i);
        updateShiftRegister();
        delay(tDelay);
    }
}

void readLEDSFromSerial() {
    if (Serial.available()) {
        char ch = Serial.read();
        
        if (ch >= '0' && ch <= '7') {
            int led = ch - '0';
            bitSet(leds, led);
            updateShiftRegister();
            Serial.print("turned on LED ");
            Serial.println(led);
        }

        if (ch == 'x') {
            leds = 0;
            updateShiftRegister();
            Serial.println("cleared");
        }
    }
}

void readLEDsFromAmbientBrightness() {
    int reading = analogRead(lightPin);
    int numLEDsLit = reading / 57; // 1023 / 9 / 2
    
    if (numLEDsLit > 8) {
        numLEDsLit = 8;
    }

    leds = 0;
    for (int i = 0; i < numLEDsLit; i++) {
        leds = leds + (1 << i); // Set ith bit.
    }
    updateShiftRegister();
}

void setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    updateShiftRegister();
    Serial.begin(9600);

    while (!Serial); // Wait until Serial is ready.
    Serial.println("Enter LED number 0 to 7 or 'x' to clear.");
}

void loop() {
    
    // toggleLEDs();
    // readLEDsFromSerial();
    readLEDsFromAmbientBrightness();
}
