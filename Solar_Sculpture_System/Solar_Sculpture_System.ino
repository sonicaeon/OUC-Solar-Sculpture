/****************************************************************************
 * Connections:
 * The Sound Detector is connected to the Adrduino as follows:
 * (Sound Detector -> Arduino pin)
 * GND → GND
 * VCC → 5V
 * Gate → Pin 18
 * Envelope → A15
 * 
 * LCD Display:
 * The LCD Display utilizes two LCD objects to control a 40x4 character display
 * where each object has control over the top and bottom 20x2 character rows
 * respectively. Where the difference between objects is solely the enable pins
 * en and en2 which control top and bottom 20x2 displays respectively.
 * 
 * Development environment specifics:
 * Using Arduino IDe 1.8.5
 * LiquidCrystal 1.0.7
 * Adafruit NeoPixel 1.1.6
 * DistanceGP2Y0A21YK
 ******************************************************************************/
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>
#include <DistanceGP2Y0A21YK.h>

// pin setup for LCD display (rw not used, goes to gnd)
// pin 1 on lcd is d7 -> pin 8 is d0 for lcd pinout
const int rs = 8, en = 7, en2 = 9, 
          d0 = 22, d1 = 23, d2 = 24, d3 = 25, 
          d4 = 26, d5 = 27, d6 = 28, d7 = 29;

// initalize library with connected pins to the arduino
LiquidCrystal lcd(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);
LiquidCrystal lcd2(rs, en2, d0, d1, d2, d3, d4, d5, d6, d7);

// initalize IRsensor object library
//DistanceGP2Y0A21YK IRSensor;
//DistanceGP2Y0A21YK IRSensor2;
//DistanceGP2Y0A21YK IRSensor3;
//DistanceGP2Y0A21YK IRSensor4;
DistanceGP2Y0A21YK IRSensor5;
//DistanceGP2Y0A21YK IRSensor6;
//DistanceGP2Y0A21YK IRSensor7;
//DistanceGP2Y0A21YK IRSensor8;
int distance = 0, distance2 = 0, distance3 = 0, distance4 = 0,
    distance5 = 0, distance6 = 0, distance7 = 0, distance8 = 0;
int brightness = 64;

// Define hardware connections
#define PIN_GATE_IN 18 // sound sensor digital pin
#define IRQ_GATE_IN 0
#define PIN_ANALOG_IN A15 // for sound sensor envelope
#define IRS_PIN A9 // analog pin for IR sensor 1
#define IRS_PIN2 A10
#define IRS_PIN3 A11
#define IRS_PIN4 A8
#define IRS_PIN5 A7
#define IRS_PIN6 A6
#define IRS_PIN7 A5
#define IRS_PIN8 A4
#define IRS_PIN9 A3
#define IRS_PIN10 A2
#define IRS_PIN11 A1
#define IRS_PIN12 A0
#define BACKLIGHT 4 // lcd display
#define LED1 14 // Digital pin for LED strip 1
#define LED2 15 // Digital pin for LED strip 2
#define STRIP_NUM 59 // # of pixels addressed to the strip
#define STRIP2_NUM 59
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
uint32_t red = strip.Color(0, 255, 0);
uint32_t green = strip.Color(255, 0, 0);
uint32_t blue = strip2.Color(0, 0, 255);
uint32_t yellow = strip2.Color(255, 255, 0);
uint32_t orange = strip2.Color(177 ,235, 58);
uint32_t indigo = strip2.Color(86 ,189, 207);
uint32_t idk = strip2.Color(6, 13, 6);
uint32_t white = strip2.Color(255, 255, 255);
uint32_t magenta = strip.Color(0, 255, 255);
uint32_t OC_Purple = strip.Color(50, 100, 220);
uint32_t OC_Gold = strip2.Color(150, 150, 0);

void setup()
{
  Serial.begin(9600);

  // Configure backlight control pin: LOW for off, HIGH for on
  pinMode(BACKLIGHT, OUTPUT);
  digitalWrite(BACKLIGHT, LOW);
  
  // Configure input to interrupt
  pinMode(PIN_GATE_IN, INPUT);
  //attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE);

  // initalize IRsensor(s)
  //IRSensor.begin(IRS_PIN);
  //IRSensor2.begin(IRS_PIN2);
  //IRSensor3.begin(IRS_PIN3);
  //IRSensor4.begin(IRS_PIN4);
  IRSensor5.begin(IRS_PIN5);
  //IRSensor6.begin(IRS_PIN6);
  //IRSensor7.begin(IRS_PIN7);
  //IRSensor8.begin(IRS_PIN8);

  // Display status
  Serial.println("Initialized");

  // initalize LCD
  displayMessage();

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
  int value = 0;
  brightness = 0;
  strip.setBrightness(offBright);
  strip2.setBrightness(offBright);
  strip.show();
  strip2.show();

  // query the distance (cm) from the sensor(s)
  //distance = IRSensor.getDistanceCentimeter();
  //distance2 = IRSensor2.getDistanceCentimeter();
  //distance3 = IRSensor3.getDistanceCentimeter();
  //distance4 = IRSensor4.getDistanceCentimeter();
  distance5 = IRSensor5.getDistanceCentimeter();
  //distance6 = IRSensor6.getDistanceCentimeter();
  //distance7 = IRSensor7.getDistanceCentimeter();
  //distance8 = IRSensor8.getDistanceCentimeter();

  // hide the message until sensor triggers
  displayMessage();
  lcd.noDisplay();
  lcd2.noDisplay();
  
  // Check the envelope input
  value = analogRead(PIN_ANALOG_IN);

  // if sound sensor triggered
  if(value > 40)
  {
    for(int i = 0;i < 8;i++)
    {
      ledPattern1(OC_Purple, OC_Gold);
    }
    //brightness = 0;
  }

  // Query the distance value if any of the sensors has triggered
  //checkProximity(distance, 1);
  //checkProximity(distance2, 2);
  //checkProximity(distance3, 3);
  //checkProximity(distance4, 4);
  checkProximity(distance5, 5);
  //checkProximity(distance6, 6);
  //checkProximity(distance7, 7);
  //checkProximity(distance8, 8);

  // turn off the backlight to conserve power when not needed
  digitalWrite(BACKLIGHT, LOW);

  // <Debug> the value to serial monitor
  Serial.print("\nValue: ");
  Serial.print(value);

  // <Debug> the distance to serial monitor
  Serial.print("\nDistance in centimeters: ");
  Serial.print(distance);

  // update the LED object, will begin to change colors afterwards
  strip.show();
  strip2.show();
  
  // pause for 250ms
  delay(250);
}

// configure the message the LCD screen displays
void displayMessage()
{
  // state the size of use the lcd has access to
  // e.g.: 40x4 display 
  lcd.begin(40,2);
  lcd2.begin(40,2);

  // clear the screen before writing
  lcd.clear();
  lcd2.clear();
  
  // (0,0) is the first line of the display
  // setCursor sets starting position to print to
  // controls top 2 lines
  lcd.setCursor(6,0);
  lcd.print("Estimated Annual Solar Energy");
  lcd.setCursor(6,1);
  lcd.print("Produced: ~1269 kWh/year");

  // controls bottom 2 lines
  lcd2.setCursor(6,0);
  lcd2.print("Money Saved: $122.60 per Year");
  lcd2.setCursor(6,1);
  lcd2.print("SPONSERED BY OUC");
}

void ledPattern1(uint32_t c1, uint32_t c2)
{
  colorFill(c1, c2, 10);
  colorFill(c2, c1, 10);
}

void ledPattern2(uint32_t c1, uint32_t c2)
{
  colorExpand(c1, c2, 50);
  colorShrink(c2, 50);
  colorAlternate(c1, c2, 500);
  colorExpand(c2, c1, 50);
  colorShrink(c1, 50);
}

void ledPattern3(uint32_t c1, uint32_t c2, uint32_t c3)
{
  for(int16_t i = 0;i < 20;i++)
  {
    colorFlip(c1, c2, c3, 100);
    colorFlip(c3, c2, c1, 100);
  }
}

// Fill the dots one after the other with two colors alternating
void colorFill(uint32_t c1, uint32_t c2, uint8_t wait)
{
  for(uint16_t i = 0;i < strip.numPixels(); i++)
  {
    // for every ODD pixel use color 1
    if(i % 2)
    {
      strip.setPixelColor(i, c1);
    }
    else
    {
      // for every EVEN pixel use color 2
      strip.setPixelColor(i, c2);
    }
    strip.setBrightness(brightness);
    strip.show();
    brightness++;
    delay(wait);
  }
  strip.setBrightness(quarterBright);
  strip.show();
}

void colorFlip(uint32_t c1, uint32_t c2, uint32_t c3, uint8_t wait)
{
  //int pixelNum = strip2.numPixels();
  int rLength = 15, bLength = 12, yLength = 6;
  int rStart = 0, rEnd = 45;
  int bStart = 15, bEnd = 33;
  int yStart = 27;

  /*// if odd number of pixel
  if(pixelNum % 2)
  {
    pixelNum += 1; // make it even
  }*/

  // fill red, blue, yellow (middle) on the left side
  for(uint16_t i = 0;i < rLength;i++)
  {
    strip2.setPixelColor(rStart, c1);
    //strip2.show(); 
    rStart++;
  }
  for(uint16_t j = 0;j < bLength;j++)
  {
    strip2.setPixelColor(bStart, c2);
    //strip2.show();
    bStart++;
  }
  for(uint16_t k = 0;k < yLength;k++)
  {
    strip2.setPixelColor(yStart, c3);
    //strip2.show();
    yStart++;
  }
  // fill blue red on the right
  for(uint16_t j = 0;j < bLength;j++)
  {
    strip2.setPixelColor(bEnd, c2);
    //strip2.show();
    bEnd++;
  }
  for(uint16_t i = 0;i < rLength;i++)
  {
    strip2.setPixelColor(rEnd, c1);
    //strip2.show(); 
    rEnd++;
  }
  strip2.show();
  delay(wait); // pause before beginning alternating pattern
  // flip and alternate red and yellow
    
  // first half fill
  /*for(uint16_t i = 0;i < (pixelNum / 2); i++)
  {
    strip2.setPixelColor(i, c1);
  }
  // second half fill
  for(uint16_t i = (pixelNum / 2);i < pixelNum; i++)
  {
    strip2.setPixelColor(i, c2);
  }
  strip2.setBrightness(brightness);
  strip2.show();
  if(brightness <= 255)
    brightness += 20;
  delay(wait);*/
}

void colorExpand(uint32_t c1, uint32_t c2, uint8_t wait)
{
  int middlePixel = strip2.numPixels() / 2;
  int leftPixel = middlePixel - 1;
  int rightPixel = middlePixel + 1;

  // fill strip with color 2
  for(uint16_t i = 0;i < strip2.numPixels();i++)
  {
    strip2.setPixelColor(i, c2);
  }
  strip2.show();
  delay(2500);
  // start from the middle pixel in the strip
  strip2.setPixelColor(middlePixel, c1);
  strip2.show();
  delay(wait);
  // expand from middle changing colors one pixels on each side at a time
  for(uint16_t i = 0;i < middlePixel;i++)
  {
    strip2.setPixelColor(leftPixel, c1);
    strip2.setPixelColor(rightPixel, c1);
    strip2.setBrightness(brightness);
    strip2.show();
    leftPixel--;
    rightPixel++;
    if(brightness <= 255)
      brightness += 2;
    //brightness += 20;
    delay(wait);
  }
  delay(wait);
}

void colorShrink(uint32_t c, uint8_t wait)
{
  int startPixel = 0;
  int endPixel = strip2.numPixels();
  int middlePixel = endPixel / 2;

  for(uint16_t i = 0;i < middlePixel;i++)
  {
    strip2.setPixelColor(startPixel, c);
    strip2.setPixelColor(endPixel, c);
    strip2.setBrightness(brightness);
    strip2.show();
    endPixel--;
    startPixel++;
    brightness += 2;
    //brightness += 20;
    delay(wait);
  }
  strip2.setBrightness(quarterBright);
  strip2.setPixelColor(middlePixel, c);
  strip2.show();
  delay(wait);
}

void colorAlternate(uint32_t c1, uint32_t c2, uint8_t wait)
{
  for(uint16_t i = 0;i < strip2.numPixels();i++)
  {
    strip2.setPixelColor(i, c1);
  }
  strip2.show();
  delay(1000);
  for(uint16_t i = 0;i < strip2.numPixels();i++)
  {
    strip2.setPixelColor(i, c2);
  }
  strip2.show();
  delay(wait);
  for(int i = 0;i < 8;i++)
  {
      for(uint16_t i = 0;i < strip2.numPixels();i++)
      {
        strip2.setPixelColor(i, c1);
      }
      strip2.show();
      delay(wait);
      for(uint16_t i = 0;i < strip2.numPixels();i++)
      {
        strip2.setPixelColor(i, c2);
      }
      strip2.show();
      delay(wait);
      wait -= 50;
  }
}

void rainbowFill()
{
  int r = 255, g = 0, b = 0;
  bool redFlag = true, blueFlag = false;
  for(uint16_t i = 0;i < 12;i++)
  {
    for(uint16_t j = 0;j < strip2.numPixels(); j++)
    {
      strip2.setPixelColor(j, g, r, b);
      strip2.show();
      if(redFlag)
      {
        r--;
        g++;
        if(g >= 255)
        {
          redFlag = false;
          blueFlag = true;
        }
      }
      else if(blueFlag)
      {
        g--;
        b++;
        if(b >= 255)
        {
          blueFlag = false;
        }
      }
      else
      {
        b--;
        r++;
        if(r >= 255)
        {
          redFlag = true;
        }
      }
    }
    delay(250);
  }
  delay(50);
}

void rainbowChase()
{
  int r = 255, g = 0, b = 0;
  bool redFlag = true, blueFlag = false;
  for(uint16_t i = 0;i < 12;i++)
  {
    for(uint16_t j = 0;j < strip2.numPixels(); j++)
    {
      strip2.setPixelColor(j, g, r, b);
      strip2.show();
      if(redFlag)
      {
        r-=3;
        g+=3;
        if(g >= 255)
        {
          redFlag = false;
          blueFlag = true;
        }
      }
      else if(blueFlag)
      {
        g-=3;
        b+=3;
        if(b >= 255)
        {
          blueFlag = false;
        }
      }
      else
      {
        b-=3;
        r+=3;
        if(r >= 255)
        {
          redFlag = true;
        }
      }
    }
    delay(250);
  }
  delay(50);
}

void colorExplosion(uint32_t c1, uint32_t c2, uint8_t wait)
{
  int startPixel = 0;
  int endPixel = strip2.numPixels();
  int middlePixel = endPixel / 2;
  int moveMiddle1 = middlePixel;
  int moveMiddle2 = middlePixel;
  int prevStartPixel = startPixel;
  int prevEndPixel = endPixel;
  int prevMiddle1 = middlePixel;
  int prevMiddle2 = middlePixel;
  int randNum, randNum2, randNum3, randNum4;

  for(uint16_t i = 0;i < strip2.numPixels();i++)
  {
    strip2.setPixelColor(i, c2);
  }
  strip2.setPixelColor(startPixel, c1);
  strip2.setPixelColor(middlePixel, c1);
  strip2.setPixelColor(endPixel, c1);
  strip2.show();
  delay(1000);
  for(uint16_t i = 0;i < middlePixel;i++)
  {
    strip2.setPixelColor(startPixel, c1);
    strip2.setPixelColor(moveMiddle1, c1);
    strip2.setPixelColor(moveMiddle2, c1);
    strip2.setPixelColor(endPixel, c1);
    strip2.show();
    startPixel++;
    moveMiddle1--;
    moveMiddle2++;
    endPixel--;
    delay(wait);
    strip2.setPixelColor(prevStartPixel, c2);
    strip2.setPixelColor(prevMiddle1, c2);
    strip2.setPixelColor(prevMiddle2, c2);
    strip2.setPixelColor(prevEndPixel, c2);
    strip2.show();
    prevStartPixel = startPixel;
    prevMiddle1 = moveMiddle1;
    prevMiddle2 = moveMiddle2;
    prevEndPixel = endPixel;
    delay(wait);
  }
  for(uint16_t j = 0;j < 50;j++)
  {
    randNum = random(strip2.numPixels());
    strip2.setPixelColor(randNum, c1);
    strip2.show();
    delay(50);
    strip2.setPixelColor(randNum, c2);
    strip2.show();
  }
}

// query the distance from the IR sensor, if triggered in the specified range
// trigger a specific LED pattern depending on which sensor was triggered
void checkProximity(int dist, int senseNum)
{
  if(dist >= 5 && dist <= 29)
  { 
    // turn backlight on & message
    lcd.display();
    lcd2.display();
    digitalWrite(BACKLIGHT, HIGH);

    strip.setBrightness(quarterBright);
    strip2.setBrightness(quarterBright);
    //brightness = quarterBright;
    brightness = 16;
    strip.show();
    strip2.show();
    
    // set pattern
    switch(senseNum)
    {
      case 1: ledPattern2(OC_Purple, OC_Gold);
              break;
      case 2: rainbowFill();
              break;
      case 3: rainbowChase();
              break;
      case 4: colorExplosion(yellow, blue, 50);
              break;
      case 5: ledPattern3(blue, yellow, green);
              break;
      default: break;
    }
    
    // update the LEDs
    strip.show();
    strip2.show();
    delay(5000); // wait 5 seconds for readability
  }
}

