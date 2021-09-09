// https://www.circuitbasics.com/how-to-make-an-arduino-capacitance-meter/
// Scroll to (CAPACITANCE METER FOR 470 UF TO 18 PF CAPACITORS)

// Adrie Kooijman, Aug 2021
// The idea is to measure capacitance using the RC time of a charging capacitor.
// R is in this case the internal pullup resistor of Arduino,
// C is the capacitance value of the button
// The absolute value is not important here, it's the change when the button is pressed.
// We have a matrix of four buttons, two lines are 'driver' lines connected to outputs,
// the other two are input lines.

//const int OUT_PIN = A2;
const int OUT1 = 2;
const int OUT2 = 3;
const int IN1 = A0;
const int IN2 = A1;

// The values are from the source, I did not bother to check correctness for raspberry pi pico.
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;
const int MAX_ADC_VALUE = 1023;

const int led = 25; // led is connected to this pin


void setup()
{
  pinMode(OUT1, OUTPUT);
  pinMode(IN1, OUTPUT); // !!
  pinMode(OUT2, OUTPUT);
  pinMode(IN2, OUTPUT); // !!
  pinMode(led, OUTPUT);
  Serial.begin(115200);
}

float val11, val21, val12, val22; // Current values row/column
float avg11, avg21, avg12, avg22; // Averages
float fac = 0.01; // Factor for exponential average filter
float trigger = 10.0; // If the current value is above average+trigger we think a button is pushed.

void loop()
{
  val11 = measureCap(IN1, OUT1, 0);
  avg11 = (1.0 - fac) * avg11 + fac * val11;
  val12 = measureCap(IN1, OUT2, 0);
  avg12 = (1.0 - fac) * avg12 + fac * val12;
  val21 = measureCap(IN2, OUT1, 0);
  avg21 = (1.0 - fac) * avg21 + fac * val21;
  val22 = measureCap(IN2, OUT2, 0);
  avg22 = (1.0 - fac) * avg22 + fac * val22;

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

  // Here we do something usefull with the information we have collected.
  if (val11 > (avg11 + trigger)) {
    digitalWrite(led, HIGH);
  }

  if (val21 > (avg21 + trigger)) {
    digitalWrite(led, LOW);
  }
}


// From the original source, 'large capacitor'function commented out.
float measureCap(int IN_PIN, int OUT_PIN, bool printIt) {
  float capacitance;
  if (printIt) {
    Serial.print(F("Measure between "));
    Serial.print(IN_PIN);
    Serial.print(F(" and "));
    Serial.print(OUT_PIN);
  }

  pinMode(IN_PIN, INPUT);
  digitalWrite(OUT_PIN, HIGH);
  int val = analogRead(IN_PIN);
  digitalWrite(OUT_PIN, LOW);

  if (val < 1000) {
    pinMode(IN_PIN, OUTPUT);

    capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);

    if (printIt) {
      Serial.print(F(", Capacitance Value = "));
      Serial.print(capacitance, 3);
      Serial.print(F(" pF ("));
      Serial.print(val);
      Serial.print(F(") "));
    }
  }

  //  else { // Only in the case of larger capacitances.
  //    Serial.print(F(", Large "));
  //    pinMode(IN_PIN, OUTPUT);
  //    delay(1);
  //    pinMode(OUT_PIN, INPUT_PULLUP);
  //    unsigned long u1 = micros();
  //    unsigned long t;
  //    int digVal;
  //
  //    do {
  //      digVal = digitalRead(OUT_PIN);
  //      unsigned long u2 = micros();
  //      t = u2 > u1 ? u2 - u1 : u1 - u2;
  //    } while ((digVal < 1) && (t < 400000L));
  //
  //    pinMode(OUT_PIN, INPUT);
  //    val = analogRead(OUT_PIN);
  //    digitalWrite(IN_PIN, HIGH);
  //    int dischargeTime = (int)(t / 1000L) * 5;
  //    delay(dischargeTime);
  //    pinMode(OUT_PIN, OUTPUT);
  //    digitalWrite(OUT_PIN, LOW);
  //    digitalWrite(IN_PIN, LOW);
  //
  //    capacitance = -(float)t / R_PULLUP
  //                  / log(1.0 - (float)val / (float)MAX_ADC_VALUE);
  //
  //    Serial.print(F("Capacitance Value = "));
  //    if (capacitance > 1000.0) {
  //      Serial.print(capacitance / 1000.0, 2);
  //      Serial.print(F(" uF"));
  //    } else {
  //      Serial.print(capacitance, 2);
  //      Serial.print(F(" nF"));
  //    }
  //
  //    Serial.print(F(" ("));
  //    Serial.print(digVal == 1 ? F("Normal") : F("HighVal"));
  //    Serial.print(F(", t= "));
  //    Serial.print(t);
  //    Serial.print(F(" us, ADC= "));
  //    Serial.print(val);
  //    Serial.println(F(")"));
  //  }

  while (millis() % 100 != 0);
  return capacitance;
}
