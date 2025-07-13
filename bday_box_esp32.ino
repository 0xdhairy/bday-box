#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Servo lidServo;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int servoPin = 13;
int buttonPin = 15;
int buzzerPin = 4;
int startButtonPin = 5;
bool started = false;
int pos = 180;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  lidServo.setPeriodHertz(50);
  lidServo.attach(servoPin, 500, 2400);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 25);
  display.println("Press the button ");
  display.println("   for a suprise!");
  display.display();  // start blank
}

void loop() {



  if (!started && digitalRead(buttonPin) == LOW) {
    display.clearDisplay();
    display.display();
    delay(50);  // debounce
    if (digitalRead(buttonPin) == LOW) {
      started = true;
      digitalWrite(buzzerPin, HIGH);  // turn buzzer ON
      delay(2000);                    // short buzz
      digitalWrite(buzzerPin, LOW);   // turn buzzer OFF

      // Show message
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(16, 25);
      display.println("Happy Bday ____!");
      display.println("   - From Dhairy");
      display.display();
      for (int pos = 180; pos >= 110; pos--) {
        lidServo.write(pos);  // slowly opens the hinge
        delay(5);
      }
    }

    delay(10000);
    lidServo.write(180);
    display.clearDisplay();
    display.display();
    started = false;
  }
}
