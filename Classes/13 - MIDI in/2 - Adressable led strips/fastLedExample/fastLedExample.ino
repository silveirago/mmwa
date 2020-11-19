//////////////////////////////////////
// If using Fast Led
#include "FastLED.h"

FASTLED_USING_NAMESPACE

#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    4

CRGB leds[NUM_LEDS];
byte ledIndex[NUM_LEDS] = {0, 1, 2, 3};

#define BRIGHTNESS          10
#define FRAMES_PER_SECOND  120


void setup() {

  Serial.begin(115200);

  //FAST LED
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  for (int i = 0; i < NUM_LEDS; i++) {

    byte tempHue = 128; // 0-255

    leds[i].setHue(tempHue);
       
  }

  FastLED.show();

}

void loop() {

  for (int i = 0; i < NUM_LEDS; i++) {

    byte tempHue = random(0, 255);

    leds[i].setHue(tempHue);
    FastLED.show();
    //    // insert a delay to keep the framerate modest
    //    FastLED.delay(1000 / FRAMES_PER_SECOND);

    delay(400);
  }


// ONE HUE FOR ALL
//  for (int i = 0; i < NUM_LEDS; i++) {
//
//    byte tempHue = map(analogRead(A0), 0, 1023, 0, 255);
//
//    leds[i].setHue(tempHue);
//    
//    FastLED.show();
//    Serial.print("HUE = ");
//    Serial.println(tempHue);
//
//  }

}
