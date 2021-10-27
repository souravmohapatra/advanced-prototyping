unsigned long timeOut;

// The logic in the state machine. Try to understand
// the logic. It will help you perform more complicated
// actions if needed.
void stateMachine() {
  switch (mState) {
    case idle:
      if (touchDetect(0)) {
        Serial.println("idle touchA0"); //
        timeOut = millis() + 500;
        mState = touchedA0;
        upDown = up;
      }
      if (touchDetect(2)) {
        Serial.println("idle touchA2"); //
        timeOut = millis() + 500;
        mState = touchedA2;
        upDown = down;
      }
      break;

    case touchedA0:
      if (millis() > timeOut) {
        Serial.println("touchedA0 timeOut"); //
        mState = idle;
        upDown = undefined;
      }

      if (touchDetect(1)) {
        Serial.println("touchedA0 touchA1"); //
        timeOut = millis() + 500;
        mState = touchedA1;
      }
      break;

    case touchedA1:
      if (millis() > timeOut) {
        Serial.println("touchedA1 timeOut"); //
        mState = idle;
        break;
      }
      if (upDown == up && touchDetect(2)) {
        Serial.println("touchedA1 touchA2, swipe UP"); //
        mState = swipeUp;
      }

      if (upDown == down && touchDetect(0)) {
        Serial.println("touchedA1 touchA0, swipe DOWN"); //
        mState = swipeDown;
      }
      break;

    case touchedA2:
      if (millis() > timeOut) {
        Serial.println("touchedA2 timeOut"); //
        mState = idle;
        upDown = undefined;
        break;
      }

      if (touchDetect(1)) {
        Serial.println("touchedA2 touchA1"); //
        timeOut = millis() + 500;
        mState = touchedA1;
        break;
      }

      break;
  }
}
