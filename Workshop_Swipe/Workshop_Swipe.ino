/*
 * Example code for a swipe sensor. The logic of the code is sensor agnostic
 * although the implementation for each sensor needs to be changed.
 *
 * ~ Sourav Mohapatra
 *
 */

#include "Ultrasonic.h"

// Define the states of the state machine
enum state_machine {
  STATE_START,
  STATE_1,
  STATE_2,
  STATE_3,
  STATE_4,
};

// Any PIN definitions
#define SENSORPIN   2

// Give physical definitions to the state.
// In this case it is for an ultrasonic sensor
#define LEFT_STATE 30
#define MIDDLE_STATE 20
#define RIGHT_STATE 10
#define BUFFER 3

// Init the sensor if any
Ultrasonic ultrasonic(SENSORPIN);
enum state_machine machine;

void setup() {
  Serial.begin(9600);
  machine = STATE_START;
}
 
static inline int fetchData()
{
  return ultrasonic.MeasureInCentimeters();
}

void stateMachine(int value)
{
  switch (machine) {
    case STATE_START:
      if (value < LEFT_STATE) {
        Serial.println("Crossed state 1");
        machine = STATE_1;
      }
      break;

    case STATE_1:
      if (value < MIDDLE_STATE) {
        Serial.println("Crossed state 2");
        machine = STATE_2;
      }
      break;

    case STATE_2:
      if (value < RIGHT_STATE) {
        Serial.println("Crossed state 3");
        machine = STATE_3;
      }
      break;
    
    case STATE_3:
      Serial.println("Swiped RIGHT\n");
      machine = STATE_4;
      break;

    case STATE_4:
      // Reset the state
      if (value > 200)
        machine = STATE_START;
      break;
  }
}

void loop() {
  int value = fetchData();

  //Serial.println(value);
  stateMachine(value);
  delay(50);
}
