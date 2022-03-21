/*
 * Primary state machine logic. There should be no need
 * to change the code here.
 * 
 * ~ Sourav Mohapatra, 2022
 */

unsigned long timeOut;
#define TIMEOUT_CONST 2000

void stateMachine() {
  switch (mState) {
    case idle:
      if (boolResult[0]) {
        Serial.println("idle touchA0");
        timeOut = millis() + TIMEOUT_CONST;
        mState = touchedA0;
      }
      
      if (boolResult[1]) {
        Serial.println("idle touchA1");
        timeOut = millis() + TIMEOUT_CONST;
        mState = touchedA1;
      }

      if (boolResult[2]) {
        Serial.println("idle touchA2");
        timeOut = millis() + TIMEOUT_CONST;
        mState = touchedA2;
      }
      break;

    case touchedA0:
      if (millis() > timeOut) {
        Serial.println("touchedA0 timeOut");
        mState = idle;
        break;
      }

      if (boolResult[0] == 0) {
        Serial.println("tap A0 complete");
        timeOut = millis() + TIMEOUT_CONST;
        mState = idle;
        tapCount[0]++;
      }
      break;

    case touchedA1:
      if (millis() > timeOut) {
        Serial.println("touchedA1 timeOut");
        mState = idle;
        break;
      }
      
      if (boolResult[1] == 0) {
        Serial.println("tap A1 complete");
        timeOut = millis() + TIMEOUT_CONST;
        mState = idle;
        tapCount[1]++;
      }
      break;

    case touchedA2:
      if (millis() > timeOut) {
        Serial.println("touchedA2 timeOut");
        mState = idle;
        break;
      }
      
      if (boolResult[2] == 0) {
        Serial.println("tap A1 complete");
        timeOut = millis() + TIMEOUT_CONST;
        mState = idle;
        tapCount[2]++;
      }
      break;
  }
}
