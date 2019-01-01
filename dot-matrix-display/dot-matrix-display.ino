//www.elegoo.com
//2016.12.9

//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to LOAD(CS)
 pin 10 is connected to the CLK 
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12,10,11,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime1 = 950;
unsigned long delaytime2 = 1250;
unsigned long delaytime3 = 150;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);
}

/* here is the data for the characters */
byte a[5] = {B00011110,
             B00101010,
             B00101010,
             B00101010,
             B00100100};
byte A[5] = {B01111110,
             B10001000,
             B10001000,
             B10001000,
             B01111110};
byte c[5] = {B00010010,
             B00100010,
             B00100010,
             B00100010,
             B00011100};
byte C[5] = {B01000100,
             B10000010,
             B10000010,
             B10000010,
             B01111100};
byte d[5] = {B11111110,
             B00010010,
             B00100010,
             B00100010,
             B00011100};
byte e[5] = {B00011010,
             B00101010,
             B00101010,
             B00101010,
             B00011100};
byte h[5] = {B00011110,
             B00100000,
             B00100000,
             B00010000,
             B11111110};
byte i[5] = {B00000000,
             B00000010,
             B10111110,
             B00100010,
             B00000000};
byte l[5] = {B00000010,
             B00000010,
             B01111100,
             B10000000,
             B00000000};
byte L[5] = {B00000010,
             B00000010,
             B00000010,
             B11111100,
             B10000000};
byte M[5] = {B01111110,
             B10000000,
             B01111000,
             B10000000,
             B01111110};           
byte n[5] = {B00011110,
             B00100000,
             B00100000,
             B00010000,
             B00111110};
byte o[5] = {B00011100,
             B00100010,
             B00100010,
             B00100010,
             B00011100};
byte r[5] = {B00010000,
             B00100000,
             B00100000,
             B00010000,
             B00111110};
byte u[5] = {B00111110,
             B00000100,
             B00000010,
             B00000010,
             B00111100};
byte y[5] = {B00111100,
             B00001010,
             B00001010,
             B00001010,
             B00110010};
byte plus[5] = {B00001000,
                B00001000,
                B00111110,
                B00001000,
                B00001000};
byte eqls[5] = {B00010100,
                B00010100,
                B00010100,
                B00010100,
                B00010100};
byte heart[5] = {B00110000,
                 B01001000,
                 B00100100,
                 B01001000,
                 B00110000};
byte space[5] = {B00000000,
                 B00000000,
                 B00000000,
                 B00000000,
                 B00000000};

void setLetter(byte lttr[5]) {
  lc.setRow(0, 0, lttr[0]);
  lc.setRow(0, 1, lttr[1]);
  lc.setRow(0, 2, lttr[2]);
  lc.setRow(0, 3, lttr[3]);
  lc.setRow(0, 4, lttr[4]);
}
/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void writeMessageOnMatrix() {

  /* now display them one by one with a small delay */
  
  setLetter(C);
  delay(delaytime1);
  setLetter(h);
  delay(delaytime1);
  setLetter(i);
  delay(delaytime1);
  setLetter(n);
  delay(delaytime2);
  setLetter(L);
  delay(delaytime1);
  setLetter(e);
  delay(delaytime1);
  setLetter(space);
  delay(delaytime3);
  setLetter(e);
  delay(delaytime2);
  setLetter(plus);
  delay(delaytime2);
  setLetter(M);
  delay(delaytime1);
  setLetter(i);
  delay(delaytime1);
  setLetter(c);
  delay(delaytime1);
  setLetter(h);
  delay(delaytime1);
  setLetter(a);
  delay(delaytime1);
  setLetter(e);
  delay(delaytime1);
  setLetter(l);
  delay(delaytime2);
  setLetter(eqls);
  delay(delaytime2);
  setLetter(A);
  delay(delaytime1);
  setLetter(n);
  delay(delaytime1);
  setLetter(y);
  delay(delaytime1);
  setLetter(a);
  delay(delaytime2);
  setLetter(heart);
  delay(delaytime2);
  setLetter(space);
  delay(delaytime3);
  setLetter(heart);
  delay(delaytime2);
  setLetter(space);
  delay(delaytime3);
  setLetter(heart);
  delay(delaytime2);
  setLetter(space);
  delay(delaytime3);
  setLetter(heart);
  delay(delaytime2);
  setLetter(space);
  delay(delaytime3);
}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
  for (int row=0; row<8; row++) {
    delay(delaytime2);
    lc.setRow(0, row, B10100000);
    delay(delaytime2);
    lc.setRow(0, row, (byte)0);
    
    for (int i=0; i<row; i++) {
      delay(delaytime2);
      lc.setRow(0, row, B10100000);
      delay(delaytime2);
      lc.setRow(0, row, (byte)0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns() {
  for (int col=0; col<8; col++) {
    delay(delaytime2);
    lc.setColumn(0, col, B10100000);
    delay(delaytime2);
    lc.setColumn(0, col, (byte)0);
    for (int i=0; i<col; i++) {
      delay(delaytime2);
      lc.setColumn(0, col, B10100000);
      delay(delaytime2);
      lc.setColumn(0, col, (byte)0);
    }
  }
}

/* 
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for (int row=0; row<8; row++) {
    for (int col=0; col<8; col++) {
      delay(delaytime2);
      lc.setLed(0, row, col, true);
      delay(delaytime2);
      for (int i=0; i<col; i++) {
        lc.setLed(0, row, col, false);
        delay(delaytime2);
        lc.setLed(0, row, col, true);
        delay(delaytime2);
      }
    }
  }
}

void loop() { 
  writeMessageOnMatrix();
//  rows();
//  columns();
//  single();
}
