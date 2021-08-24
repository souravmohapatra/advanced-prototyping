#include <Adafruit_NeoPixel.h>
#define NEOPIN 6 // Neopixel data pin
#define NEONUM 12 // How many pixels we have?

//See https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html

// Parameter 1 = number of pixels in strip
// Parameter 2 = datapin number (most are valid)
// Parameter 3 = pixel type flags, OR || to combine:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(23, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEONUM, NEOPIN, NEO_GRB);

int R, G, B; // Red Green and Blue values
byte Wshift = 24; // mickey mouse programming...
byte Rshift = 16;
byte Gshift = 8;
byte Bshift = 0;

int colors[NEONUM][3];
unsigned long C = 0; // Color for NeoPixels (combined RGB)
const int delayTime = 30; // delay between steps (milliseconds)
const int maxBrightness = 50;

void setup() {
  // Initialize all pixels to 'off'
  pixels.begin();
  pixels.show();
  Serial.begin(9600);
  pixels.setBrightness(maxBrightness);
  Serial.println("testFader Works (almost)");
  testFader();
}

void loop() {
  Serial.println("fadeInOut works");
  for (int fadeCount = 0; fadeCount < 3; fadeCount++) {
    fadeInOut();
  }

  Serial.println("changeColours not working yet"); //
  while (1) {
    changeColors();
    delay(delayTime);
  }
}

void changeColors() {
  int led = random(NEONUM);
  colors[led][0] += random(5) - 2;
  colors[led][0] = constrain(colors[led][0], 0, maxBrightness);
  colors[led][1] += random(5) - 2;
  colors[led][1] = constrain(colors[led][1], 0, maxBrightness);
  colors[led][2] += random(5) - 1;
  colors[led][2] = constrain(colors[led][2], 0, maxBrightness);

  pixels.setPixelColor(led, colors[led][0], colors[led][1], colors[led][2]);
  //pixels.setPixelColor(led, 100, 100, 100);

  delay(delayTime);
  pixels.show();
  delay(delayTime);

  if (Serial.available()) {
    for (int i = 0; i < NEONUM; i++) {
      for (int j = 0; j < 3; j++) {
        Serial.print(colors[i][j]);
        Serial.print(" ");
      }
      Serial.println();
    }
    Serial.read();
  }
}


void fadeInOut() {
  // Fade R, G, B and RGB
  fadeIn(Rshift);
  delay(100);
  fadeOut(Rshift);
  delay(100);
  fadeIn(Gshift);
  fadeOut(Gshift);
  delay(100);
  fadeIn(Bshift);
  fadeOut(Bshift);
  delay(100);
  fadeIn(Wshift);
  fadeOut(Wshift);
  delay(100);
}

void fadeIn(int shft) {
  Serial.println("FadeIn ");
  // step through brighness levels (255..0)
  for (long int brightness = 0; brightness < maxBrightness; brightness += 5) {
    // for all NEONUM neopixels
    for (int i = 0; i < NEONUM; i++) {
      if (shft == 24) { // don't support white
        pixels.setPixelColor(i, brightness, brightness, brightness);
      } else {
        pixels.setPixelColor(i, brightness << shft);
      }
      // show is necessary to activate the programmed light-scheme
      // (now the programmed values are transferred from computer memory to the actual pixels)
      pixels.show();
      delay(delayTime);
    }
  }
}

void fadeOut(int shft) {
  Serial.println("FadeOut ");
  // step through brighness levels (255..0)
  for (long int brightness = maxBrightness; brightness > 0; brightness -= 5) {
    // for all NEONUM neopixels
    for (int i = 0; i < NEONUM; i++) {
      if (shft == 24) { // don't support white
        pixels.setPixelColor(i, brightness, brightness, brightness);
      } else {
        pixels.setPixelColor(i, brightness << shft);
      }
      // show is necessary to activate the programmed light-scheme
      // (now the programmed values are transferred from computer memory to the actual pixels)
      pixels.show();
      delay(delayTime);
    }
  }
}

void testFader() {
  Serial.println("R");
  for (R = 0; R < maxBrightness; R++) {
    pixels.setPixelColor(0, R, G, B);
    pixels.show();
    delay(delayTime);
  }
  R = 0;
  pixels.setPixelColor(0, 0, 0, 0);

  Serial.println("G");
  for (G = 0; G < maxBrightness; G++) {
    pixels.setPixelColor(1, R, G, B);
    pixels.show();
    delay(delayTime);
  }
  G = 0;
  pixels.setPixelColor(1, 0, 0, 0);

  Serial.println("B");
  for (B = 0; B < maxBrightness; B++) {
    pixels.setPixelColor(2, R, G, B);
    pixels.show();
    delay(delayTime);
  }
  B = 0;
  pixels.setPixelColor(2, 0, 0, 0);

  Serial.println("W");
  for (R = 0; R < maxBrightness; R++) {
    G = R; B = R;
    pixels.setPixelColor(3, R, G, B);
    pixels.show();
    delay(delayTime);
  }
  R = 0; G = 0; B = 0;
  pixels.setPixelColor(3, 0, 0, 0);

}
