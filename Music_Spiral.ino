// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            22

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS    256

#define BRIGHTNESS 100

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);

int analogPin = A4;

int mapArray[16][16] = {
  {0,1,2,3,4,5,6,7,64,65,66,67,68,69,70,71},
  {8,9,10,11,12,13,14,15,72,73,74,75,76,77,78,79},
  {16,17,18,19,20,21,22,23,80,81,82,83,84,85,86,87},
  {24,25,26,27,28,29,30,31,88,89,90,91,92,93,94,95},
  {32,33,34,35,36,37,38,39,96,97,98,99,100,101,102,103},
  {40,41,42,43,44,45,46,47,104,105,106,107,108,109,110,111},
  {48,49,50,51,52,53,54,55,112,113,114,115,116,117,118,119},
  {56,57,58,59,60,61,62,63,120,121,122,123,124,125,126,127},
  {192,193,194,195,196,197,198,199,128,129,130,131,132,133,134,135},
  {200,201,202,203,204,205,206,207,136,137,138,139,140,141,142,143},
  {208,209,210,211,212,213,214,215,144,145,146,147,148,149,150,151},
  {216,217,218,219,220,221,222,223,152,153,154,155,156,157,158,159},
  {224,225,226,227,228,229,230,231,160,161,162,163,164,165,166,167},
  {232,233,234,235,236,237,238,239,168,169,170,171,172,173,174,175},
  {240,241,242,243,244,245,246,247,176,177,178,179,180,181,182,183},
  {248,249,250,251,252,253,254,255,184,185,186,187,188,189,190,191}, 
};


void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  leds.setBrightness(BRIGHTNESS);
  leds.begin();
  leds.show(); // Initialize all pixels to 'off'
  Serial.begin(9600); 
}

void loop() {
  spiral(16, rand() % 3);
}

void spiral(int sizy, int z){
    int x = 0; // current position; x
    int y = 0; // current position; y
    int d = 0; // current direction; 0=RIGHT, 1=DOWN, 2=LEFT, 3=UP
    int c = 0; // counter
    int s = 1; // chain size
    
    // starting point
    x = ((int)floor(sizy/2.0))-1;
    y = ((int)floor(sizy/2.0))-1;

    for (int k=1; k<=(sizy-1); k++)
    {
        for (int j=0; j<(k<(sizy-1)?2:3); j++)
        {
            for (int i=0; i<s; i++)
            {
                 setNew(x, y, z);
                 leds.show();
                 delay(25);
                c++;

                switch (d)
                {
                    case 0: y = y + 1; break;
                    case 1: x = x + 1; break;
                    case 2: y = y - 1; break;
                    case 3: x = x - 1; break;
                }
            }
            d = (d+1)%4;
        }
        s = s + 1;
    }
}

void setNew(int x, int y, int z){
  uint32_t c;
  
  if(z == 0){ 
    c = leds.Color(255, 0, 0);
  }

    if(z == 1){
     c = leds.Color(0, 255, 0);
  }

     if(z == 2){
     c = leds.Color(0, 0, 255);
  }
   
  
  leds.setPixelColor(mapArray[x][y], c);
  setIntensity();
}

#Intensity of the light depends on amplitude of the analog signal coming form the music
void setIntensity(){
  int val = analogRead(analogPin);
  if(val == 0){
    val = rand() % 100;
  }
  leds.setBrightness(val);
}


