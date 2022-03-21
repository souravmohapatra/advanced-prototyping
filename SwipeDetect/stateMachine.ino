/*
 * Primary state machine logic. There should be no need
 * to change the code here.
 * 
 * ~ Sourav Mohapatra, 2022
 */

unsigned long timeOut;
#define TIMEOUT_CONST 1000

void stateMachine() {
  switch (mState) {
    case idle:
      if (boolResult[0]) {
        Serial.println("idle touchA0");
        timeOut = millis() + TIMEOUT_CONST;
        mState = touchedA0;
        upDown = up;
      }
      if (boolResult[2]) {
        Serial.println("idle touchA2");
        timeOut = millis() + TIMEOUT_CONST;
        mState = touchedA2;
        upDown = down;
      }
      break;

    case touchedA0:
      if (millis() > timeOut) {
        Serial.println("touchedA0 timeOut");
        mState = idle;
        upDown = undefined;
      }

      if (boolResult[1]) {
        Serial.println("touchedA0 touchA1");
        timeOut = millis() + TIMEOUT_CONST;
        mState = touchedA1;
      }
      break;

    case touchedA1:
      if (millis() > timeOut) {
        Serial.println("touchedA1 timeOut");
        mState = idle;
        break;
      }
      if (upDown == up && boolResult[2]) {
        Serial.println("touchedA1 touchA2, swipe UP");
        mState = swipeUp;
      }

      if (upDown == down && boolResult[0]) {
        Serial.println("touchedA1 touchA0, swipe DOWN");
        mState = swipeDown;
      }
      break;

    case touchedA2:
      if (millis() > timeOut) {
        Serial.println("touchedA2 timeOut");
        mState = idle;
        upDown = undefined;
        break;
      }

      if (boolResult[1]) {
        Serial.println("touchedA2 touchA1");
        timeOut = millis() + TIMEOUT_CONST;
        mState = touchedA1;
        break;
      }

      break;
  }
}
