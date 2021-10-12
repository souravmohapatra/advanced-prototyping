// Swipe detect
// Detect (sequential) touches of multiple touch sensors. 
// 
// Detection of touches works, gesture detection still needs to be implemented. 
// See the capacitivetouchwswipe example (that uses external resistors)
//
// Adrie Kooijman, aug 2021

enum swipeSensor {
  RIGHT_SENSOR = 0,
  MIDDLE_SENSOR = 1,
  LEFT_SENSOR = 2,
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  Serial.println();
}

float longF = 0.01; // Filterfactor for long and short term averages
float shortF = 0.2;
float longAvg[3];
float shortAvg[3];
float val[3];
int prev[3];

float trigger = 1500.0;

void loop() {
  // Measure the values from the sensors
  val[LEFT_SENSOR] = detectSwipe(LEFT_SENSOR, A0);
  val[MIDDLE_SENSOR] = detectSwipe(MIDDLE_SENSOR, A1);
  val[RIGHT_SENSOR] = detectSwipe(RIGHT_SENSOR, A2);

  // Perform any action
  if (val[LEFT_SENSOR] > trigger)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);

  // Optional print to the screen to visualize
  Serial.print(val[LEFT_SENSOR]); Serial.print(" ");
  Serial.print(val[MIDDLE_SENSOR] + 50); Serial.print(" ");
  Serial.print(val[RIGHT_SENSOR] + 100); Serial.print(" ");
  Serial.println();
  delay(5);
}

float detectSwipe(enum swipeSensor s, int pin)
{
  int sensorRead = analogRead(pin);
  int differential = sensorRead - prev[s];
  prev[s] = sensorRead;
  
  longAvg[s] = (1.0 - longF) * longAvg[s] +  longF * differential;
  
  if (differential > longAvg[s])
    shortAvg[s] = (1.0 - shortF) * shortAvg[s] + shortF * differential;

  return abs(longAvg[s] - shortAvg[s]);
}