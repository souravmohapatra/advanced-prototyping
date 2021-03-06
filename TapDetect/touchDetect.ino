/*
 * Actual sensor detection logic. There should be no reason
 * to change the code here.
 * 
 * ~ Sourav Mohapatra, 2022
 */

bool touchDetect(int num) {
  count++;
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
  result[num] = diff;

  // If greater than a trigger, turn on the LED and return true
  // else false
  if (diff > trigger) {
    boolResult[num] = 1;
    return true;
  } else {
    boolResult[num] = 0;
    return false;
  }
}
