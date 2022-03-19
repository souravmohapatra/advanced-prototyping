// The function that actually detects the touch of a sensor.
// As of now, no need to change the logic.

bool touchDetect(int num) {
  // Debug?
  bool DBG = true;
  boolResult[num] = 0;
  
  // Some special magic to make the input more stable
  pinMode(pin[num], INPUT);
  int val = analogRead(pin[num]);
  pinMode(pin[num], OUTPUT);

  // Filter the values
  longAvg[num]  = (1.0 - longF) * longAvg[num] +  longF * val;
  if (val > longAvg[num]) // only track higher than avarage
    shortAvg[num] = (1.0 - shortF) * shortAvg[num] + shortF * val;

  float diff = abs(longAvg[num] - shortAvg[num]);
  if (diff < 80.0)
    diff = 50.0;

  result[num] = diff;

  // If greater than a trigger, turn on the LED and return true
  // else false
  if (diff > trigger) {
    digitalWrite(led, HIGH);
    boolResult[num] = 1;
    return true;
  } else {
    digitalWrite(led, LOW);
    boolResult[num] = 0;
    return false;
  }
  
  return false;
}
