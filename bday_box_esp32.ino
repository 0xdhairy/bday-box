#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // display.setCursor(0, 20);
  // display.println("Happy Birthday Dad!");
  // display.setCursor(0, 25);
  // display.println(" You're the best!");
  // display.setCursor(5, 45);
  // display.println("   - From Dhairy");

  display.display();
}

void loop() {
  // nothing for now — static display
}
