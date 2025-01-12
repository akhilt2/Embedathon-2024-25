#include <Arduino.h>

#define ROWS 8
#define COLS 8

int rowPins[ROWS] = {2, 4, 35, 12, 5, 18, 19, 21};
int colPins[COLS] = {22, 23, 25, 26, 27, 32, 33, 34};

byte letters[][8] = {
  {0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b11111111, 0b00000000}, // L
  {0b00111110, 0b00100010, 0b00100010, 0b11111100, 0b00100010, 0b00100010, 0b00100010, 0b00100010}, // A
  {0b00100010, 0b00010010, 0b00001010, 0b00000110, 0b00001010, 0b00010010, 0b00100010, 0b00000000}, // K
  {0b00100010, 0b00100010, 0b00100010, 0b11111110, 0b00100010, 0b00100010, 0b00100010, 0b00000000}, // H
  {0b11111111, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100}, // T
  {0b00111110, 0b00100010, 0b00100010, 0b11111100, 0b00100010, 0b00100010, 0b00100010, 0b00100010}, // A
  {0b00111111, 0b00100001, 0b00100001, 0b00111111, 0b00000101, 0b00001001, 0b00010001, 0b00100001}, // R
  {0b00100010, 0b00100010, 0b00100010, 0b00100010, 0b00100010, 0b00100010, 0b00111110, 0b00000000}, // U
  {0b00111111, 0b00000001, 0b00000001, 0b00111111, 0b00100000, 0b00100000, 0b00111111, 0b00000000}  // S
};

void setupPins() {
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }

  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
}

void displayChar(byte character[8]) {
  for (int row = 0; row < ROWS; row++) {
    digitalWrite(rowPins[row], HIGH);
    for (int col = 0; col < COLS; col++) {
      digitalWrite(colPins[col], (character[row] & (1 << col)) ? LOW : HIGH);
    }
    delay(2);
    digitalWrite(rowPins[row], LOW);
  }
}

void displayMessage() {
  for (int i = 0; i < 9; i++) {
    unsigned long startTime = millis();
    while (millis() - startTime < 1000) {
      displayChar(letters[i]);
    }
  }
}

void setup() {
  setupPins();
}

void loop() {
  displayMessage();
}

// Row number 3 and Column number 7 and 8 was not working in the 8x8 LED matrix.
