// Copied from https://wiki.seeedstudio.com/Grove-Speaker/
// (should also test the Arduin tone() library

/*macro definition of Speaker pin*/
#define SPEAKER 8

int toneList[] = {1911, 1702, 1516, 1431, 1275, 1136, 1012, 902, 803}; //bass 1~7
int toneTime = 200; // how long to sustain the note
int waitTime = 50; // how much delay between notes

void setup() {
  pinInit();
}

void loop() {
  /*sound bass 1~7*/
  int numberOfNotes = sizeof(toneList) / sizeof(toneList[0]);
  for (int note_index = 0; note_index < numberOfNotes; note_index++)
  {
    sound(note_index);
    delay(waitTime);
  }
  while (1); // pause forever - comment this line to loop forever ...
}

void pinInit() {
  pinMode(SPEAKER, OUTPUT);
  digitalWrite(SPEAKER, LOW);
}

void sound(uint8_t note_index) {
  unsigned long startTime = millis();
  while (millis() < startTime + toneTime) {
    digitalWrite(SPEAKER, HIGH);
    delayMicroseconds(toneList[note_index]);
    digitalWrite(SPEAKER, LOW);
    delayMicroseconds(toneList[note_index]);

    
  }
}
