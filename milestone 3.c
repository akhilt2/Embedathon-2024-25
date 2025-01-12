#include <Arduino.h>

// Define the number of rows and columns
#define ROWS 8
#define COLS 8

// Define GPIO pins for rows and columns
int rowPins[ROWS] = {2, 3, 4, 5, 6, 7, 8, 9};    // GPIO pins for rows
int colPins[COLS] = {10, 11, 12, 13, 14, 15, 16, 17}; // GPIO pins for columns

// Define the bitmaps for the letters in "LAKHTARUS"
byte letters[][8] = {
  {0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b11111111, 0b00000000}, // L
  {0b01111110, 0b10000001, 0b10000001, 0b11111111, 0b10000001, 0b10000001, 0b10000001, 0b00000000}, // A
  {0b10000001, 0b10000001, 0b10010001, 0b10101001, 0b11000101, 0b10000011, 0b10000001, 0b00000000}, // K
  {0b11111111, 0b10000001, 0b10000001, 0b11111111, 0b10000001, 0b10000001, 0b11111111, 0b00000000}, // H
  {0b11111111, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b11111111, 0b00000000}, // T
  {0b01111110, 0b10000001, 0b10000001, 0b11111111, 0b10000001, 0b10000001, 0b01111110, 0b00000000}, // A
  {0b11111110, 0b10000010, 0b10000010, 0b11111110, 0b10010010, 0b10001010, 0b10000110, 0b00000000}, // R
  {0b11111111, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b11111111, 0b00000000}, // U
  {0b01111110, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b01111110, 0b00000000}  // S
};

// Function to initialize the row and column pins
void setupPins() {
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH); // Turn rows OFF initially
  }

  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW); // Turn columns OFF initially
  }
}

// Function to display a character on the LED matrix
void displayChar(byte character[8]) {
  for (int row = 0; row < ROWS; row++) {
    digitalWrite(rowPins[row], LOW); // Activate the current row
    for (int col = 0; col < COLS; col++) {
      digitalWrite(colPins[col], !(character[row] & (1 << col))); // Set column state
    }
    delay(2); // Short delay to stabilize LEDs
    digitalWrite(rowPins[row], HIGH); // Deactivate the current row
  }
}

// Function to display the message letter-by-letter
void displayMessage() {
  for (int i = 0; i < 9; i++) { // Loop through 9 letters in "LAKHTARUS"
    unsigned long startTime = millis();
    while (millis() - startTime < 500) { // Display each letter for 500ms
      displayChar(letters[i]);
    }
  }
}

void setup() {
  setupPins();
}

void loop() {
  displayMessage(); // Display the message continuously
}
