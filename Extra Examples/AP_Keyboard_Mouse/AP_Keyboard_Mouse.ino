#include <Keyboard.h>
#include <Mouse.h>

#define OFFSETX 100
#define OFFSETY 100

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Keyboard");
  delay(5000); // Delay to open up paint
  Keyboard.begin();
  //Mouse.begin();

  Keyboard.print('w');
  
  delay(1000);
  Keyboard.print('a');
  
  delay(1000);
  Keyboard.print('s');
  
  delay(1000);
  Keyboard.print('d');
  
  delay(1000);
  //Mouse.end();
  Keyboard.end();
}

void loop() {
  exit(0);
}

// It may be a good idea to move the carett to the comment space below
// That way your software will not destroy your code (hopefully)
/*
  0wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
  count 1
  count 2
  count 3
  count 4
  count 5
  count 6
  count 7
  count 8
  count 9
  
*/
