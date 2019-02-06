// IO&E Project 1 
// Thompson & Truong 

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NEOPIN 6

// *******LIGHT SENESOR********
int photocellPin = 9;    // photocell sensor input
int photocellValue = 0;  // variable to store the value coming from the photocell val

// *******NEOPIXEL STRIP********
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, NEOPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {

// *******LIGHT SENSOR********
  // read the value from the sensor:
  photocellValue = analogRead(photocellPin);  
  photocellValue = constrain(photocellValue, 200, 800); //adjust depending on environment.   

  Serial.print("incoming value from photocell sensor =");
  Serial.println(photocellValue);
  delay(100);  

  if(photocellValue < 250){
    rainbowA(20);
  } else {
    rainbowB(20);
  };

}


void rainbowA(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, WheelA((i+j) & 255));
      
    }
    strip.show();
    //delay(wait);
  }
}


void rainbowB(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, WheelB((i+j) & 255));
      
    }
    strip.show();
    //delay(wait);
  }
}


// Red-Orange scale
uint32_t WheelA(byte WheelPos) {
  
  WheelPos = 255 - WheelPos;

  if(WheelPos < 85) {
    return strip.Color(255, 255 - WheelPos * 3, 0);
   }
  
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255, WheelPos, 0);
  }

  WheelPos -= 170;
  return strip.Color(255, 100 - WheelPos * 3, 0); 

}


// Blue-Green scale
uint32_t WheelB(byte WheelPos) {
  
  WheelPos = 255 - WheelPos;

// GREEN-BLUE
if(WheelPos < 85) {
  return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
}

if(WheelPos < 170) {
  WheelPos -= 85;
  return strip.Color(0, 255 - WheelPos * 3, 255 - WheelPos * 3);
}

  WheelPos -= 170;
  return strip.Color(0, WheelPos * 3, WheelPos * 3);

}







