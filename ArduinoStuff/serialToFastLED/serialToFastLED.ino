#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#include <FastLED.h>

#define DATA_PIN 6

const int NUM_LEDS = 32 * 8;

const int bufferLength = NUM_LEDS * 3;

CRGB leds[NUM_LEDS];

byte buf[bufferLength];

void setup() {

  // initial Serial com
  Serial.begin(250000, SERIAL_8E1);

  // waiting time after request a package
  Serial.setTimeout(1000);

  // setup FastLED
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  // waiting f Serial is ready
  while(!Serial) delay(1);
  
}

void loop() {

  // flush Serrial
  while(Serial.available() > 0) Serial.read();

  // send for start transmission
  Serial.write(0xff);

  // read all color values
  int lastCount = Serial.readBytes(buf, bufferLength);
  
  // put on LEDs if there are enought byte. else random demo mode
  if(lastCount == bufferLength)
    for( int i = 0 ; i < bufferLength ; i++)
      leds[i/3][i%3] = buf[i];
  else
    for( int i = 0 ; i < bufferLength ; i++){
      leds[i/3][i%3] = random(0,2);
    }

  // show on LEDs
  FastLED.show(); // needs ~ 8ms

}
