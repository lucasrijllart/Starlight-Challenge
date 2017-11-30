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

  union_j();

  clear_and_logo();
}

void loop() {

  
}

void union_j() {
  int r[110] = {0, 7, 8, 9, 15, 17, 18, 23, 26, 27, 31, 35, 36, 39, 44, 45, 47, 54, 55, 56, 57, 58,
  59, 60, 61, 62, 63, 64, 70, 71, 72, 77, 78, 80, 84, 85, 88, 91, 92, 96, 98, 99, 104, 106, 112, 113,
  120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 144, 146,
  147, 152, 155, 156, 160, 164, 165, 168, 173, 174, 176, 182, 183, 184, 191, 192, 193, 194, 195, 196,
  197, 198, 199, 206, 207, 213, 215, 220, 221, 223, 227, 228, 231, 234, 235, 239, 241, 242, 247, 248,
  249, 255};
  int b[100] = {2, 3, 4, 5, 11, 12, 13, 16, 20, 21, 24, 25, 29, 32, 33, 34, 40, 41, 42, 43, 66, 67,
  68, 69, 74, 75, 76, 82, 83, 87, 90, 94, 95, 101, 102, 103, 108, 109, 110, 111, 148, 149, 150, 151,
  157, 158, 159, 162, 166, 167, 170, 171, 175, 178, 179, 180, 186, 187, 188, 189, 208, 209, 210, 211,
  217, 216, 218, 224, 225, 229, 232, 236, 237, 243, 244, 245, 250, 251, 252, 253};
  int w[100] = {1, 6, 10, 14, 19, 22, 28, 30, 37, 38, 46, 48, 49, 50, 51, 52, 53, 65, 73, 79, 81,
  86, 89, 93, 97, 100, 105, 107, 114, 115, 116, 117, 118, 119, 138, 139, 140, 141, 142, 143, 145, 153,
  154, 161, 163, 169, 172, 177, 181, 185, 190, 200, 201, 202, 203, 204, 205, 212, 214, 219, 222, 226,
  230, 233, 238, 240, 246, 254};

  for (int i=0; i<110; i++) {
    red(r[i]);
  }
  for (int i=0; i<100; i++) {
    blue(b[i]);
  }
  for (int i=0; i<100; i++) {
    white(w[i]);
  }
  leds.show();
  delay(10000);
}

void red(int index) {
  leds.setPixelColor(index, leds.Color(0,255,0));
}

void blue(int index) {
  leds.setPixelColor(index, leds.Color(0,0,255));
}

void white(int index) {
  leds.setPixelColor(index, leds.Color(255,255,255));
}

void clear_and_logo() {
  int logo[71] = {10, 11, 12, 13, 14, 15, 72, 19, 80, 27, 29, 30, 31, 88, 89, 90, 91, 35, 38, 97,
  99, 43, 46, 105, 108, 51, 54, 113, 116, 59, 60, 61, 62, 63, 120, 124, 195, 198, 129, 132, 203, 206,
  207, 136, 137, 138, 139, 211, 214, 146, 148, 219, 222, 154, 156, 227, 230, 162, 165, 235, 238,
  169, 170, 171, 173, 246, 181, 254, 188, 189, 190};

  colorWipe(leds.Color(0,0,0), 0);

  for(int i=0; i<71; i++) {
    leds.setPixelColor(logo[i], leds.Color(255,255,255));
    leds.show();
  }
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  int maskArray[256] = {0,1,2,3,4,5,6,7,64,65,66,67,68,69,70,71,
8,9,10,11,12,13,14,15,72,73,74,75,76,77,78,79,
16,17,18,19,20,21,22,23,80,81,82,83,84,85,86,87,
24,25,26,27,28,29,30,31,88,89,90,91,92,93,94,95,
32,33,34,35,36,37,38,39,96,97,98,99,100,101,102,103,
40,41,42,43,44,45,46,47,104,105,106,107,108,109,110,111,
48,49,50,51,52,53,54,55,112,113,114,115,116,117,118,119,
56,57,58,59,60,61,62,63,120,121,122,123,124,125,126,127,
192,193,194,195,196,197,198,199,128,129,130,131,132,133,134,135,
200,201,202,203,204,205,206,207,136,137,138,139,140,141,142,143,
208,209,210,211,212,213,214,215,144,145,146,147,148,149,150,151,
216,217,218,219,220,221,222,223,152,153,154,155,156,157,158,159,
224,225,226,227,228,229,230,231,160,161,162,163,164,165,166,167,
232,233,234,235,236,237,238,239,168,169,170,171,172,173,174,175,
240,241,242,243,244,245,246,247,176,177,178,179,180,181,182,183,
248,249,250,251,252,253,254,255,184,185,186,187,188,189,190,191} ; 
  
  for(uint16_t i=0; i<leds.numPixels(); i++) {
    leds.setPixelColor(maskArray[i], c);
    leds.show();
    delay(wait);
  }
}

