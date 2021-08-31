// https://www.circuitbasics.com/how-to-make-an-arduino-capacitance-meter/
// Scroll to (CAPACITANCE METER FOR 470 UF TO 18 PF CAPACITORS)

// Adrie Kooijman, Aug 2021
// The idea is to measure capacitance using the RC time of a charging capacitor.
// R is in this case the internal pullup resistor of Arduino,
// C is the capacitance value of the button
// The absolute value is not important here, it's the change when the button is pressed.
// We have a matrix of four buttons, two lines are 'driver' lines connected to outputs,
// the other two are input lines.

// Set to true to enable printing
const bool printIt = false;

// Pin mappings
const int OUT1 = 2;
const int OUT2 = 3;
const int IN1 = A0;
const int IN2 = A1;
const int led = LED_BUILTIN;

// Constants used in the calculation of the capacitance.
const int LOW_CAPACITANCE_THRESHOLD = 1000;
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;
const int MAX_ADC_VALUE = 4096;

// Variable declarations
float val11, val21, val12, val22; // Current values row/column
float avg11, avg21, avg12, avg22; // Averages
float expFactor = 0.01; // expFactortor for exponential average filter
float threshold = 1.0; // If the current value is above average + threshold we think a button is pushed.

void setup()
{
  pinMode(OUT1, OUTPUT);
  pinMode(IN1, OUTPUT); // !!
  pinMode(OUT2, OUTPUT);
  pinMode(IN2, OUTPUT); // !!
  pinMode(led, OUTPUT);
  Serial.begin(115200);

  // Permeate the circuit with a longer pulse - just a one time thing
  calibrate();

  // Get the initial measurement after calibration
  avg11 = measureCap(IN1, OUT1);
  avg12 = measureCap(IN1, OUT2);
  avg21 = measureCap(IN2, OUT1);
  avg22 = measureCap(IN2, OUT2);
}

void loop()
{
  // Get the capacitance for all 4 buttons
  val11 = measureCap(IN1, OUT1);
  val12 = measureCap(IN1, OUT2);
  val21 = measureCap(IN2, OUT1);
  val22 = measureCap(IN2, OUT2);

  // Calculate the filtered values for the capacitances for each button
  avg11 = exponentialAverageFilter(avg11, val11);
  avg12 = exponentialAverageFilter(avg12, val12);
  avg21 = exponentialAverageFilter(avg21, val21);
  avg22 = exponentialAverageFilter(avg22, val22);

  // Send to serial - for plotter
  plotValues();

  // Here we do something useful with the information we have collected - place to innovate!
  if (val11 > (avg11 + threshold)) {
    digitalWrite(led, HIGH);
  }

  if (val21 > (avg21 + threshold)) {
    digitalWrite(led, LOW);
  }
}

void calibrate()
{
  int count = 0;
  digitalWrite(OUT1, HIGH);
  digitalWrite(OUT2, HIGH);
  
  while (count++ < 20) {
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
  }
  
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, LOW);
}

/*
 * exponentialAverageFilter() - A very basic exponential filtering algorithm
 *
 * prevVal: The previous value of the filtered signal
 * nextVal: The next value that has to be filtered and put
 *
 * Returns: The filtered output
 */
static inline float exponentialAverageFilter(float prevVal, float nextVal)
{
  return (1.0 - expFactor) * prevVal + expFactor * nextVal;
}

/*
 * plotValues() - Helper function to plot the values in SerialPlotter tool
 *
 * Returns: None
 */
void plotValues()
{
  // Print results, add offsets for visyalisation in serial plotter
  Serial.print(avg11);
  Serial.print(" ");
  Serial.print(val11);
  Serial.print(" ");
  Serial.print(avg12 + 2); // add a value (2) to separate the resulting lines in serial plotter.
  Serial.print(" ");
  Serial.print(val12 + 2);
  Serial.print(" ");
  Serial.print(avg21 + 4);
  Serial.print(" ");
  Serial.print(val21 + 4);
  Serial.print(" ");
  Serial.print(avg22 + 6);
  Serial.print(" ");
  Serial.print(val22 + 6);
  Serial.print(" ");
  Serial.println();
}

/*
 * measureCap() - Function to measure the capacitance of between the
 *                two pins specified in the parameters.
 *
 * inputPin: The pin where the input probe is attached
 * outputPin: The pin where the output probe is attached
 *
 * Returns: The capacitance value between the pins
 */
float measureCap(int inputPin, int outputPin)
{
  float capacitance = 0.0f;

  if (printIt) {
    Serial.print(F("Measure between "));
    Serial.print(inputPin);
    Serial.print(F(" and "));
    Serial.print(outputPin);
  }

  // Monitor the input pin
  pinMode(inputPin, INPUT);
  
  // Send a momentary pulse and measure the change in value
  digitalWrite(outputPin, HIGH);
  int val = analogRead(inputPin);
  digitalWrite(outputPin, LOW);

  // Check if the reading is less than the constant, calculate the actual value
  if (val < LOW_CAPACITANCE_THRESHOLD) {
    pinMode(inputPin, OUTPUT);

    capacitance = (float) val * IN_CAP_TO_GND / (float) (MAX_ADC_VALUE - val);

    if (printIt) {
      Serial.print(F(", Capacitance Value = "));
      Serial.print(capacitance, 3);
      Serial.print(F(" pF ("));
      Serial.print(val);
      Serial.print(F(") "));
    }
  }



  while (millis() % 100 != 0);
  return capacitance;
}
