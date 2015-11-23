#include <FastLED.h>
#define NUM_LEDS 4
#define DATA_PIN 8
#include "SPI.h"

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

CRGB leds[NUM_LEDS];

void setup () {
  Serial.println("setup!");
  
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}
void loop () {
  Serial.println("running!");
  
  DateTime now = RTC.now(); 
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println(); 

  FastLED.clear();

  DateTime firstAdvent (2015, 11, 28, 0, 0, 0);
  handleCandle(now, firstAdvent, 0);
  
  DateTime secondAdvent (2015, 12, 5, 0, 0, 0);
  handleCandle(now, secondAdvent, 1);
  
  DateTime thirdAdvent (2015, 12, 12, 0, 0, 0);
  handleCandle(now, thirdAdvent, 2);
  
  DateTime fourthAdvent (2015, 12, 19, 0, 0, 0);
  handleCandle(now, fourthAdvent, 3);
  
  FastLED.show(); // display this frame
  delay(30);
}

void handleCandle(DateTime now, DateTime date, int candleIndex) {
  if (now.unixtime() > date.unixtime()) {
    float x = millis()/1000000.0 + random()/10000.0;
    //leds[candleIndex] = CRGB::Red;
    //float i = (millis()/random8()/10) * ((sin(millis()/1000) + 1) / 2);
    float i = ((sin(x + cos(x)) + 1)/2) * ((sin(x*10) + 1)/4 + 0.5);
    //int hue = ((sin(millis()/500.0 + random()/10000.0) + 1)/2 * 45);
    int intensity = ((sin(i) + 1)/2 * 150) + 55;
    int hue = ((sin(millis()) + 1)/2 * 10) + 40;
    leds[candleIndex].setHSV(hue, 255, intensity);
  } else {
    //leds[candleIndex] = CRGB::Black;
    int sat = ease8InOutApprox(millis()/10 % 255);
    //int hue = ((sin(millis()/800.0) + 1) * 128) - 1;
    int hue = ((sin(millis()/500.0) + 1)/2 * 40) + 160;
    int intensity = ((sin(millis()/500.0) + 1)/2 * 200) + 50;
    leds[candleIndex].setHSV(hue, 255, intensity);
  }
}


