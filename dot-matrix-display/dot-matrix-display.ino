//www.elegoo.com
//2016.12.9

//We always have to include the library
#include "LedControl.h"
#include "dm-symbols.h"

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
unsigned long delaytime1 = 100;
unsigned long delaytime2 = 1250;
unsigned long delaytime3 = 250;

byte currentSymbol[8] = {};

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


/**
 * TODO: Change this method to allow for transition of symbols, e.g.: a marquee
 * running display on the dot-matrix.
 * Rough outline:
    - variable for the current symbol
    - next symbol as method argument
    - for i in 0 .. 7 (symbols are 5 wide for now)
        - shift bits in current symbol one to the left
        - copy bit 7-i from next symbol into current symbol 
 *  
 */


void setLetter(byte lttr[], unsigned long delaytime) {
    for (int i=0; i<5; ++i) {
        currentSymbol[i] = lttr[i];
    }
    for (int i=0; i<8; ++i) {
        lc.setRow(0, i, currentSymbol[i]);
    }
    delay(delaytime);
}

/**
 * Sets a new symbol to transition to, by moving the letter towards the left.  
 */
void transitionToSymbol(byte lttr[5], unsigned long delayT) {
    int lPtr = 4;
    for (int i=0; i<8; ++i) {
        for (int j=7; j>0; --j) {
            currentSymbol[j] = currentSymbol[j-1];
        }

        if (lPtr >= 0) {
            currentSymbol[1] = lttr[lPtr];
        }
        lPtr -= 1;
        
        // Display the new symbol.
        for (int i=0; i<8; ++i) {
            lc.setRow(0, i, currentSymbol[i]);
        }
        delay(delayT);
    }
    
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 TODO: Change this to hand over a string and map the letters
 to characters so that they can be parsed from said string.
 */
void writeMessageOnMatrix() {

  /* now display them one by one with a small delay */
    transitionToSymbol(sym_C, delaytime1);
    transitionToSymbol(sym_h, delaytime1);
    transitionToSymbol(sym_i, delaytime1);
    transitionToSymbol(sym_n, delaytime1);
    transitionToSymbol(sym_L, delaytime1);
    transitionToSymbol(sym_e, delaytime1);
    transitionToSymbol(sym_e, delaytime1);
    transitionToSymbol(sym_plus, delaytime1);
    transitionToSymbol(sym_M, delaytime1);
    transitionToSymbol(sym_i, delaytime1);
    transitionToSymbol(sym_c, delaytime1);
    transitionToSymbol(sym_h, delaytime1);
    transitionToSymbol(sym_a, delaytime1);
    transitionToSymbol(sym_e, delaytime1);
    transitionToSymbol(sym_l, delaytime1);
    transitionToSymbol(sym_eqls, delaytime1);
    transitionToSymbol(sym_A, delaytime1);
    transitionToSymbol(sym_n, delaytime1);
    transitionToSymbol(sym_y, delaytime1);
    transitionToSymbol(sym_a, delaytime1);
    transitionToSymbol(sym_blank, delaytime3);
    setLetter(sym_heart, delaytime2);
    setLetter(sym_space, delaytime3);
    setLetter(sym_heart, delaytime2);
    setLetter(sym_space, delaytime3);
    setLetter(sym_heart, delaytime2);
    setLetter(sym_space, delaytime3);
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
