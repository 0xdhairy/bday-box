#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Servo myservo;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int servoPin = 13;
int buttonPin = 15;
int buzzerPin = 4;
int startButtonPin = 5;
bool started = false;
int pos = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    
  myservo.attach(servoPin, 500, 2400);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();  // start blank
}

void loop() {
  
  
  if (digitalRead(startButtonPin) == LOW) {
    for (int i = 0; i < 100; i+= 1 ) {
digitalWrite(buzzerPin, HIGH);
  delay(50);
  digitalWrite(buzzerPin, LOW);
  delay(50);
  }
  }
  if (!started && digitalRead(buttonPin) == LOW) {
    
    delay(50); // debounce
    if (digitalRead(buttonPin) == LOW) {
      started = true;
      digitalWrite(buzzerPin, HIGH); // turn buzzer ON
      delay(2000);                    // short buzz
      digitalWrite(buzzerPin, LOW);  // turn buzzer OFF

      // Show message
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(20, 25);
      display.println("Hello!");
      display.display();

      // Move servo once
      for (pos = 0; pos <= 180; pos += 1) {
        myservo.write(pos);
        delay(15);
      }

    }

    delay(10000);
    // Stop everything
    display.clearDisplay();
    display.display();
    myservo.write(0);
    myservo.detach(); // stops signal yeah
    started = false;
  }
}
