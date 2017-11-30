// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            22

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      256

#define BRIGHTNESS 100

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  leds.setBrightness(BRIGHTNESS);
  leds.begin();
  leds.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);

  int num_of_lights = 80;
  for (int i=0; i<num_of_lights; i++) {
    int rand_index = rand() % 256;
    int intens = rand()%255;
    leds.setPixelColor(rand_index, leds.Color(intens,intens,intens));
    leds.show();
  }
}

void loop() {
  
}


