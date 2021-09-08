// https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody

/* Melody
  Plays a melody using the arduino tone function.
  circuit:
  - 8 ohm speaker on digital pin 8
  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C3, NOTE_G2, NOTE_G2, NOTE_A2, NOTE_G2, 0, NOTE_B2, NOTE_C3, 0,
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4, 0, 
  NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, 0, NOTE_B4, NOTE_C5, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4, 4, 
  4, 8, 8, 4, 4, 4, 4, 4, 4, 
  4, 8, 8, 4, 4, 4, 4, 4, 4
};

const int tonePin = 6;
void setup() {
  int numberOfNotes = sizeof(melody) / sizeof(melody[0]);

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < numberOfNotes; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(tonePin, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(tonePin);
  }
}

void loop() {
  // no need to repeat the melody.
}
