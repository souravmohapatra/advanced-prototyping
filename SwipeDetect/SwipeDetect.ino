// Swipe detect
// Detect (sequential) touches of multiple touch sensors.
//
// Adrie Kooijman, Aug 2021
// Adrie Kooijman, Oct 2021
// Sourav Mohapatra, Oct 2021

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
  Serial.println();
}

// Filter params, no need to change
float longF = 0.001; // Filterfactor for long and short term averages
float shortF = 0.04;
float longAvg[3], shortAvg[3];
int pin[] = {A0, A1, A2};
int val;

// This is the trigger. Change it according to your need.
float trigger = 80.0;

void loop() {

  // Call the state machine. This function is present in the separate file.
  // If you want to change, open that file and do any changes. By default,
  // this file would be open in a tab in your Arduino IDE
  stateMachine();

  // If the state ends up at "swipeUp" then UP is detected
  if (mState == swipeUp) {
    Serial.println("Swipe UP detected");
    delay(5000); // Remember to remove this delay. This is just for demonstration purpose
    mState = idle;
  }

  // Otherwise DOWN is detected.
  if (mState == swipeDown) {
    Serial.println("Swipe DOWN detected");
    delay(5000); // Remember to remove this delay. This is just for demonstration purpose
    mState = idle;
  }
  
  delay(10);
}
