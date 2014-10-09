#include <Adafruit_NeoPixel.h>

// each RGB strip is on a diffrent pin
#define PRING 6 // ring pin
#define PSTRIP1 7 // first strip pin
#define PSTRIP2 8 // second strip pin
#define PSTRIP3 9 // third strip pin

#define STRIPPIXELCOUNT 39 // the number of pixels in the strips
#define RINGPIXELCOUNT 60 // the number of pixels in the ring

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(STRIPPIXELCOUNT, PSTRIP1, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(STRIPPIXELCOUNT, PSTRIP2, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(STRIPPIXELCOUNT, PSTRIP3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel currentStrip = Adafruit_NeoPixel(STRIPPIXELCOUNT, PSTRIP1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(RINGPIXELCOUNT, PRING, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// LED Brightness is cut to conserve power and prevent color browning
// when on battery power
int intBrightness = 127;

// a few colors
uint32_t colorWhite = currentStrip.Color(127, 127, 127); // white is cut in half to prevent discoloration
uint32_t colorBlack = currentStrip.Color(0, 0, 0);
uint32_t colorRed = currentStrip.Color(255, 0, 0);
uint32_t colorPink = currentStrip.Color(255, 105, 180);
uint32_t colorGold = currentStrip.Color(255, 215, 0);
uint32_t colorPurple = currentStrip.Color(128, 0, 128);

// set a few basic vars for controling the strips
int intStripStep = 0;
int intCurrentStripPin = 0;
int intRingStep = 0;

// a few vars to hold random strip values
int intRanStripActive = 0; // random number has been picked and is active
long lngRanStrip; // which strip gets the action
long lngRanStripAnimation = 0; // what animation will the strip do
long lngRanStripChaseLength = 4; // random chaser length (default to 4)
long lngRanStripColor1 = 0; // random color chooser
long lngRanStripColor2 = 0; // random color chooser

// a few vars to hold random ring values
int intRanRingActive = 0; // random number has been chose for ring and is active
long lngRanRingAnimation = 0; // what animation should we do for the ring?
long lngRanRingChaseLength = 4; // random chaser length (default to 4)
long lngRanRingColor1 = 0; // random color chooser
long lngRanRingColor2 = 0; // random color chooser

void setup(){
  // set up the debuging serial output
  Serial.begin(9600);
  // while(!Serial); // Needed for Leonardo only
  // found for simple debuging you just have to hold out for a few moments
  delay(200);

  // Initialize all pixels to 'off' and set the brightness
//  strip1.begin();
//  strip1.setBrightness(intBrightness);
//  strip2.begin();
//  strip2.setBrightness(intBrightness);
//  strip3.begin();
//  strip3.setBrightness(intBrightness);
  currentStrip.begin();
  currentStrip.setBrightness(intBrightness);
  currentStrip.show();
  ring.begin();
  ring.setBrightness(intBrightness);
  ring.show();
//  strip1.show();
//  strip2.show();
//  strip3.show();

}

void loop(){
  // check to see if we are already in the middle of an animation
  // if we are not (intRanStripActive == 0) then lets randomly set some values
  if(intRanStripActive == 0){
    // pick the strip we are going to animate
    lngRanStrip = random(1,4);
    // pick the animation
    lngRanStripAnimation = random(1,3);
    // pick the length of the chaser tail
    lngRanStripChaseLength = random(2,11);
    // pick the first chaser color
    lngRanStripColor1 = random(1,5);
    // pick the second chaser color
    lngRanStripColor2 = random(1,5);
    // set the flag indicating we are running an animation
    intRanStripActive = 1;
    // lets set the strip pin based on the random strip picked
    if(lngRanStrip == 1){
      intCurrentStripPin = PSTRIP1;
    }
    if(lngRanStrip == 2){
      intCurrentStripPin = PSTRIP2;
    }
    if(lngRanStrip == 3){
      intCurrentStripPin = PSTRIP3;
    }
    // set the current active strip based on the current active pin
    currentStrip.setPin(intCurrentStripPin);
    Serial.println("New Random STRIP Values");
    Serial.print("Animation: ");
    Serial.println(lngRanStripAnimation);
    Serial.print("Strip #: ");
    Serial.println(lngRanStrip);
    Serial.print("Chase Len: ");
    Serial.println(lngRanStripChaseLength);
    Serial.print("Color 1: ");
    Serial.println(lngRanStripColor1);
    Serial.print("Color 2: ");
    Serial.println(lngRanStripColor2);
    Serial.println("---------------------------");
  }



  // set the first color
  uint32_t intFirstStripColor;
  if(lngRanStripColor1 == 1){
    intFirstStripColor = colorBlack;
  }
  if(lngRanStripColor1 == 2){
    intFirstStripColor = colorWhite;
  }
  if(lngRanStripColor1 == 3){
    intFirstStripColor = colorGold;
  }
  if(lngRanStripColor1 == 4){
    intFirstStripColor = colorPurple;
  }

  // set the second color
  uint32_t intSecondStripColor;
  if(lngRanStripColor2 == 1){
    intSecondStripColor = colorBlack;
  }
  if(lngRanStripColor2 == 2){
    intSecondStripColor = colorWhite;
  }
  if(lngRanStripColor2 == 3){
    intSecondStripColor = colorGold;
  }
  if(lngRanStripColor2 == 4){
    intSecondStripColor = colorPurple;
  }
  
  // now we find out which animation we are running
  // simple chaser drop
  if(lngRanStripAnimation == 1){
    currentStrip.setPixelColor(intStripStep  , intFirstStripColor); // Draw the pixel
    currentStrip.setPixelColor(intStripStep - lngRanStripChaseLength, 0); // Erase pixel a few steps back
    currentStrip.show();
    // now lets incrment the step for the strips (which are all 39 pixels long)
    // yea... why I didn't cut them at an even 40 is beyond me!
    intStripStep += 1;
    if(intStripStep < 0){
      intStripStep = 1;
    }else if(intStripStep >= (39 + lngRanStripChaseLength)) {
      intStripStep = 0;
      // if we have reached the end of the strip, lets reset the random active flag
      // so we can pick another strip
      intRanStripActive = 0;
    }
  }
  // simple chaser drop in reverse
//  if(lngRanStripAnimation == 2){
//    currentStrip.setPixelColor(abs(intStripStep - STRIPPIXELCOUNT)  , intFirstStripColor); // Draw the pixel
//    currentStrip.setPixelColor(abs(intStripStep - STRIPPIXELCOUNT) + lngRanStripChaseLength, 0); // Erase pixel a few steps back
//    currentStrip.show();
//    // now lets incrment the step for the strips (which are all 39 pixels long)
//    // yea... why I didn't cut them at an even 40 is beyond me!
//    intStripStep += 1;
//    if(intStripStep < 0){
//      intStripStep = 1;
//    }else if(intStripStep >= abs(intStripStep - STRIPPIXELCOUNT)){
//      Serial.println(intStripStep);
//      intStripStep = 0;
//      // if we have reached the end of the strip, lets reset the random active flag
//      // so we can pick another strip
//      intRanStripActive = 0;
//    }
//  }
  // simple chaser drop with following second color
  if(lngRanStripAnimation == 2){
    if((intStripStep % 2) == 0){
      currentStrip.setPixelColor(intStripStep  , intFirstStripColor); // Draw the pixel
    }else{
      currentStrip.setPixelColor(intStripStep  , intSecondStripColor); // Draw the pixel
    }
    currentStrip.setPixelColor(intStripStep - lngRanStripChaseLength, 0); // Erase pixel a few steps back
    currentStrip.show();
    // now lets incrment the step for the strips (which are all 39 pixels long)
    // yea... why I didn't cut them at an even 40 is beyond me!
    intStripStep += 1;
    if(intStripStep < 0){
      intStripStep = 1;
    }else if(intStripStep >= (39 + lngRanStripChaseLength)) {
      intStripStep = 0;
      // if we have reached the end of the strip, lets reset the random active flag
      // so we can pick another strip
      intRanStripActive = 0;
    }
  }

  // now lets work with the ring
  if(intRanRingActive == 0){
    Serial.println("new random RING values");
    lngRanRingAnimation = random(1,8);
    lngRanRingChaseLength = random(2,60);
    lngRanRingColor1 = random(1,5);
    lngRanRingColor2 = random(1,5);
    intRanRingActive = 1;
    Serial.print("chase len: ");
    Serial.println(lngRanRingChaseLength);
    Serial.print("color: ");
    Serial.println(lngRanRingColor1);
    Serial.println("---------------------------");
  }

  uint32_t intCurrentRingColor1;
  if(lngRanRingColor1 == 1){
    intCurrentRingColor1 = colorBlack;
  }
  if(lngRanRingColor1 == 2){
    intCurrentRingColor1 = colorWhite;
  }
  if(lngRanRingColor1 == 3){
    intCurrentRingColor1 = colorGold;
  }
  if(lngRanRingColor1 == 4){
    intCurrentRingColor1 = colorPurple;
  }

  uint32_t intCurrentRingColor2;
  if(lngRanRingColor2 == 1){
    intCurrentRingColor2 = colorBlack;
  }
  if(lngRanRingColor2 == 2){
    intCurrentRingColor2 = colorWhite;
  }
  if(lngRanRingColor2 == 3){
    intCurrentRingColor2 = colorGold;
  }
  if(lngRanRingColor2 == 4){
    intCurrentRingColor2 = colorPurple;
  }

  // chaser around
  if(lngRanRingAnimation == 1){
    ring.setPixelColor(intRingStep  , intCurrentRingColor1); // Draw the pixel
    ring.setPixelColor(intRingStep - lngRanRingChaseLength, 0); // Erase pixel a few steps back
    ring.show();

    intRingStep += 1;
    if(intRingStep < 0){
      intRingStep = 1;
    }else if(intRingStep >= (60 + lngRanRingChaseLength)) {
      intRingStep = 0;
      intRanRingActive = 0;
    }
  }
  // build from the quarters
  if(lngRanRingAnimation == 2){
    ring.setPixelColor(intRingStep, intCurrentRingColor1);
//    ring.setPixelColor(intRingStep - 2, 0); // Erase pixel a few steps back
    ring.setPixelColor(intRingStep + 14, intCurrentRingColor1);
//    ring.setPixelColor((intRingStep + 14) - 2, 0); // Erase pixel a few steps back
    ring.setPixelColor(intRingStep + 29, intCurrentRingColor1);
//    ring.setPixelColor((intRingStep + 29) - 2, 0); // Erase pixel a few steps back
    ring.setPixelColor(intRingStep + 44, intCurrentRingColor1);
//    ring.setPixelColor((intRingStep + 44) - 2, 0); // Erase pixel a few steps back
    ring.show();

    intRingStep += 1;
    if(intRingStep < 0){
      intRingStep = 1;
    }else if(intRingStep >= 14) {
      intRingStep = 0;
      intRanRingActive = 0;
    }
  }

  // build from the quarters
  if(lngRanRingAnimation == 3){
    ring.setPixelColor(intRingStep, intCurrentRingColor1);
    ring.setPixelColor(intRingStep - 2, 0); // Erase pixel a few steps back
    ring.setPixelColor(intRingStep + 14, intCurrentRingColor1);
    ring.setPixelColor((intRingStep + 14) - 1, 0); // Erase pixel a few steps back
    ring.setPixelColor(intRingStep + 29, intCurrentRingColor1);
    ring.setPixelColor((intRingStep + 29) - 1, 0); // Erase pixel a few steps back
    ring.setPixelColor(intRingStep + 44, intCurrentRingColor1);
    ring.setPixelColor((intRingStep + 44) - 1, 0); // Erase pixel a few steps back
    ring.show();

    intRingStep += 1;
    if(intRingStep < 0){
      intRingStep = 1;
    }else if(intRingStep >= 14) {
      intRingStep = 0;
      intRanRingActive = 0;
    }
  }

  // build from the quarters
  if(lngRanRingAnimation == 4){
    ring.setPixelColor(intRingStep, intCurrentRingColor1);
//    ring.setPixelColor(intRingStep - 2, 0); // Erase pixel a few steps back
    ring.setPixelColor(intRingStep + 29, intCurrentRingColor1);
//    ring.setPixelColor((intRingStep + 29) - 2, 0); // Erase pixel a few steps back
    ring.show();

    intRingStep += 1;
    if(intRingStep < 0){
      intRingStep = 1;
    }else if(intRingStep >= 29) {
      intRingStep = 0;
      intRanRingActive = 0;
    }
  }

  // build from the quarters
  if(lngRanRingAnimation == 5){
    ring.setPixelColor(intRingStep, intCurrentRingColor1);
    ring.setPixelColor(intRingStep - 2, intCurrentRingColor2); // Erase pixel a few steps back
    ring.setPixelColor(intRingStep + 29, intCurrentRingColor1);
    ring.setPixelColor((intRingStep + 29) - 2, intCurrentRingColor2); // Erase pixel a few steps back
    ring.show();

    intRingStep += 1;
    if(intRingStep < 0){
      intRingStep = 1;
    }else if(intRingStep >= 29) {
      intRingStep = 0;
      intRanRingActive = 0;
    }
  }

  // build from the quarters
  if(lngRanRingAnimation == 6){
    ring.setPixelColor(abs(intRingStep - 28), intCurrentRingColor1);
//    ring.setPixelColor(intRingStep - 2, 0); // Erase pixel a few steps back
    ring.setPixelColor(intRingStep + 29, intCurrentRingColor1);
//    ring.setPixelColor((intRingStep + 29) - 2, 0); // Erase pixel a few steps back
    ring.show();

    intRingStep += 1;
    if(intRingStep < 0){
      intRingStep = 1;
    }else if(intRingStep >= 29) {
      intRingStep = 0;
      intRanRingActive = 0;
    }
  }

  if(lngRanRingAnimation == 7){
    ring.setPixelColor(abs(intRingStep - 60)  , intCurrentRingColor1); // Draw the pixel
    ring.setPixelColor(abs(intRingStep -60) - lngRanRingChaseLength, 0); // Erase pixel a few steps back
    ring.show();

    intRingStep += 1;
    if(intRingStep < 0){
      intRingStep = 1;
    }else if(intRingStep >= (60 + lngRanRingChaseLength)) {
      intRingStep = 0;
      intRanRingActive = 0;
    }
  }
  delay(15);
}

//void fadeOut(int time){
//  for (int i = intBrightness; i > 0; --i){
//    grid.setBrightness(i);
//    grid.show();
//    delay(time);
//  }
//}

//void fadeIn(int time){
//  for(int i = 1; i < intBrightness; ++i){
//    grid.setBrightness(i);
//    grid.show();
//    delay(time);  
//  }
//}
