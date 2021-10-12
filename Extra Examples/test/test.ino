#include <Keyboard.h>
#include <Mouse.h>

// Send some data to the connected PC emulating a keyboard ( Try excel for example)
// Move the mouse to a programmed position
// Just a demonstrator
// *** It is recommended to use a control system to turn this functionality on,     ***
// *** like a physical switch or only responding to specific input you can control. ***
// *** Refer to the Mouse and Keyboard examples for some ways to handle this.       ***
//
// See also 
// https://www.arduino.cc/reference/en/language/functions/usb/keyboard/
// https://www.arduino.cc/reference/en/language/functions/usb/mouse/
// https://www.arduino.cc/en/Reference/KeyboardModifiers
//
// *** Very Experimantal, might not work as expected!!!

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Keyboard");
  delay(500);
  Keyboard.begin();
  delay(500);
  // Does not work ...
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_TAB);
  delay(100);
  Keyboard.releaseAll();
  delay(500);

  // Works, but often seems to miss the first line?
  for (int i = 0; i < 10; i++) {
    // put your main code here, to run repeatedly:
    Keyboard.print("count\t");
    Keyboard.println(i);
    delay(500);
  }
  Keyboard.end();

  Mouse.begin();

  //Works
  Serial.println("Mouse");
  for (int x = 100; x < 500; x += 500) { // So far only the last (500,500) move seems to be executed
    for (int y = 100; y < 500; y += 500) {
      Mouse.move(x, y);
      delay(1000);
    }
    Mouse.click(MOUSE_LEFT); // does not seem to work this way.
    delay(5000);
  }

  // pac-man (Does not work yet ...)
  Keyboard.press('a');
  delay(500);
  Keyboard.releaseAll();
  Keyboard.press('s');
  delay(500);
  Keyboard.releaseAll();
  Keyboard.press('a');
  delay(500);
  Keyboard.press('s');
  delay(500);
  Keyboard.print('d');
  delay(500);
  Mouse.end();
  delay(500);
  Serial.println("Done!");
}


void loop() {
}

// It may be a good idea to move the carett to the comment space below
// That way your software will not destroy your code (hopefully)
/*
  0
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
