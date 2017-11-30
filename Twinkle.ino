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

#define BRIGHTNESS 150

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);

int delayval = 500; // delay for half a second

int alight_stars[200];
int star_intens[200];
int next_star = 0;

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

  int start_lights = 15;
  for (int i=0; i<start_lights; i++) {
    int rand_index = rand() % NUMPIXELS;
    int rand_intens = (rand() % 90) + 10;
    for(int i=0; i<rand_intens; i=i+3) {
      leds.setPixelColor(rand_index, leds.Color(i,i,i));
      alight_stars[next_star] = rand_index;
      star_intens[next_star] = rand_intens;
      next_star++;
      leds.show();
    }
  }
}

void loop() {
  int speed = (rand() % 4) + 2;
  
  if (rand() % 100 < 40) {
    int desiredIndex = rand() % NUMPIXELS;
    int old_color = (int)leds.getPixelColor(desiredIndex);
    int b = (old_color)&0xff;
    old_color = b;
    int new_color = rand() % 255;
  
    if (new_color < old_color) {  // dim
      for(int i=old_color; i>=new_color; i=i-speed) {
            leds.setPixelColor(desiredIndex, leds.Color(i,i,i));
            alight_stars[next_star] = desiredIndex;
            star_intens[next_star] = new_color;
            next_star = next_star++;
            leds.show();
          }
      } else {  // brighten
        for(int i=old_color; i<=new_color; i=i+speed) {
            leds.setPixelColor(desiredIndex, leds.Color(i,i,i));
            alight_stars[next_star] = desiredIndex;
            star_intens[next_star] = new_color;
            next_star = next_star++;
            leds.show();
        }
      }
    } else {  // remove existing light
      int dimming_light = rand() % next_star;
      int star_index = alight_stars[dimming_light];
      int old_intens = star_intens[dimming_light];
      int new_intens = rand() % (old_intens-10);
      star_intens[dimming_light] = new_intens;
      for(int i=old_intens; i>=new_intens; i=i-speed) {
            leds.setPixelColor(star_index, leds.Color(i,i,i));
            leds.show();
          }
    }

  
  
  
}
