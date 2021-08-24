// Use a reference resistor in series with your sensor.
// Connect the reference resistor to 5V, 
// connect the sensor to GND
// connect the sensor/reference resistors other side to A0

void setup() {
  Serial.begin(115200);
}

const float Rref = 10000.0; // reference resistor
const int maxCounts = 1024; // Arduino 10 bit A/D

void loop() {
  int aVal = analogRead(A0);
  float Rx = Rref * aVal / (maxCounts - aVal);
  if (Rx < 10000) { // ignore outliers
    Serial.println(Rx);
    
  }
  delay(250);
}
