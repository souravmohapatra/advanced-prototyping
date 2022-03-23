/*
 * Swipe Sensor - Detect swipes in both direction.
 * Change the threshold to work in different scenarios.
 * Also might need to change the filter params according
 * to the surface where the soft sensor is kept.
 * 
 * glowLED(R, G, B) - Call this function with RGB values to
 * glow the NeoPixel (RGB values between 0 - 255)
 * 
 * Note: Feel free to change and explore the code in this
 * file.
 * 
 * ~ Sourav Mohapatra, 2022
 */

#include <Adafruit_NeoPixel.h>

#define NEOPIN 6
#define NEONUM 1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEONUM, NEOPIN, NEO_GRB);

/* For the state machine */
enum states {
  idle, 
  touchedA0, 
  touchedA1, 
  touchedA2, 
} mState;


float longAvg[3], shortAvg[3];
int pin[] = {A0, A1, A2};
int result[] = {0,0,0};
int boolResult[] = {0,0,0};
int tapCount[] = {0, 0, 0};
long int count = 0;

// This is the trigger. Change it according to your environment
float trigger = 18.0;

float longF = 0.2; // INCREASE or DECREASE when needed
float shortF = 0.1; // INCREASE or DECREASE when needed

void setup()
{
  Serial.begin(115200);
  pixels.begin();
  pixels.show();
  pixels.setBrightness(255);
  Serial.println();
  _stall();
}

void loop()
{
  touchDetect(0);
  touchDetect(1);
  touchDetect(2);

  Serial.print(result[0]); Serial.print(" ");
  Serial.print(result[1]); Serial.print(" ");
  Serial.print(result[2]); Serial.print(" ");

  Serial.print("\t\t"); Serial.print(tapCount[0]);
  Serial.print(" "); Serial.print(tapCount[1]);
  Serial.print(" "); Serial.println(tapCount[2]);

  stateMachine();

  if (tapCount[0] % 3 == 0 && tapCount[0]) {
    glowLED(255, 0, 0);
    tapCount[0] = 0;
  }

  if (tapCount[1] % 3 == 0 && tapCount[1]) {
    glowLED(0, 255, 0);
    tapCount[1] = 0;
  }

  if (tapCount[2] % 3 == 0 && tapCount[2]) {
    glowLED(0, 0, 255);
    tapCount[2] = 0;
  }
  
  delay(10);
}

void glowLED(float R, float G, float B)
{
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
  _stall();
}

static inline void _stall()
{
  unsigned long _tmp = millis();
  while (millis() - _tmp < 500) {
    touchDetect(0);
    touchDetect(1);
    touchDetect(2);
  }  
}
