/****************************************************************************
 * Author: Daniel Truong
 * Date: 4-12-18
 * Development environment specifics:
 * Using Arduino IDe 1.8.5
 * Adafruit NeoPixel 1.1.6
 * DistanceGP2Y0A21YK
 ******************************************************************************/
#include <Adafruit_NeoPixel.h>
#include <DistanceGP2Y0A21YK.h>

// initalize IRsensor object library
DistanceGP2Y0A21YK IRSensor;
DistanceGP2Y0A21YK IRSensor2;
//DistanceGP2Y0A21YK IRSensor3;
int distance = 0, distance2 = 0, distance3 = 0, distance4 = 0;
int brightness = 90;
bool patternFlag = true;

// Define hardware connections
#define IRS_PIN A9 // analog pin for IR sensor 1
#define IRS_PIN2 A10
//#define IRS_PIN3 A11
//#define IRS_PIN4 A8
#define LED1 14 // Digital pin for LED strip 1
#define LED2 15 // Digital pin for LED strip 2
#define STRIP_NUM 32 // # of pixels addressed to the strip
#define STRIP2_NUM 12
#define offBright 0
#define quarterBright 64
#define halfBright 128
#define fullBright 255

// declare LED-strip object;
// Adafruit_NeoPixel objname = Adafruit_NeoPixel(# of LEDS, Pin #, NEO_RGBW);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_NUM, LED1, NEO_RGBW);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(STRIP2_NUM, LED2, NEO_RGBW);

// Preset LED colors
//format: colorname = stripname.Color(green, red, blue);
uint32_t white = strip2.Color(255, 255, 255, brightness);
uint32_t indigo = strip2.Color(0, 75, 130);

void setup()
{
  // Initialize LEDs
  strip.begin();
  strip2.begin();

  // initalize IRsensor(s)
  IRSensor.begin(IRS_PIN);
  IRSensor2.begin(IRS_PIN2);
  //IRSensor3.begin(IRS_PIN3);
  //IRSensor4.begin(IRS_PIN4);
  
  // set LED brightness (0 (off) to 255 (max))
  strip.setBrightness(offBright); // off initially
  strip2.setBrightness(offBright);
  strip.show();
  strip2.show();
}

void loop()
{
  strip.setBrightness(halfBright);
  strip2.setBrightness(halfBright);
  strip.show();
  strip2.show();

  // query the distance (cm) from the sensor(s)
  distance = IRSensor.getDistanceCentimeter();
  delay(2);
  distance2 = IRSensor2.getDistanceCentimeter();
  delay(2);
  //distance3 = IRSensor3.getDistanceCentimeter();
  //delay(2);
  //distance4 = IRSensor4.getDistanceCentimeter();
  //delay(2);

  // default color
  stripFill(indigo);
  strip2Fill(indigo);

  //checkProximity(distance, 1);
  //checkProximity(distance2, 2);
  checkProximity(distance, distance2);
  
  // update the LED object, will begin to change colors afterwards
  strip.show();
  strip2.show();
  
  // pause for 250ms
  delay(250);
}

void stripFill(uint32_t color)
{
  for(int i = 0;i < strip.numPixels();i++)
  {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void strip2Fill(uint32_t color)
{
  for(int i = 0;i < strip2.numPixels();i++)
  {
    strip2.setPixelColor(i, color);
  }
  strip2.show();
}

// query the distance from the IR sensor, if triggered in the specified range
// trigger a specific LED pattern depending on which sensor was triggered
void checkProximity(int dist, int dist2)
{
  if((dist >= 5 && dist <= 29) && (dist2 >= 5 && dist2 <= 29))
  {
    stripFill(white);
    strip2Fill(white);
  }
  else if(dist >= 5 && dist <= 29)
  {
    stripFill(white);
  }
  else if(dist2 >= 5 && dist2 <= 29)
  {
    strip2Fill(white);
  }
  delay(1000);
}

