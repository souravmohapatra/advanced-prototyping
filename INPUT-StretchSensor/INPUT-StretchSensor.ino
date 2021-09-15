/* Simple example for stretch sensor
 *  Author: Adrie
 *  Edited: Sourav
 *  
 *  This program reads the value across the register which changes when
 *  there is a stretch on the fabric. That value can then be used to
 *  perform any action.
 */

#define INPUT_PIN A0

int trigLevel = 300;
bool switchState = false;
float avg = 0.0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Function that calculates the amount of stretch. The exact value will depend on your usecase.
  float stretch = measureStretchAmount();

  // Print to the serial monitor
  Serial.print(stretch);
  Serial.println(" ");

  // Logic to implement when you detect that it is stretched
  performAction(stretch);

  // Delay between actions
  delay(50);
}

// Function to measure the amount of stretch. Change the filter response (fast or slow) as per your need.
float measureStretchAmount()
{
  int aVal = analogRead(INPUT_PIN);
  avg = 0.5 * avg + 0.5 * aVal;

  return avg;
}

// Function to implement any action based on the amount of stretch
void performAction(float stretch)
{
  static bool crossedTrigger = false;

  // A rather simple turn-on-led when stretched logic.
  if (stretch > trigLevel) {
    if (crossedTrigger == false)
      switchState = !switchState;
    crossedTrigger = true;
  } else {
    crossedTrigger = false;
  }

  digitalWrite(LED_BUILTIN, switchState);  
}
