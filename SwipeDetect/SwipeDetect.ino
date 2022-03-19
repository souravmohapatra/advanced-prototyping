// Swipe detect
// Detect (sequential) touches of multiple touch sensors.
//
// Adrie Kooijman, Aug 2021
// Adrie Kooijman, Oct 2021
// Sourav Mohapatra, Oct 2021

#include <Adafruit_NeoPixel.h>
#define NEOPIN 6 // Neopixel data pin
#define NEONUM 1 // How many pixels we have?
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEONUM, NEOPIN, NEO_GRB);

const int led = 25; // for Raspberry pi pico.

// The state machine states. No need to change these
enum states {idle, touchedA0, touchedA1, touchedA2, swipeUp, swipeDown} mState;
enum direct {undefined, up, down} upDown;

// Run once, no need to change
void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pixels.begin();
  pixels.show();
  pixels.setBrightness(255);
  Serial.println();
}

// Filter params, no need to change
float longF = 0.001;
float shortF = 0.04;
float longAvg[3], shortAvg[3];
int pin[] = {A0, A1, A2};
int result[] = {0,0,0};
int boolResult[] = {0,0,0};
int val;

// This is the trigger. Change it according to your need.
float trigger = 85.0;

void loop() {
  touchDetect(0);
  touchDetect(1);
  touchDetect(2);

//  int _tmp = 0;
//  Serial.println(_tmp);
  Serial.print(boolResult[0]); Serial.print(" ");
  Serial.print(boolResult[1]); Serial.print(" ");
  Serial.print(boolResult[2]); Serial.println(" ");

  // Call the state machine. This function is present in the separate file.
  // If you want to change, open that file and do any changes. By default,
  // this file would be open in a tab in your Arduino IDE
  stateMachine();

  // If the state ends up at "swipeUp" then UP is detected
  if (mState == swipeUp) {
    Serial.println("Swipe UP detected");
    reset();
    glowLED(255, 0, 0);
    delay(500);
    mState = idle;
  }

  // Otherwise DOWN is detected.
  if (mState == swipeDown) {
    Serial.println("Swipe DOWN detected");
    reset();

    // Experiment with this to change the colors. The parameters
    glowLED(0, 255, 0);
    delay(500);
    mState = idle;
  }
  
  delay(10);
}

void glowLED(float R, float G, float B)
{
  for (int j = 0; j < 3; j++) {
    for (float i = 0.0; i < 255.0; i++) {
      pixels.setPixelColor(0, (int)(R * (i / 255)), (int)(G * (i / 255)), (int)(B * (i / 255)));
//      pixels.setPixelColor(0, i, 0, 0);
      pixels.show();
      delay(2);
    }
    delay(50);
    for (float i = 255.0; i > 0.0; i--) {
      pixels.setPixelColor(0, (int)(R * (i / 255)), (int)(G * (i / 255)), (int)(B * (i / 255)));
//      pixels.setPixelColor(0, i, 0, 0);
      pixels.show();
      delay(2);
    }
    delay(50);
  }

  pixels.setPixelColor(0, 0, 0, 0);
  pixels.show();
}

void reset()
{
    boolResult[0] = 0;
    boolResult[1] = 0;
    boolResult[2] = 0;
    longAvg[0] = 0;
    longAvg[1] = 0;
    longAvg[2] = 0;
    shortAvg[0] = 0;
    shortAvg[1] = 0;
    shortAvg[2] = 0;
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
}
