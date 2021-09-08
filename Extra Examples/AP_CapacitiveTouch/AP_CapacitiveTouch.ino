#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10 megohm between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
 */

// Example from https://playground.arduino.cc/Main/CapacitiveSensor/

// 10 megaOhm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor cs1 = CapacitiveSensor(5,2);        
CapacitiveSensor cs2 = CapacitiveSensor(5,3);        
CapacitiveSensor cs3 = CapacitiveSensor(5,4);        

bool touch1, touch2, touch3;

void setup()                    
{
   //cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs1.set_CS_Timeout_Millis(100);
   cs2.set_CS_Timeout_Millis(100);
   cs3.set_CS_Timeout_Millis(100);
   Serial.begin(115200);
   Serial.println("Capacitive sensor starts");
   pinMode(13,OUTPUT);
}


void loop()                    
{
    long start = millis();
    long t1 = cs1.capacitiveSensor(5);
    long t2 = cs2.capacitiveSensor(5);
    long t3 = cs3.capacitiveSensor(5);

    const int tValue = 1000; // triggervalue to detect touch

isTouched(cs1);

    //long total1 = cs.capacitiveSensorRaw(10);
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug window spacing
    Serial.print(t1);                  // print sensor output 1
    Serial.print("\t");                    // tab character for debug window spacing
    Serial.print(t2);                  // print sensor output 1
    Serial.print("\t");                    // tab character for debug window spacing
    Serial.print(t3);                  // print sensor output 1
    Serial.println();                  // print sensor output 1
//    for (int i=0; i<total1; i++) {
//      digitalWrite(13,1);
//      delay(7);
//      digitalWrite(13,0);
//      delay(26);
//    }      
    delay(50);                             // arbitrary delay to limit data to serial port 
}

bool isTouched(CapacitiveSensor c) {
  if (c.capacitiveSensor(5) > 1000) {
    Serial.println("touched!");
  }
}
