// The function that actually detects the touch of a sensor.
// As of now, no need to change the logic.

bool touchDetect(int num) {
  // Debug?
  bool DBG = false;
  
  // Some special Adrie-Magic to make the input more stable
  pinMode(pin[num], INPUT);
  int val = analogRead(pin[num]);
  pinMode(pin[num], OUTPUT);

  // Filter the values
  longAvg[num]  = (1.0 - longF) * longAvg[num] +  longF * val;
  if (val > longAvg[num]) // only track higher than avarage
    shortAvg[num] = (1.0 - shortF) * shortAvg[num] + shortF * val;

  float diff = abs(longAvg[num] - shortAvg[num]);

  
  if (DBG) {
    Serial.print(diff);
    Serial.print(" ");
  }

  // If greater than a trigger, turn on the LED and return true
  // else false
  if (abs(longAvg[num] - shortAvg[num]) > trigger) {
    digitalWrite(led, HIGH);
    if (DBG) {
      Serial.print(trigger * 2);
      Serial.print(" ");
    }
    return true;
  } else {
    digitalWrite(led, LOW);
    if (DBG) {
      Serial.print(trigger);
      Serial.print(" ");
    }
    return false;
  }
}
