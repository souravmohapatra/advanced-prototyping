// Swipe detect
// Detect (sequential) touches of multiple touch sensors. 
// 
// Detection of touches works, gesture detection still needs to be implemented. 
// See the capacitivetouchwswipe example (that uses external resistors)
//
// Adrie Kooijman, aug 2021

const int led = 25; // for Raspvberry pi pico.

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.println();
}


float longF = 0.001; // Filterfactor for long and short term averages
float shortF = 0.02;
float longAvg0, longAvg1;
float shortAvg0, shortAvg1;
int val;

float trigger = 20.0;

void loop() {
  val = analogRead(A0);
  longAvg0  = (1.0 - longF) * longAvg0 +  longF * val;
  if (val > longAvg0)
    shortAvg0 = (1.0 - shortF) * shortAvg0 + shortF * val;
  //  Serial.print(longAvg0);
  //  Serial.print(" ");
  //  Serial.print(shortAvg0);
  //  Serial.print(" ");
  Serial.print(abs(longAvg0 - shortAvg0));
  Serial.print(" ");

  if (abs(longAvg0 - shortAvg0) > trigger) {
    digitalWrite(led, HIGH);
  }

  val = analogRead(A1);
  longAvg1  = (1.0 - longF) * longAvg1 +  longF * val;
  if (val > longAvg1)
    shortAvg1 = (1.0 - shortF) * shortAvg1 + shortF * val;
  //  Serial.print(longAvg1);
  //  Serial.print(" ");
  //  Serial.print(shortAvg1);
  //  Serial.print(" ");
  Serial.print(abs(longAvg1 - shortAvg1));

  if (abs(longAvg1 - shortAvg1) > trigger) {
    digitalWrite(led, LOW);
  }

  Serial.println();
  delay(1);
}
