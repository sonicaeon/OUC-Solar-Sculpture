/****************************************************************************
 * Author: Daniel Truong
 * Date: 4-12-18
 * Development environment specifics:
 * Using Arduino IDe 1.8.5
 * Adafruit NeoPixel 1.1.6
 * DistanceGP2Y0A21YK
 ******************************************************************************/
#include <Adafruit_NeoPixel.h>

int brightness = 90;

// Define hardware connections
#define LED1 14 // Digital pin for LED strip 1
#define LED2 15 // Digital pin for LED strip 2
#define STRIP_NUM 93 // # of pixels addressed to the strip (3 risers (~30 pixels ea), 1 pixel for a spotlight (1 per riser))
#define STRIP2_NUM 60 // 62 pixels per circular ball half dome (2 pixels per side, 31 sides)
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
uint32_t white = strip2.Color(255, 255, 255, 255);
uint32_t orange = strip2.Color(83, 255, 0);
uint32_t firstOrange = strip2.Color(43, 255, 0);
uint32_t secondOrange = strip2.Color(83, 229, 0);
uint32_t fourthOrange = strip2.Color(105, 255, 0);
uint32_t fifthOrange = strip2.Color(159, 255, 0);
uint32_t off = strip2.Color(0, 0, 0);

void setup()
{
  // Initialize LEDs
  strip.begin();
  strip2.begin();
  
  // set LED brightness (0 (off) to 255 (max))
  strip.setBrightness(offBright); // off initially
  strip2.setBrightness(offBright);
  strip.show();
  strip2.show();
}

void loop()
{
  strip.setBrightness(fullBright);
  strip2.setBrightness(fullBright);
  strip.show();
  strip2.show();

  // orangeChase down the 3 raizers
  riserChase(firstOrange, secondOrange, orange, fourthOrange, fifthOrange, off, white, 50);

  // after riserChase ends flow into the two domes and execute orangeChase
  orangeChase(firstOrange, secondOrange, orange, fourthOrange, fifthOrange, off, 50);
  //strip2Fill(orange);
  
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

void riserChase(uint32_t firstOrange, uint32_t secondOrange, uint32_t Orange, uint32_t fourthOrange, uint32_t fifthOrange, uint32_t off, uint32_t white, uint8_t wait)
{
  int riser1 = 30, riser2 = 61, riser3 = 92;
  int spotlight1 = 0, spotlight2 = 31, spotlight3 = 62;
  int x = 30, y = 61, z = 92; // counter positions for each riser start
  strip.setBrightness(fullBright);

  // turn on all 3 spotlights
  strip.setPixelColor(spotlight1, white);
  strip.setPixelColor(spotlight2, white);
  strip.setPixelColor(spotlight3, white);
  strip.show();

  // all 3 risers will do an orange chase down at the same time
  for(int i = 0;i < 36;i++)
  {
    // 1st riser
    if(x <= 30 && x > 0)
    {
      strip.setPixelColor(x, firstOrange);
    }
    else
    {
      strip.setPixelColor(x, off);
    }
    if((x+1) <= 30 && (x+1) > 0)
    {
      strip.setPixelColor(x+1, secondOrange);
    }
    else
    {
      strip.setPixelColor(x+1, off);
    }
    if((x+2) <= 30 && (x+2) > 0)
    {
      strip.setPixelColor(x+2, Orange);
    }
    else
    {
      strip.setPixelColor(x+2, off);
    }
    if((x+3) <= 30 && (x+3) > 0)
    {
      strip.setPixelColor(x+3, fourthOrange);
    }
    else
    {
      strip.setPixelColor(x+3, off);
    }
    if((x+4) <= 30 && (x+4) > 0)
    {
      strip.setPixelColor(x+4, fifthOrange);
    }
    else
    {
      strip.setPixelColor(x+4, off);
    }
    if((x+5) <= 30)
    {
      strip.setPixelColor(x+5, off);
    }
    x--;

    // 2nd riser
    if(y <= 61 && y > 31)
    {
      strip.setPixelColor(y, firstOrange);
    }
    else
    {
      strip.setPixelColor(y, off);
    }
    if((y+1) <= 61 && (y+1) > 31)
    {
      strip.setPixelColor(y+1, secondOrange);
    }
    else
    {
      strip.setPixelColor(y+1, off);
    }
    if((y+2) <= 61 && (y+2) > 31)
    {
      strip.setPixelColor(y+2, Orange);
    }
    else
    {
      strip.setPixelColor(y+2, off);
    }
    if((y+3) <= 61 && (y+3) > 31)
    {
      strip.setPixelColor(y+3, fourthOrange);
    }
    else
    {
      strip.setPixelColor(y+3, off);
    }
    if((y+4) <= 61 && (y+4) > 31)
    {
      strip.setPixelColor(y+4, fifthOrange);
    }
    else
    {
      strip.setPixelColor(y+4, off);
    }
    if(y+5 <= 61)
    {
      strip.setPixelColor(y+5, off);
    }
    y--;

    // 3rd riser
    if(z <= 92 && z > 62)
    {
      strip.setPixelColor(z, firstOrange);
    }
    else
    {
      strip.setPixelColor(z, off);
    }
    if((z+1) <= 92 && (z+1) > 62)
    {
      strip.setPixelColor(z+1, secondOrange);
    }
    else
    {
      strip.setPixelColor(z+1, off);
    }
    if((z+2) <= 92 && (z+2) > 62)
    {
      strip.setPixelColor(z+2, Orange);
    }
    else
    {
      strip.setPixelColor(z+2, off);
    }
    if((z+3) <= 92 && (z+3) > 62)
    {
      strip.setPixelColor(z+3, fourthOrange);
    }
    else
    {
      strip.setPixelColor(z+3, off);
    }
    if((z+4) <= 92 && (z+4) > 62)
    {
      strip.setPixelColor(z+4, fifthOrange);
    }
    else
    {
      strip.setPixelColor(z+4, off);
    }
    if((z+5) <= 92)
    {
      strip.setPixelColor(z+5, off);
    }
    z--;
        
    // turn on all 3 spotlights
    strip.setPixelColor(spotlight1, white);
    strip.setPixelColor(spotlight2, white);
    strip.setPixelColor(spotlight3, white);

    // update chase LEDs
    strip.show();
    delay(wait);
  }
}

void orangeChase(uint32_t firstOrange, uint32_t secondOrange, uint32_t Orange, uint32_t fourthOrange, uint32_t fifthOrange, uint32_t off, uint8_t wait)
{
  int ballStart = 0;
  int ballEnd = 14;
  int offset1 = 15;
  int offset2 = 30;
  int offset3 = 45;
  strip2.setBrightness(fullBright);

  // dome 1 & 2
  for(int i = ballStart;i < ballEnd + 6;i++)
  {
    // strip 1 in dome 1
    if(i <= 14 && i >= 0)
    {
      strip2.setPixelColor(i, firstOrange);
    }
    else
    {
      strip2.setPixelColor(i, off);
    }
    if((i-1) <= 14 && (i-1) >= 0)
    {
      strip2.setPixelColor(i-1, secondOrange);
    }
    else
    {
      strip2.setPixelColor(i-1, off);
    }
    if((i-2) <= 14 && (i-2) >= 0)
    {
      strip2.setPixelColor(i-2, Orange);
    }
    else
    {
      strip2.setPixelColor(i-2, off);
    }
    if((i-3) <= 14 && (i-3) >= 0)
    {
      strip2.setPixelColor(i-3, fourthOrange);
    }
    else
    {
      strip2.setPixelColor(i-3, off);
    }
    if((i-4) <= 14 && (i-4) >= 0)
    {
      strip2.setPixelColor(i-4, fifthOrange);
    }
    else
    {
      strip2.setPixelColor(i-4, off);
    }
    if((i-5) <= 14 && (i-5) >= 0)
    {
      strip2.setPixelColor(i-5, off);
    }
    
    // strip 2 in dome 1
    if(i + offset1 <= 29 && i + offset1 >= 15)
    {
      strip2.setPixelColor(i + offset1, firstOrange);
    }
    else
    {
      strip2.setPixelColor(i + offset1, off);
    }
    if((i-1 + offset1) <= 29 && (i-1 + offset1) >= 15)
    {
      strip2.setPixelColor(i-1 + offset1, secondOrange);
    }
    else
    {
      strip2.setPixelColor(i-1 + offset1, off);
    }
    if((i-2 + offset1) <= 29 && (i-2 + offset1) >= 15)
    {
      strip2.setPixelColor(i-2 + offset1, Orange);
    }
    else
    {
      strip2.setPixelColor(i-2 + offset1, off);
    }
    if((i-3 + offset1) <= 29 && (i-3 + offset1) >= 15)
    {
      strip2.setPixelColor(i-3 + offset1, fourthOrange);
    }
    else
    {
      strip2.setPixelColor(i-3 + offset1, off);
    }
    if((i-4 + offset1) <= 29 && (i-4 + offset1) >= 15)
    {
      strip2.setPixelColor(i-4 + offset1, fifthOrange);
    }
    else
    {
      strip2.setPixelColor(i-4 + offset1, off);
    }
    if((i-5 + offset1) <= 29 && (i-5 + offset1) >= 15)
    {
      strip2.setPixelColor(i-5 + offset1, off);
    }
    
    // strip 1 in dome 2
    if(i + offset2 <= 44 && i + offset2 >= 30)
    {
      strip2.setPixelColor(i + offset2, firstOrange);
    }
    else
    {
      strip2.setPixelColor(i + offset2, off);
    }
    if((i-1) + offset2 <= 44 && (i-1) + offset2 >= 30)
    {
      strip2.setPixelColor(i-1 + offset2, secondOrange);
    }
    else
    {
      strip2.setPixelColor(i-1 + offset2, off);
    }
    if((i-2) + offset2 <= 44 && (i-2) + offset2 >= 30)
    {
      strip2.setPixelColor(i-2 + offset2, Orange);
    }
    else
    {
      strip2.setPixelColor(i-2 + offset2, off);
    }
    if((i-3) + offset2 <= 44 && (i-3) + offset2 >= 30)
    {
      strip2.setPixelColor(i-3 + offset2, fourthOrange);
    }
    else
    {
      strip2.setPixelColor(i-3 + offset2, off);
    }
    if((i-4) + offset2 <= 44 && (i-4) + offset2 >= 30)
    {
      strip2.setPixelColor(i-4 + offset2, fifthOrange);
    }
    else
    {
      strip2.setPixelColor(i-4 + offset2, off);
    }
    if((i-5) + offset2 <= 44 && (i-5) + offset2 >= 30)
    {
      strip2.setPixelColor(i-5 + offset2, off);
    }
    
    // strip 2 in dome 2
    if(i + offset3 <= 59 && i + offset3 >= 45)
    {
      strip2.setPixelColor(i + offset3, firstOrange);
    }
    else
    {
      strip2.setPixelColor(i + offset3, off);
    }
    if((i-1) + offset3 <= 59 && (i-1) + offset3 >= 45)
    {
      strip2.setPixelColor(i-1 + offset3, secondOrange);
    }
    else
    {
      strip2.setPixelColor(i-1 + offset3, off);
    }
    if((i-2) + offset3 <= 59 && (i-2) + offset3 >= 45)
    {
      strip2.setPixelColor(i-2 + offset3, Orange);
    }
    else
    {
      strip2.setPixelColor(i-2 + offset3, off);
    }
    if((i-3) + offset3 <= 59 && (i-3) + offset3 >= 45)
    {
      strip2.setPixelColor(i-3 + offset3, fourthOrange);
    }
    else
    {
      strip2.setPixelColor(i-3 + offset3, off);
    }
    if((i-4) + offset3 <= 59 && (i-4) + offset3 >= 45)
    {
      strip2.setPixelColor(i-4 + offset3, fifthOrange);
    }
    else
    {
      strip2.setPixelColor(i-4 + offset3, off);
    }
    if((i-5) + offset3 <= 59 && (i-5) + offset3 >= 45)
    {
      strip2.setPixelColor(i-5 + offset3, off);
    }

    // update chase movement
    strip2.show();
    delay(wait);
  }
}

/*// orangeChase pattern inside both half domes, pattern is hardcoded due to hardware layout installation
void orangeChase(uint32_t firstOrange, uint32_t secondOrange, uint32_t Orange, uint32_t fourthOrange, uint32_t fifthOrange, uint32_t off, uint8_t wait)
{
  int i = 0;
  int rightNode = 1; // side # starting point; where Pixel start # = (current side #) + (prev side #) - 1
  int middleNode = 13;
  int leftNode = 14;
  int offset = 62; // offset for starting position of 2nd dome
  strip2.setBrightness(fullBright);

  // side 1, 13, 14
  strip2.setPixelColor(0, firstOrange);
  strip2.setPixelColor(25, firstOrange);
  strip2.setPixelColor(26, firstOrange);
  // dome2
  strip2.setPixelColor(0 + offset, firstOrange);
  strip2.setPixelColor(25 + offset, firstOrange);
  strip2.setPixelColor(26 + offset, firstOrange);
  strip2.show();
  delay(wait);
  strip2.setPixelColor(1, firstOrange); // side 1
  strip2.setPixelColor(0, secondOrange);
  strip2.setPixelColor(24, firstOrange); // side 13
  strip2.setPixelColor(25, secondOrange);
  strip2.setPixelColor(27, firstOrange); // side 14
  strip2.setPixelColor(26, secondOrange);
  // dome2
  strip2.setPixelColor(1 + offset, firstOrange); // side 1
  strip2.setPixelColor(0 + offset, secondOrange);
  strip2.setPixelColor(24 + offset, firstOrange); // side 13
  strip2.setPixelColor(25 + offset, secondOrange);
  strip2.setPixelColor(27 + offset, firstOrange); // side 14
  strip2.setPixelColor(26 + offset, secondOrange);
  strip2.show();
  delay(wait);
  // side 1, 2, 10, 12, 13, 25, 14, 15, 23
  strip2.setPixelColor(19, firstOrange);
  strip2.setPixelColor(2, firstOrange);
  strip2.setPixelColor(1, secondOrange); // side 1
  strip2.setPixelColor(0, Orange);
  strip2.setPixelColor(49, firstOrange); // 25
  strip2.setPixelColor(23, firstOrange); // 12
  strip2.setPixelColor(24, secondOrange); // side 13
  strip2.setPixelColor(25, Orange);
  strip2.setPixelColor(45, firstOrange); // 23
  strip2.setPixelColor(28, firstOrange); // 15
  strip2.setPixelColor(27, secondOrange); // side 14
  strip2.setPixelColor(26, Orange);
  // dome2
  strip2.setPixelColor(19 + offset, firstOrange);
  strip2.setPixelColor(2 + offset, firstOrange);
  strip2.setPixelColor(1 + offset, secondOrange); // side 1
  strip2.setPixelColor(0 + offset, Orange);
  strip2.setPixelColor(49 + offset, firstOrange); // 25
  strip2.setPixelColor(23 + offset, firstOrange); // 12
  strip2.setPixelColor(24 + offset, secondOrange); // side 13
  strip2.setPixelColor(25 + offset, Orange);
  strip2.setPixelColor(45 + offset, firstOrange); // 23
  strip2.setPixelColor(28 + offset, firstOrange); // 15
  strip2.setPixelColor(27 + offset, secondOrange); // side 14
  strip2.setPixelColor(26 + offset, Orange);
  strip2.show();
  delay(wait);
  // side 1, 2, 10, 12, 13, 25, 14, 15, 23
  strip2.setPixelColor(18, firstOrange); // side 10
  strip2.setPixelColor(19, secondOrange);
  strip2.setPixelColor(3, firstOrange); // side 2
  strip2.setPixelColor(2, secondOrange);
  strip2.setPixelColor(1, Orange); // side 1
  strip2.setPixelColor(0, fourthOrange);
  strip2.setPixelColor(48, firstOrange); // side 25
  strip2.setPixelColor(49, secondOrange);
  strip2.setPixelColor(22, firstOrange); // side 12
  strip2.setPixelColor(23, secondOrange);
  strip2.setPixelColor(24, Orange); // side 13
  strip2.setPixelColor(25, fourthOrange);
  strip2.setPixelColor(44, firstOrange); // side 23
  strip2.setPixelColor(45, secondOrange);
  strip2.setPixelColor(29, firstOrange); // side 15
  strip2.setPixelColor(28, secondOrange);
  strip2.setPixelColor(27, fourthOrange); // side 14
  strip2.setPixelColor(26, off);
  // dome2
  strip2.setPixelColor(18 + offset, firstOrange); // side 10
  strip2.setPixelColor(19 + offset, secondOrange);
  strip2.setPixelColor(3 + offset, firstOrange); // side 2
  strip2.setPixelColor(2 + offset, secondOrange);
  strip2.setPixelColor(1 + offset, Orange); // side 1
  strip2.setPixelColor(0 + offset, fourthOrange);
  strip2.setPixelColor(48 + offset, firstOrange); // side 25
  strip2.setPixelColor(49 + offset, secondOrange);
  strip2.setPixelColor(22 + offset, firstOrange); // side 12
  strip2.setPixelColor(23 + offset, secondOrange);
  strip2.setPixelColor(24 + offset, Orange); // side 13
  strip2.setPixelColor(25 + offset, fourthOrange);
  strip2.setPixelColor(44 + offset, firstOrange); // side 23
  strip2.setPixelColor(45 + offset, secondOrange);
  strip2.setPixelColor(29 + offset, firstOrange); // side 15
  strip2.setPixelColor(28 + offset, secondOrange);
  strip2.setPixelColor(27 + offset, fourthOrange); // side 14
  strip2.setPixelColor(26 + offset, off);
  strip2.show();
  delay(wait);
  
  // side 1, 2, 9, 10, 11, 12, 13, 25, 31, 14 <end>, 15, 22, 23, 24
  strip2.setPixelColor(20, firstOrange);
  strip2.setPixelColor(17, firstOrange);
  strip2.setPixelColor(18, secondOrange); // side 10
  strip2.setPixelColor(19, Orange);
  strip2.setPixelColor(3, secondOrange); // side 2
  strip2.setPixelColor(2, Orange);
  strip2.setPixelColor(1, fourthOrange); // side 1
  strip2.setPixelColor(0, off);
  strip2.setPixelColor(61, firstOrange); // 31
  strip2.setPixelColor(48, secondOrange); // side 25
  strip2.setPixelColor(49, Orange);
  strip2.setPixelColor(22, secondOrange); // side 12
  strip2.setPixelColor(23, Orange);
  strip2.setPixelColor(24, fourthOrange); // side 13
  strip2.setPixelColor(25, off);
  strip2.setPixelColor(43, firstOrange); // 22
  strip2.setPixelColor(46, firstOrange); // 24
  strip2.setPixelColor(44, secondOrange); // side 23
  strip2.setPixelColor(45, Orange);
  strip2.setPixelColor(29, secondOrange); // side 15
  strip2.setPixelColor(28, Orange);
  strip2.setPixelColor(27, off); // end of side 14
  // dome2
  strip2.setPixelColor(20 + offset, firstOrange);
  strip2.setPixelColor(17 + offset, firstOrange);
  strip2.setPixelColor(18 + offset, secondOrange); // side 10
  strip2.setPixelColor(19 + offset, Orange);
  strip2.setPixelColor(3 + offset, secondOrange); // side 2
  strip2.setPixelColor(2 + offset, Orange);
  strip2.setPixelColor(1 + offset, fourthOrange); // side 1
  strip2.setPixelColor(0 + offset, off);
  strip2.setPixelColor(61 + offset, firstOrange); // 31
  strip2.setPixelColor(48 + offset, secondOrange); // side 25
  strip2.setPixelColor(49 + offset, Orange);
  strip2.setPixelColor(22 + offset, secondOrange); // side 12
  strip2.setPixelColor(23 + offset, Orange);
  strip2.setPixelColor(24 + offset, fourthOrange); // side 13
  strip2.setPixelColor(25 + offset, off);
  strip2.setPixelColor(43 + offset, firstOrange); // 22
  strip2.setPixelColor(46 + offset, firstOrange); // 24
  strip2.setPixelColor(44 + offset, secondOrange); // side 23
  strip2.setPixelColor(45 + offset, Orange);
  strip2.setPixelColor(29 + offset, secondOrange); // side 15
  strip2.setPixelColor(28 + offset, Orange);
  strip2.setPixelColor(27 + offset, off); // end of side 14
  strip2.show();
  delay(wait);
  // side 1 <end>, 2, 9, 10, 11, 12, 13 <end>, 25, 31, 22, 24, 23, 15
  strip2.setPixelColor(21, firstOrange); // side 11
  strip2.setPixelColor(20, secondOrange);
  strip2.setPixelColor(16, firstOrange); // side 9
  strip2.setPixelColor(17, secondOrange);
  strip2.setPixelColor(19, Orange); // side 10
  strip2.setPixelColor(18, fourthOrange);
  strip2.setPixelColor(3, Orange); // side 2
  strip2.setPixelColor(2, fourthOrange);
  strip2.setPixelColor(1, off); // end of side 1
  strip2.setPixelColor(60, firstOrange); // side 31
  strip2.setPixelColor(61, secondOrange);
  strip2.setPixelColor(48, Orange); // side 25
  strip2.setPixelColor(49, fourthOrange);
  strip2.setPixelColor(22, Orange); // side 12
  strip2.setPixelColor(23, fourthOrange);
  strip2.setPixelColor(24, off); // end of side 13
  strip2.setPixelColor(42, firstOrange); // side 22
  strip2.setPixelColor(43, secondOrange);
  strip2.setPixelColor(47, firstOrange); // side 24
  strip2.setPixelColor(46, secondOrange);
  strip2.setPixelColor(44, Orange); // side 23
  strip2.setPixelColor(45, fourthOrange);
  strip2.setPixelColor(29, Orange); // side 15
  strip2.setPixelColor(28, fourthOrange);
  // dome2
  strip2.setPixelColor(21 + offset, firstOrange); // side 11
  strip2.setPixelColor(20 + offset, secondOrange);
  strip2.setPixelColor(16 + offset, firstOrange); // side 9
  strip2.setPixelColor(17 + offset, secondOrange);
  strip2.setPixelColor(19 + offset, Orange); // side 10
  strip2.setPixelColor(18 + offset, fourthOrange);
  strip2.setPixelColor(3 + offset, Orange); // side 2
  strip2.setPixelColor(2 + offset, fourthOrange);
  strip2.setPixelColor(1 + offset, off); // end of side 1
  strip2.setPixelColor(60 + offset, firstOrange); // side 31
  strip2.setPixelColor(61 + offset, secondOrange);
  strip2.setPixelColor(48 + offset, Orange); // side 25
  strip2.setPixelColor(49 + offset, fourthOrange);
  strip2.setPixelColor(22 + offset, Orange); // side 12
  strip2.setPixelColor(23 + offset, fourthOrange);
  strip2.setPixelColor(24 + offset, off); // end of side 13
  strip2.setPixelColor(42 + offset, firstOrange); // side 22
  strip2.setPixelColor(43 + offset, secondOrange);
  strip2.setPixelColor(47 + offset, firstOrange); // side 24
  strip2.setPixelColor(46 + offset, secondOrange);
  strip2.setPixelColor(44 + offset, Orange); // side 23
  strip2.setPixelColor(45 + offset, fourthOrange);
  strip2.setPixelColor(29 + offset, Orange); // side 15
  strip2.setPixelColor(28 + offset, fourthOrange);
  strip2.show();
  delay(wait);

  // side 2, 3, 4, 9, 10, 11, 26, 12, 25, 29, 30, 31, 15, 23, 24, 22, 16, 17
  strip2.setPixelColor(4, firstOrange);
  strip2.setPixelColor(6, firstOrange);
  strip2.setPixelColor(50, firstOrange);
  strip2.setPixelColor(21, secondOrange); // side 11
  strip2.setPixelColor(20, Orange);
  strip2.setPixelColor(16, secondOrange); // side 9
  strip2.setPixelColor(17, Orange);
  strip2.setPixelColor(19, fourthOrange); // side 10
  strip2.setPixelColor(18, off);
  strip2.setPixelColor(3, fourthOrange); // side 2
  strip2.setPixelColor(2, off);
  strip2.setPixelColor(57, firstOrange); // 29
  strip2.setPixelColor(58, firstOrange); // 30
  strip2.setPixelColor(60, secondOrange); // side 31
  strip2.setPixelColor(61, Orange);
  strip2.setPixelColor(48, fourthOrange); // side 25
  strip2.setPixelColor(49, off);
  strip2.setPixelColor(22, fourthOrange); // side 12
  strip2.setPixelColor(23, off);
  strip2.setPixelColor(32, firstOrange); // 17
  strip2.setPixelColor(31, firstOrange); // 16
  strip2.setPixelColor(42, secondOrange); // side 22
  strip2.setPixelColor(43, Orange);
  strip2.setPixelColor(47, secondOrange); // side 24
  strip2.setPixelColor(46, Orange);
  strip2.setPixelColor(44, fourthOrange); // side 23
  strip2.setPixelColor(45, off);
  strip2.setPixelColor(29, fourthOrange); // side 15
  strip2.setPixelColor(28, off);
  // dome 2
  strip2.setPixelColor(4 + offset, firstOrange);
  strip2.setPixelColor(6 + offset, firstOrange);
  strip2.setPixelColor(50 + offset, firstOrange);
  strip2.setPixelColor(21 + offset, secondOrange); // side 11
  strip2.setPixelColor(20 + offset, Orange);
  strip2.setPixelColor(16 + offset, secondOrange); // side 9
  strip2.setPixelColor(17 + offset, Orange);
  strip2.setPixelColor(19 + offset, fourthOrange); // side 10
  strip2.setPixelColor(18 + offset, off);
  strip2.setPixelColor(3 + offset, fourthOrange); // side 2
  strip2.setPixelColor(2 + offset, off);
  strip2.setPixelColor(57 + offset, firstOrange); // 29
  strip2.setPixelColor(58 + offset, firstOrange); // 30
  strip2.setPixelColor(60 + offset, secondOrange); // side 31
  strip2.setPixelColor(61 + offset, Orange);
  strip2.setPixelColor(48 + offset, fourthOrange); // side 25
  strip2.setPixelColor(49 + offset, off);
  strip2.setPixelColor(22 + offset, fourthOrange); // side 12
  strip2.setPixelColor(23 + offset, off);
  strip2.setPixelColor(32 + offset, firstOrange); // 17
  strip2.setPixelColor(31 + offset, firstOrange); // 16
  strip2.setPixelColor(42 + offset, secondOrange); // side 22
  strip2.setPixelColor(43 + offset, Orange);
  strip2.setPixelColor(47 + offset, secondOrange); // side 24
  strip2.setPixelColor(46 + offset, Orange);
  strip2.setPixelColor(44 + offset, fourthOrange); // side 23
  strip2.setPixelColor(45 + offset, off);
  strip2.setPixelColor(29 + offset, fourthOrange); // side 15
  strip2.setPixelColor(28 + offset, off);
  strip2.show();
  delay(wait);
  // side 2 <end>, 3, 4, 9, 10 <end>, 11, 26, 12 <end>, 25 <end>, 29, 30, 31, 15 <end>, 23 <end>, 24, 22, 16, 17
  strip2.setPixelColor(5, firstOrange); // side 3
  strip2.setPixelColor(4, secondOrange);
  strip2.setPixelColor(7, firstOrange); // side 4
  strip2.setPixelColor(6, secondOrange);
  strip2.setPixelColor(51, firstOrange); // side 26
  strip2.setPixelColor(50, secondOrange);
  strip2.setPixelColor(21, Orange); // side 11
  strip2.setPixelColor(20, fourthOrange);
  strip2.setPixelColor(16, Orange); // side 9
  strip2.setPixelColor(17, fourthOrange);
  strip2.setPixelColor(19, off); // end of side 10
  strip2.setPixelColor(3, off); // end of side 2
  strip2.setPixelColor(56, firstOrange); // side 29
  strip2.setPixelColor(57, secondOrange);
  strip2.setPixelColor(59, firstOrange); // side 30
  strip2.setPixelColor(58, secondOrange);
  strip2.setPixelColor(60, Orange); // side 31
  strip2.setPixelColor(61, fourthOrange);
  strip2.setPixelColor(48, off); // end of side 25
  strip2.setPixelColor(22, off); // end of side 12
  strip2.setPixelColor(33, firstOrange); // side 17
  strip2.setPixelColor(32, secondOrange);
  strip2.setPixelColor(30, firstOrange); // side 16
  strip2.setPixelColor(31, secondOrange);
  strip2.setPixelColor(42, Orange); // side 22
  strip2.setPixelColor(43, fourthOrange);
  strip2.setPixelColor(47, Orange); // side 24
  strip2.setPixelColor(46, fourthOrange);
  strip2.setPixelColor(44, off); // end of side 23
  strip2.setPixelColor(29, off); // end of side 15
  // dome 2
  strip2.setPixelColor(5 + offset, firstOrange); // side 3
  strip2.setPixelColor(4 + offset, secondOrange);
  strip2.setPixelColor(7 + offset, firstOrange); // side 4
  strip2.setPixelColor(6 + offset, secondOrange);
  strip2.setPixelColor(51 + offset, firstOrange); // side 26
  strip2.setPixelColor(50 + offset, secondOrange);
  strip2.setPixelColor(21 + offset, Orange); // side 11
  strip2.setPixelColor(20 + offset, fourthOrange);
  strip2.setPixelColor(16 + offset, Orange); // side 9
  strip2.setPixelColor(17 + offset, fourthOrange);
  strip2.setPixelColor(19 + offset, off); // end of side 10
  strip2.setPixelColor(3 + offset, off); // end of side 2
  strip2.setPixelColor(56 + offset, firstOrange); // side 29
  strip2.setPixelColor(57 + offset, secondOrange);
  strip2.setPixelColor(59 + offset, firstOrange); // side 30
  strip2.setPixelColor(58 + offset, secondOrange);
  strip2.setPixelColor(60 + offset, Orange); // side 31
  strip2.setPixelColor(61 + offset, fourthOrange);
  strip2.setPixelColor(48 + offset, off); // end of side 25
  strip2.setPixelColor(22 + offset, off); // end of side 12
  strip2.setPixelColor(33 + offset, firstOrange); // side 17
  strip2.setPixelColor(32 + offset, secondOrange);
  strip2.setPixelColor(30 + offset, firstOrange); // side 16
  strip2.setPixelColor(31 + offset, secondOrange);
  strip2.setPixelColor(42 + offset, Orange); // side 22
  strip2.setPixelColor(43 + offset, fourthOrange);
  strip2.setPixelColor(47 + offset, Orange); // side 24
  strip2.setPixelColor(46 + offset, fourthOrange);
  strip2.setPixelColor(44 + offset, off); // end of side 23
  strip2.setPixelColor(29 + offset, off); // end of side 15
  strip2.show();
  delay(wait);

  // side 3, 4, 9, 11, 26, 27, 29, 30, 31, 24, 22, 16, 17, 18, 21
  strip2.setPixelColor(5, secondOrange); // side 3
  strip2.setPixelColor(4, Orange);
  strip2.setPixelColor(7, firstOrange); // side 4
  strip2.setPixelColor(6, secondOrange);
  strip2.setPixelColor(52, firstOrange);
  strip2.setPixelColor(51, secondOrange); // side 26
  strip2.setPixelColor(50, Orange);
  strip2.setPixelColor(21, Orange); // side 11
  strip2.setPixelColor(20, fourthOrange);
  strip2.setPixelColor(16, Orange); // side 9
  strip2.setPixelColor(17, fourthOrange);
  strip2.setPixelColor(56, secondOrange); // side 29
  strip2.setPixelColor(57, Orange);
  strip2.setPixelColor(59, secondOrange); // side 30
  strip2.setPixelColor(58, Orange);
  strip2.setPixelColor(60, fourthOrange); // side 31
  strip2.setPixelColor(61, off);
  strip2.setPixelColor(34, firstOrange); // 18
  strip2.setPixelColor(41, firstOrange); // 21
  strip2.setPixelColor(33, secondOrange); // side 17
  strip2.setPixelColor(32, Orange);
  strip2.setPixelColor(30, secondOrange); // side 16
  strip2.setPixelColor(31, Orange);
  strip2.setPixelColor(42, fourthOrange); // side 22
  strip2.setPixelColor(43, off);
  strip2.setPixelColor(47, fourthOrange); // side 24
  strip2.setPixelColor(46, off);
  // dome 2
  strip2.setPixelColor(5 + offset, secondOrange); // side 3
  strip2.setPixelColor(4 + offset, Orange);
  strip2.setPixelColor(7 + offset, firstOrange); // side 4
  strip2.setPixelColor(6 + offset, secondOrange);
  strip2.setPixelColor(52 + offset, firstOrange);
  strip2.setPixelColor(51 + offset, secondOrange); // side 26
  strip2.setPixelColor(50 + offset, Orange);
  strip2.setPixelColor(21 + offset, Orange); // side 11
  strip2.setPixelColor(20 + offset, fourthOrange);
  strip2.setPixelColor(16 + offset, Orange); // side 9
  strip2.setPixelColor(17 + offset, fourthOrange);
  strip2.setPixelColor(56 + offset, secondOrange); // side 29
  strip2.setPixelColor(57 + offset, Orange);
  strip2.setPixelColor(59 + offset, secondOrange); // side 30
  strip2.setPixelColor(58 + offset, Orange);
  strip2.setPixelColor(60 + offset, fourthOrange); // side 31
  strip2.setPixelColor(61 + offset, off);
  strip2.setPixelColor(34 + offset, firstOrange); // 18
  strip2.setPixelColor(41 + offset, firstOrange); // 21
  strip2.setPixelColor(33 + offset, secondOrange); // side 17
  strip2.setPixelColor(32 + offset, Orange);
  strip2.setPixelColor(30 + offset, secondOrange); // side 16
  strip2.setPixelColor(31 + offset, Orange);
  strip2.setPixelColor(42 + offset, fourthOrange); // side 22
  strip2.setPixelColor(43 + offset, off);
  strip2.setPixelColor(47 + offset, fourthOrange); // side 24
  strip2.setPixelColor(46 + offset, off);
  strip2.show();
  delay(wait);
  // side 3, 4, 5, 8, 9, 11, 26, 27, 29, 30, 31 <end>, 24 <end>, 22 <end>, 16, 17, 18, 21
  strip2.setPixelColor(5, fourthOrange); // side 3
  strip2.setPixelColor(4, off);
  strip2.setPixelColor(15, firstOrange);
  strip2.setPixelColor(8, firstOrange);
  strip2.setPixelColor(7, secondOrange); // side 4
  strip2.setPixelColor(6, Orange);
  strip2.setPixelColor(52, secondOrange);
  strip2.setPixelColor(51, secondOrange); // side 26
  strip2.setPixelColor(50, Orange);
  strip2.setPixelColor(21, fourthOrange); // side 11
  strip2.setPixelColor(20, off);
  strip2.setPixelColor(16, fourthOrange); // side 9
  strip2.setPixelColor(17, off);
  strip2.setPixelColor(56, Orange); // side 29
  strip2.setPixelColor(57, fourthOrange);
  strip2.setPixelColor(59, Orange); // side 30
  strip2.setPixelColor(58, fourthOrange);
  strip2.setPixelColor(60, off); // end of side 31
  strip2.setPixelColor(35, firstOrange); // side 18
  strip2.setPixelColor(34, secondOrange);
  strip2.setPixelColor(40, firstOrange); // side 21
  strip2.setPixelColor(41, secondOrange);
  strip2.setPixelColor(33, Orange); // side 17
  strip2.setPixelColor(32, fourthOrange);
  strip2.setPixelColor(30, Orange); // side 16
  strip2.setPixelColor(31, fourthOrange);
  strip2.setPixelColor(42, off); // end of side 22
  strip2.setPixelColor(47, off); // end of side 24
  // dome 2
  strip2.setPixelColor(5 + offset, fourthOrange); // side 3
  strip2.setPixelColor(4 + offset, off);
  strip2.setPixelColor(15 + offset, firstOrange);
  strip2.setPixelColor(8 + offset, firstOrange);
  strip2.setPixelColor(7 + offset, secondOrange); // side 4
  strip2.setPixelColor(6 + offset, Orange);
  strip2.setPixelColor(52 + offset, secondOrange);
  strip2.setPixelColor(51 + offset, secondOrange); // side 26
  strip2.setPixelColor(50 + offset, Orange);
  strip2.setPixelColor(21 + offset, fourthOrange); // side 11
  strip2.setPixelColor(20 + offset, off);
  strip2.setPixelColor(16 + offset, fourthOrange); // side 9
  strip2.setPixelColor(17 + offset, off);
  strip2.setPixelColor(56 + offset, Orange); // side 29
  strip2.setPixelColor(57 + offset, fourthOrange);
  strip2.setPixelColor(59 + offset, Orange); // side 30
  strip2.setPixelColor(58 + offset, fourthOrange);
  strip2.setPixelColor(60 + offset, off); // end of side 31
  strip2.setPixelColor(35 + offset, firstOrange); // side 18
  strip2.setPixelColor(34 + offset, secondOrange);
  strip2.setPixelColor(40 + offset, firstOrange); // side 21
  strip2.setPixelColor(41 + offset, secondOrange);
  strip2.setPixelColor(33 + offset, Orange); // side 17
  strip2.setPixelColor(32 + offset, fourthOrange);
  strip2.setPixelColor(30 + offset, Orange); // side 16
  strip2.setPixelColor(31 + offset, fourthOrange);
  strip2.setPixelColor(42 + offset, off); // end of side 22
  strip2.setPixelColor(47 + offset, off); // end of side 24
  strip2.show();
  delay(wait);
  // side 3 <end>, 4, 5, 8, 9 <end>, 11 <end>, 26, 27, 29, 30, 16, 17, 18, 21, 20
  strip2.setPixelColor(5, off); // end of side 3
  strip2.setPixelColor(14, firstOrange); // side 8
  strip2.setPixelColor(15, secondOrange);
  strip2.setPixelColor(9, firstOrange); // side 5
  strip2.setPixelColor(8, secondOrange);
  strip2.setPixelColor(7, Orange); // side 4
  strip2.setPixelColor(6, fourthOrange);
  strip2.setPixelColor(53, firstOrange); // side 27
  strip2.setPixelColor(52, secondOrange);
  strip2.setPixelColor(51, Orange); // side 26
  strip2.setPixelColor(50, fourthOrange);
  strip2.setPixelColor(21, off); // end of side 11
  strip2.setPixelColor(16, off); // end of side 9
  strip2.setPixelColor(56, fourthOrange); // side 29
  strip2.setPixelColor(57, off);
  strip2.setPixelColor(59, fourthOrange); // side 30
  strip2.setPixelColor(58, off);
  strip2.setPixelColor(39, firstOrange); // 20
  strip2.setPixelColor(35, secondOrange); // side 18
  strip2.setPixelColor(34, Orange);
  strip2.setPixelColor(40, secondOrange); // side 21
  strip2.setPixelColor(41, Orange);
  strip2.setPixelColor(33, fourthOrange); // side 17
  strip2.setPixelColor(32, off);
  strip2.setPixelColor(30, fourthOrange); // side 16
  strip2.setPixelColor(31, off);
  // dome 2
  strip2.setPixelColor(5 + offset, off); // end of side 3
  strip2.setPixelColor(14 + offset, firstOrange); // side 8
  strip2.setPixelColor(15 + offset, secondOrange);
  strip2.setPixelColor(9 + offset, firstOrange); // side 5
  strip2.setPixelColor(8 + offset, secondOrange);
  strip2.setPixelColor(7 + offset, Orange); // side 4
  strip2.setPixelColor(6 + offset, fourthOrange);
  strip2.setPixelColor(53 + offset, firstOrange); // side 27
  strip2.setPixelColor(52 + offset, secondOrange);
  strip2.setPixelColor(51 + offset, Orange); // side 26
  strip2.setPixelColor(50 + offset, fourthOrange);
  strip2.setPixelColor(21 + offset, off); // end of side 11
  strip2.setPixelColor(16 + offset, off); // end of side 9
  strip2.setPixelColor(56 + offset, fourthOrange); // side 29
  strip2.setPixelColor(57 + offset, off);
  strip2.setPixelColor(59 + offset, fourthOrange); // side 30
  strip2.setPixelColor(58 + offset, off);
  strip2.setPixelColor(39 + offset, firstOrange); // 20
  strip2.setPixelColor(35 + offset, secondOrange); // side 18
  strip2.setPixelColor(34 + offset, Orange);
  strip2.setPixelColor(40 + offset, secondOrange); // side 21
  strip2.setPixelColor(41 + offset, Orange);
  strip2.setPixelColor(33 + offset, fourthOrange); // side 17
  strip2.setPixelColor(32 + offset, off);
  strip2.setPixelColor(30 + offset, fourthOrange); // side 16
  strip2.setPixelColor(31 + offset, off);
  strip2.show();
  delay(wait);

  // 4, 5, 7, 8, 26, 27, 29 <end>, 30 <end>, 16 <end>, 17 <end>, 18, 20, 21
  strip2.setPixelColor(13, firstOrange);
  strip2.setPixelColor(14, secondOrange); // side 8
  strip2.setPixelColor(15, Orange);
  strip2.setPixelColor(9, secondOrange); // side 5
  strip2.setPixelColor(8, Orange);
  strip2.setPixelColor(7, fourthOrange); // side 4
  strip2.setPixelColor(6, off);
  strip2.setPixelColor(53, secondOrange); // side 27
  strip2.setPixelColor(52, Orange);
  strip2.setPixelColor(51, fourthOrange); // side 26
  strip2.setPixelColor(50, off);
  strip2.setPixelColor(56, off); // end of side 29
  strip2.setPixelColor(59, off); // end of side 30
  strip2.setPixelColor(38, firstOrange); // side 20
  strip2.setPixelColor(39, secondOrange);
  strip2.setPixelColor(35, Orange); // side 18
  strip2.setPixelColor(34, fourthOrange);
  strip2.setPixelColor(40, Orange); // side 21
  strip2.setPixelColor(41, fourthOrange);
  strip2.setPixelColor(33, off); // end of side 17
  strip2.setPixelColor(30, off); // end of side 16
  // dome 2
  strip2.setPixelColor(13 + offset, firstOrange);
  strip2.setPixelColor(14 + offset, secondOrange); // side 8
  strip2.setPixelColor(15 + offset, Orange);
  strip2.setPixelColor(9 + offset, secondOrange); // side 5
  strip2.setPixelColor(8 + offset, Orange);
  strip2.setPixelColor(7 + offset, fourthOrange); // side 4
  strip2.setPixelColor(6 + offset, off);
  strip2.setPixelColor(53 + offset, secondOrange); // side 27
  strip2.setPixelColor(52 + offset, Orange);
  strip2.setPixelColor(51 + offset, fourthOrange); // side 26
  strip2.setPixelColor(50 + offset, off);
  strip2.setPixelColor(56 + offset, off); // end of side 29
  strip2.setPixelColor(59 + offset, off); // end of side 30
  strip2.setPixelColor(38 + offset, firstOrange); // side 20
  strip2.setPixelColor(39 + offset, secondOrange);
  strip2.setPixelColor(35 + offset, Orange); // side 18
  strip2.setPixelColor(34 + offset, fourthOrange);
  strip2.setPixelColor(40 + offset, Orange); // side 21
  strip2.setPixelColor(41 + offset, fourthOrange);
  strip2.setPixelColor(33 + offset, off); // end of side 17
  strip2.setPixelColor(30 + offset, off); // end of side 16
  strip2.show();
  delay(wait);
  // 4 <end>, 5, 7, 8, 26 <end>, 27, 19, 18, 20, 21
  strip2.setPixelColor(12, firstOrange); // side 7
  strip2.setPixelColor(13, secondOrange);
  strip2.setPixelColor(14, Orange); // side 8
  strip2.setPixelColor(15, fourthOrange);
  strip2.setPixelColor(9, Orange); // side 5
  strip2.setPixelColor(8, fourthOrange);
  strip2.setPixelColor(7, off); // end of side 4
  strip2.setPixelColor(53, Orange); // side 27
  strip2.setPixelColor(52, fourthOrange);
  strip2.setPixelColor(51, off); // end of side 26
  strip2.setPixelColor(37, firstOrange); // 19
  strip2.setPixelColor(55, firstOrange); // 28
  strip2.setPixelColor(38, secondOrange); // side 20
  strip2.setPixelColor(39, Orange);
  strip2.setPixelColor(35, fourthOrange); // side 18
  strip2.setPixelColor(34, off);
  strip2.setPixelColor(40, fourthOrange); // side 21
  strip2.setPixelColor(41, off);
  // dome 2
  strip2.setPixelColor(12 + offset, firstOrange); // side 7
  strip2.setPixelColor(13 + offset, secondOrange);
  strip2.setPixelColor(14 + offset, Orange); // side 8
  strip2.setPixelColor(15 + offset, fourthOrange);
  strip2.setPixelColor(9 + offset, Orange); // side 5
  strip2.setPixelColor(8 + offset, fourthOrange);
  strip2.setPixelColor(7 + offset, off); // end of side 4
  strip2.setPixelColor(53 + offset, Orange); // side 27
  strip2.setPixelColor(52 + offset, fourthOrange);
  strip2.setPixelColor(51 + offset, off); // end of side 26
  strip2.setPixelColor(37 + offset, firstOrange); // 19
  strip2.setPixelColor(55 + offset, firstOrange); // 28
  strip2.setPixelColor(38 + offset, secondOrange); // side 20
  strip2.setPixelColor(39 + offset, Orange);
  strip2.setPixelColor(35 + offset, fourthOrange); // side 18
  strip2.setPixelColor(34 + offset, off);
  strip2.setPixelColor(40 + offset, fourthOrange); // side 21
  strip2.setPixelColor(41 + offset, off);
  strip2.show();
  delay(wait);

  // 5, 6, 7, 8, 27, 28, 19, 18 <end>, 21 <end>, 20, 27
  strip2.setPixelColor(36, firstOrange); // side 19 <left start>
  strip2.setPixelColor(37, secondOrange);
  strip2.setPixelColor(55, secondOrange); // 28 left half
  strip2.setPixelColor(54, firstOrange); // 28 right half
  strip2.setPixelColor(11, firstOrange);
  strip2.setPixelColor(12, secondOrange); // side 7
  strip2.setPixelColor(13, Orange);
  strip2.setPixelColor(14, fourthOrange); // side 8
  strip2.setPixelColor(15, off);
  strip2.setPixelColor(9, fourthOrange); // side 5
  strip2.setPixelColor(8, off);
  strip2.setPixelColor(53, fourthOrange); // side 27
  strip2.setPixelColor(52, off);
  strip2.setPixelColor(38, secondOrange); // side 20
  strip2.setPixelColor(39, Orange);
  strip2.setPixelColor(35, off); // end of side 18
  strip2.setPixelColor(40, off); // end of side 21
  // dome 2
  strip2.setPixelColor(36 + offset, firstOrange); // side 19 <left start>
  strip2.setPixelColor(37 + offset, secondOrange);
  strip2.setPixelColor(55 + offset, secondOrange); // 28 left half
  strip2.setPixelColor(54 + offset, firstOrange); // 28 right half
  strip2.setPixelColor(11 + offset, firstOrange);
  strip2.setPixelColor(12 + offset, secondOrange); // side 7
  strip2.setPixelColor(13 + offset, Orange);
  strip2.setPixelColor(14 + offset, fourthOrange); // side 8
  strip2.setPixelColor(15 + offset, off);
  strip2.setPixelColor(9 + offset, fourthOrange); // side 5
  strip2.setPixelColor(8 + offset, off);
  strip2.setPixelColor(53 + offset, fourthOrange); // side 27
  strip2.setPixelColor(52 + offset, off);
  strip2.setPixelColor(38 + offset, secondOrange); // side 20
  strip2.setPixelColor(39 + offset, Orange);
  strip2.setPixelColor(35 + offset, off); // end of side 18
  strip2.setPixelColor(40 + offset, off); // end of side 21
  strip2.show();
  delay(wait);
  // 5 <end>, 6, 7, 8 <end>, 27 <end>, 28, 20, 19
  strip2.setPixelColor(36, secondOrange); // side 19 <left start>
  strip2.setPixelColor(37, Orange);
  strip2.setPixelColor(55, Orange); // side 28
  strip2.setPixelColor(54, secondOrange);
  strip2.setPixelColor(10, firstOrange); // side 6
  strip2.setPixelColor(11, secondOrange);
  strip2.setPixelColor(12, Orange); // side 7
  strip2.setPixelColor(13, fourthOrange);
  strip2.setPixelColor(14, off); // end of side 8
  strip2.setPixelColor(9, off); // end of side 5
  strip2.setPixelColor(53, off); // end of side 27
  strip2.setPixelColor(38, Orange); // side 20
  strip2.setPixelColor(39, fourthOrange);
  // dome 2
  strip2.setPixelColor(36 + offset, secondOrange); // side 19 <left start>
  strip2.setPixelColor(37 + offset, Orange);
  strip2.setPixelColor(55 + offset, Orange); // side 28
  strip2.setPixelColor(54 + offset, secondOrange);
  strip2.setPixelColor(10 + offset, firstOrange); // side 6
  strip2.setPixelColor(11 + offset, secondOrange);
  strip2.setPixelColor(12 + offset, Orange); // side 7
  strip2.setPixelColor(13 + offset, fourthOrange);
  strip2.setPixelColor(14 + offset, off); // end of side 8
  strip2.setPixelColor(9 + offset, off); // end of side 5
  strip2.setPixelColor(53 + offset, off); // end of side 27
  strip2.setPixelColor(38 + offset, Orange); // side 20
  strip2.setPixelColor(39 + offset, fourthOrange);
  strip2.show();
  delay(wait);
  
  // 6, 7, 28, 20, 19
  strip2.setPixelColor(36, Orange); // side 19 <left start>
  strip2.setPixelColor(37, fourthOrange);
  strip2.setPixelColor(55, fourthOrange); // side 28
  strip2.setPixelColor(54, Orange);
  strip2.setPixelColor(10, secondOrange); // side 6
  strip2.setPixelColor(11, Orange);
  strip2.setPixelColor(12, fourthOrange); // side 7
  strip2.setPixelColor(13, off);
  strip2.setPixelColor(38, fourthOrange); // side 20
  strip2.setPixelColor(39, off);
  // dome 2
  strip2.setPixelColor(36 + offset, Orange); // side 19 <left start>
  strip2.setPixelColor(37 + offset, fourthOrange);
  strip2.setPixelColor(55 + offset, fourthOrange); // side 28
  strip2.setPixelColor(54 + offset, Orange);
  strip2.setPixelColor(10 + offset, secondOrange); // side 6
  strip2.setPixelColor(11 + offset, Orange);
  strip2.setPixelColor(12 + offset, fourthOrange); // side 7
  strip2.setPixelColor(13 + offset, off);
  strip2.setPixelColor(38 + offset, fourthOrange); // side 20
  strip2.setPixelColor(39 + offset, off);
  strip2.show();
  delay(wait);
  // 6, 7 <end>, 28, 20 <end>, 19
  strip2.setPixelColor(36, fourthOrange); // side 19 <left start>
  strip2.setPixelColor(37, off);
  strip2.setPixelColor(55, off); // side 28
  strip2.setPixelColor(54, fourthOrange);
  strip2.setPixelColor(10, Orange); // side 6
  strip2.setPixelColor(11, fourthOrange);
  strip2.setPixelColor(12, off); // end of side 7
  strip2.setPixelColor(38, off); // end of side 20
  // dome 2
  strip2.setPixelColor(36 + offset, fourthOrange); // side 19 <left start>
  strip2.setPixelColor(37 + offset, off);
  strip2.setPixelColor(55 + offset, off); // side 28
  strip2.setPixelColor(54 + offset, fourthOrange);
  strip2.setPixelColor(10 + offset, Orange); // side 6
  strip2.setPixelColor(11 + offset, fourthOrange);
  strip2.setPixelColor(12 + offset, off); // end of side 7
  strip2.setPixelColor(38 + offset, off); // end of side 20
  strip2.show();
  delay(wait);
  
  // 6, 19 <end>, 28 <end>, 19 <end>
  strip2.setPixelColor(36, off); // end of side 19 <left start>
  strip2.setPixelColor(54, off); // end of side 28
  strip2.setPixelColor(10, fourthOrange); // side 6
  strip2.setPixelColor(11, off);
  // dome 2
  strip2.setPixelColor(36 + offset, off); // end of side 19 <left start>
  strip2.setPixelColor(54 + offset, off); // end of side 28
  strip2.setPixelColor(10 + offset, fourthOrange); // side 6
  strip2.setPixelColor(11 + offset, off);
  strip2.show();
  delay(wait);
  
  // 6 <end>
  strip2.setPixelColor(10, off); // end of side 6
  // dome 2
  strip2.setPixelColor(10 + offset, off); // end of side 6
  strip2.show();
  delay(wait);
}*/

