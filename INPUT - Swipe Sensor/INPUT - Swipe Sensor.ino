#include <CapacitiveSensor.h>

/*
   CapitiveSense Library Demo Sketch
   Paul Badger 2008
   Uses a high value resistor e.g. 10 megohm between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
   Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
*/

// Example from https://playground.arduino.cc/Main/CapacitiveSensor/
// Swipe detection based on https://docs.google.com/document/d/1OTrTXFR14CP84z4LUM0RPAmTBjanlfKHe6ips4blU7o/edit


// 10 megaOhm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor cs1 = CapacitiveSensor(5, 2);
CapacitiveSensor cs2 = CapacitiveSensor(5, 3);
CapacitiveSensor cs3 = CapacitiveSensor(5, 4);

bool touch1, touch2, touch3;

void setup() {
  //cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  cs1.set_CS_Timeout_Millis(100);
  cs2.set_CS_Timeout_Millis(100);
  cs3.set_CS_Timeout_Millis(100);
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  Serial.println("Capacitive sensor starts");
}


void loop() {
  swipeDetect();
  //Serial.println(millis());
  delay(10);                             // arbitrary delay to limit data to serial port
}


const int THRESHOLD = 1400;
const bool UPWARDS = true;
const bool DOWNWARDS = false;
bool prev1 = false;
bool prev2 = false;
bool prev3 = false;

int numberOfStrokes = 0;
bool strokes[3] = { false };
unsigned long gestureDetectionTimeout = 0;
bool wasReleaseDetected = false;
unsigned long releaseDetectionTimeout = 0;
bool releaseDirection;


void swipeDetect() {

  bool curr1 = touchRead(&cs1);
  bool curr2 = touchRead(&cs2);
  bool curr3 = touchRead(&cs3);

  bool isAny = curr1 || curr2 || curr3;
  bool wasAny = prev1 || prev2 || prev3;

  if (!isAny && wasAny && numberOfStrokes < 3) {
    Serial.println("!isAny&&waAny");
    wasReleaseDetected = true;
    releaseDetectionTimeout = millis() + 80;

    if (prev1 || prev2 || prev3) {
      releaseDirection = UPWARDS;
    } else {
      releaseDirection = DOWNWARDS;
    }
  }

  if (wasReleaseDetected && numberOfStrokes < 3 && millis() > releaseDetectionTimeout) {
    Serial.println("wasReleaseDetected");
    strokes[numberOfStrokes] = releaseDirection;
    numberOfStrokes++;
    gestureDetectionTimeout = millis() + 1000;

    // reset
    wasReleaseDetected = false;
  }

  if (numberOfStrokes > 0 && millis() > gestureDetectionTimeout) {
    Serial.println("numberOfStrokes");
    switch (numberOfStrokes) {
      case 1:
        if (strokes[0] == UPWARDS) {
          digitalWrite(LED_BUILTIN, HIGH);
        } else {
          digitalWrite(LED_BUILTIN, LOW);
        }

        delay(1000);
        break;

      case 2:
        digitalWrite(LED_BUILTIN, LOW);

        for (int i = 0; i < 2; i++) {
          digitalWrite(LED_BUILTIN, HIGH);
          delay(300);
          digitalWrite(LED_BUILTIN, LOW);
          delay(300);
        }

        delay(1000);
        break;

      case 3:
        digitalWrite(LED_BUILTIN, LOW);

        for (int i = 0; i < 3; i++) {
          digitalWrite(LED_BUILTIN, HIGH);
          delay(300);
          digitalWrite(LED_BUILTIN, LOW);
          delay(300);
        }

        delay(1000);
        break;
    }

    // reset
    numberOfStrokes = 0;
    //gestureDetectionTimeout = 0;
    wasReleaseDetected = false;
  }

  prev1 = curr1;
  prev2 = curr2;
  prev3 = curr3;
}


bool touchRead(CapacitiveSensor *c) {
  if (c->capacitiveSensor(5) > THRESHOLD) {
    Serial.println("touched!");
    return true;
  }
  return false;
}
