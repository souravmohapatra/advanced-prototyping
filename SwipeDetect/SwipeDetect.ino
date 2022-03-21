/*
 * Swipe Sensor - Detect swipes in both direction.
 * Change the threshold to work in different scenarios.
 * Also might need to change the filter params according
 * to the surface where the soft sensor is kept.
 * 
 * glowLED(R, G, B) - Call this function with RGB values to
 * glow the NeoPixel (RGB values between 0 - 255)
 * 
 * Note: Code marked inside "###" are meant to be experimented.
 * Feel free to change and explore.
 * 
 * ~ Sourav Mohapatra, 2022
 */

#include <Adafruit_NeoPixel.h>
#define NEOPIN 6 // Neopixel data pin
#define NEONUM 1 // How many pixels we have?
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEONUM, NEOPIN, NEO_GRB);
enum states {idle, touchedA0, touchedA1, touchedA2, swipeUp, swipeDown} mState;
enum direct {undefined, up, down} upDown;
const int led = 25; // for Raspberry pi pico.
// Filter params, no need to change
float longF = 0.1;
float shortF = 0.004;
float longAvg[3], shortAvg[3];
int pin[] = {A0, A1, A2};
int result[] = {0,0,0};
int boolResult[] = {0,0,0};
int val;
long int count = 0;
short unsigned int upCount = 0, downCount = 0;
short unsigned int upTime = 0, downTime = 0;
bool ledGlowed = false;

/* ##################################################################################### */
// This is the trigger. Change it according to your environment
float trigger = 17.0;

// Start with a value of true to just plot values. Then change to
// false to start the swipe detection
const bool isTestCode = false;
/* ##################################################################################### */

// Run once, no need to change
void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pixels.begin();
  pixels.show();
  pixels.setBrightness(255);
  Serial.println();

  unsigned long _tmp = millis();
  while (millis() - _tmp < 2000) {
    touchDetect(0);
    touchDetect(1);
    touchDetect(2);
  }
}

void loop() {
  ledGlowed = false;
  touchDetect(0);
  touchDetect(1);
  touchDetect(2);

  if (isTestCode) {
    Serial.print(result[0]); Serial.print(" ");
    Serial.print(result[1]); Serial.print(" ");
    Serial.print(result[2]); Serial.println(" ");
  } else {
    Serial.print(boolResult[0]); Serial.print(" ");
    Serial.print(boolResult[1]); Serial.print(" ");
    Serial.print(boolResult[2]); Serial.println(" ");
  }

  if (!isTestCode)
    stateMachine();

  if (mState == swipeUp) {
    upCount++;
    upTime = millis();
  } else if (mState == swipeDown) {
    downCount++;
    downTime = millis();
  }

/* ##################################################################################### */
  if (upCount == 1 && downCount == 1) {
    glowLED(255, 92, 245);
    upCount = 0;
    downCount = 0;
  }
  
  if (upCount == 3) {
    glowLED(0, 255, 255);
    upCount = 0;
  }

  if (downCount == 3) {
    glowLED(255, 255, 0);
    downCount = 0;
  }
/* ##################################################################################### */

  if (millis() - upTime > 10000)
    upCount = 0;

  if (millis() - downTime > 10000)
    downCount = 0;

  if (ledGlowed) {
    reset();
    mState = idle;
    unsigned long _tmp = millis();
    while (millis() - _tmp < 200) {
      touchDetect(0);
      touchDetect(1);
      touchDetect(2);
    }
    return;
  }

  // If the state ends up at "swipeUp" then UP is detected
  if (mState == swipeUp) {
    Serial.println("Swipe UP detected");
    reset();

/* ##################################################################################### */
    // Experiment with this to change the colors. The parameters are R, G, B
    // values with brightness range from 0 to 255
    glowLED(255, 0, 0);
/* ##################################################################################### */
    
    delay(100);
    mState = idle;
  }

  // Otherwise DOWN is detected.
  if (mState == swipeDown) {
    Serial.println("Swipe DOWN detected");
    reset();

/* ##################################################################################### */
    // Experiment with this to change the colors. The parameters are R, G, B
    // values with brightness range from 0 to 255
    glowLED(0, 255, 0);
/* ##################################################################################### */

    delay(100);
    mState = idle;
  }
  
  delay(10);
}

void glowLED(float R, float G, float B)
{
  ledGlowed = true;
  for (int j = 0; j < 2; j++) {
    for (float i = 0.0; i < 255.0; i++) {
      pixels.setPixelColor(0, (int)(R * (i / 255)), (int)(G * (i / 255)), (int)(B * (i / 255)));
      pixels.show();
      delay(2);
    }
    delay(100);
    for (float i = 255.0; i > 0.0; i--) {
      pixels.setPixelColor(0, (int)(R * (i / 255)), (int)(G * (i / 255)), (int)(B * (i / 255)));
      pixels.show();
      delay(2);
    }
    delay(100);
  }

  pixels.setPixelColor(0, 0, 0, 0);
  pixels.show();

  unsigned long _tmp = millis();
  while (millis() - _tmp < 200) {
    touchDetect(0);
    touchDetect(1);
    touchDetect(2);
  }
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
