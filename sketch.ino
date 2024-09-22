#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Setup
#define SCREEN_WIDTH 128  // OLED width, in pixels
#define SCREEN_HEIGHT 64  // OLED height, in pixels
#define OLED_RESET    -1  // Reset pin (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Define Pins
const int triggerPin = 9;
const int echoPin = 10;
const int buzzerPin = 6;
const int ledPin = 7;

// Define variables for distance
long duration;
float distance;

void setup() {
  // Initialize Serial
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {  // Address 0x3C for 128x64
    Serial.println(F("Allocation failed"));
    for(;;); // loop forever
  }

  display.display();
  delay(2000);

  display.clearDisplay(); // clear the buffer

  // Pin modes
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

// Function to draw progress bar based on distance
void drawProgressBar(float distance) {
  int progress = map(distance, 0, 400, 0, 100); // Map distance to percentage

  // Calculate the starting position for centering the bar
  int barWidth = 100;
  int barX = (SCREEN_WIDTH - barWidth) / 2; //Calculate centered position

  display.clearDisplay(); //Clear the display
  display.setTextSize(1); // Text Size
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");

  //Draw progress bar
  display.drawRect(barX, 20, barWidth, 10, SSD1306_WHITE); //Draw the border
  display.fillRect(barX, 20, progress, 10, SSD1306_WHITE); // Fill the bar

  display.display();
}

void loop() {
  // Pulse from the TRIG pin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Measure the pulse duration on the ECHO pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm's
  distance = duration * 0.034 / 2;

  // Update OLED with distance and progress bar
  drawProgressBar(distance);

  // Control the buzzer and LED based on distance
  if (distance > 400) {
    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);
  } else if (distance > 300) {
    tone(buzzerPin, 500, 200);  // 200ms tone
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  } else if (distance > 200) {
    tone(buzzerPin, 500, 100);  // 100ms tone
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
  } else if (distance > 100) {
    tone(buzzerPin, 500, 50);   // 50ms tone
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
  } else if (distance > 50) {
    tone(buzzerPin, 500, 25);   // 25ms tone
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
  } else {
    tone(buzzerPin, 500);       // Continuous tone
    digitalWrite(ledPin, HIGH); // Continuous light
  }

  // Debugging: Print the distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100); // Small delay to stabilize readings
}


