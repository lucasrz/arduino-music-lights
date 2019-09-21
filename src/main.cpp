#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 300
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
const int brightnessButtonPin = 2;
const int blinkButtonPin = A1;
const int knobPin = A0;
int buttonCount = 0;
boolean blinkState = false;
int outputValue = 0;
int pastSensorValue = 0;
int sensorValueMapped = 0;
boolean isFilled = false;


void setPixel(int Pixel, byte red, byte green, byte blue)
{
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
}


void fillStrip(int start, int count)
{
  int r  = random(0,255);
  int g  = random(0,255);
  int b = random(0,255);
  for (int i = start; i < count; i++)
  {
    setPixel(i, r,g,b );

    strip.show();
  }
    // delay(speedDelay);

}

void unfillStrip(int start, int count)
{
  for (int i = start; i >= (start - count); i--)
  {
    setPixel(i, 0, 0, 0);
    strip.show();
  }

}

void fillBackwards(int start, int count)
{
  int r  = random(0,255);
  int g  = random(0,255);
  int b = random(0,255);
  for (int i = start; i >=  count; i--)
  {
    setPixel(i, r, g, b);
    strip.show();
  }

}

void blink() {
  blinkState = !blinkState;
  if(blinkState) {
    strip.setBrightness(1);
    strip.show();
  } else {
    strip.setBrightness(random(0,200));
    strip.show();
  }
}

void sendRandom(int start, int count, boolean reverse)
{
  int r  = random(0,255);
  int g  = random(0,255);
  int b = random(0,255);
  
  if(reverse) {  
    for (int i = start; i >= count; i--)
    {
      strip.setBrightness(random(0,200));
      setPixel(i, r, g, b);
      setPixel(i + random(0,50), 0, 0, 0);
      strip.show();
    }
  } else {
    for (int i = start; i <= count; i++)
    {
      strip.setBrightness(random(0,200));
      setPixel(i, r, g, b);
      setPixel(i - random(0,50), 0, 0, 0);
      strip.show();
    }
  }

  strip.clear();
}

void sendOne(int start, int count, boolean reverse)
{
  int r  = random(0,255);
  int g  = random(0,255);
  int b = random(0,255);

  if(reverse) {  
    for (int i = start; i >= count; i--)
    {
      strip.setBrightness(random(0,200));
      setPixel(i, r, g, b);
      setPixel(i + 1, 0, 0, 0);
      strip.show();
    }
  } else {
    for (int i = start; i <= count; i++)
    {
      strip.setBrightness(random(0,200));
      setPixel(i, r, g, b);
      setPixel(i - 1, 0, 0, 0);
      strip.show();
    }
  }

  strip.clear();
}

void sendMany(int start, int count, boolean reverse)
{
  int r  = random(0,255);
  int g  = random(0,255);
  int b = random(0,255);

   if(reverse) {  
    for (int i = start; i >= count; i--)
    {
      strip.setBrightness(random(0,200));
      setPixel(i, r, g, b);
      setPixel(i + 25, 0, 0, 0);
      strip.show();
    }
  } else {
    for (int i = start; i <= count; i++)
    {
      strip.setBrightness(random(0,200));
      setPixel(i, r, g, b);
      setPixel(i - 25, 0, 0, 0);
      strip.show();
    }
  }

  strip.clear();
}

void fillRandom ( ) {

}

void controlBrightness() {
    strip.show();
    delay(10);
}

void loop()
{
  int sensorValue;

  for (int i = 0; i < 100; i++)
  {
    sensorValue = analogRead(A0);
    sensorValue = sensorValue * 2;
    // sensorValueMapped = map(sensorValue, 0, 450, 0, 300);
    if( sensorValue  >= 350  && sensorValue != pastSensorValue) {
        Serial.write("beat");
        sensorValueMapped = random(1, 300);
        switch(random(1,8)) {
          case 1: 
            sendOne(0, sensorValueMapped + random(0, 100), false);
              isFilled = true;
            break;
          case 2: 
            sendRandom(0, sensorValueMapped + random(0, 100), false);
              isFilled = true;
          break;
          case 3: 
            sendMany(0, sensorValueMapped + random(0, 100), false);
              isFilled = true;
          break;
          case 4: 
            sendOne(300, sensorValueMapped - random(0, 100), true);
              isFilled = true;
          break;
          case 5: 
            sendRandom(300, sensorValueMapped - random(0, 100), true);
              isFilled = true;
          break;
          case 6: 
            sendMany(300, sensorValueMapped - random(0, 100), true);
              isFilled = true;
          break;
           case 7: 
            fillStrip(0, sensorValueMapped);
              isFilled = true;
          break;
           case 8: 
            fillBackwards(300, sensorValueMapped);
              isFilled = true;
          break;
        }
        isFilled = false;
        blink();
      } else if( sensorValue > 150 && sensorValue > pastSensorValue) {
        blink();
        Serial.write("weak");
        if(isFilled == false) {
          int n =random(1,3);
          Serial.println(n);
          switch(n) {
            case 1: 
              fillStrip(0, sensorValueMapped);
              isFilled = true;
            break;
            case 2:
              fillBackwards(300, sensorValueMapped);
              isFilled = true;
            break;
          }
        } else {
          blink();
        }
      } 
  }
    pastSensorValue = sensorValue;
}

void setup()
{
  strip.begin();
  strip.setBrightness(100);
  strip.show();
  Serial.begin(9600);
}