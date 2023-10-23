#include <FastLED.h>

// Define the LED strip
#define NUM_LEDS 25  // Total number of LEDs in your 5x5 grid
#define DATA_PIN 6   // Define the data pin to which your LEDs are connected
CRGB leds[NUM_LEDS];

// Define the mapping of numerical values to LED positions (0-based)
const int ledMap[5][5] = {
  {0, 1, 2, 3, 4},
  {5, 6, 7, 8, 9},
  {10, 11, 12, 13, 14},
  {15, 16, 17, 18, 19},
  {20, 21, 22, 23, 24}
};

void setup() {
  // Initialize the LED strip
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100); // Set the LED brightness (adjust as needed)
  FastLED.clear(); // Clear all LEDs at startup
  FastLED.show();   // Show the initial state
}

void loop() {
  // Read the serial data
  while (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    
    // Split the data into client and status numbers
    int clientNumber = data.substring(0, data.indexOf(',')).toInt();
    int statusNumber = data.substring(data.indexOf(',') + 1).toInt();

    // Call a function to control the LEDs based on clientNumber and statusNumber
    controlLEDs(clientNumber, statusNumber);
  }
}

void controlLEDs(int client, int status) {
  // Clear all LEDs
  FastLED.clear();

  // Check if the client and status values are within the valid range
  if (client >= 1 && client <= 5 && status >= 1 && status <= 5) {
    // Calculate the corresponding LED index based on the client and status numbers
    int ledIndex = ledMap[status - 1][client - 1];

    // Set the LED color (you can customize this)
    leds[ledIndex] = CRGB::Red;

    // Show the changes on the LED strip
    FastLED.show();
  }
}
