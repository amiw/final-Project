// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS    10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

boolean blink_toggle = 0; // true or false

// analog variables


const int analogInPin1 = A1;// Analog input pin that the potentiometer is attached to

int sensorValue = 0; // value read from the pot
int sensorValue1 = 0;// value output to the PWM (analog out)

float outputValue1 = 0;

// end analog variables





void setup() {

// analog setup()

  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

// end analog setup()
  
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

int peopleCount = 0;
bool peopleState = false;


void loop() {

// analog loop()
  
 sensorValue1 = analogRead(analogInPin1);

 outputValue1 = sensorValue1 / 1023.;

 Serial.print(peopleCount);
 Serial.print('\t');
 Serial.print(sensorValue1);
 Serial.print('\t');
 Serial.println(outputValue1);

 if (outputValue1 > 0.04 && !peopleState){
  peopleState = true;
  peopleCount++;
 } else if (outputValue1 < 0.02 && peopleState) {
  peopleState = false;
 }
  
// end analog loop()

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<min(peopleCount,NUMPIXELS);i++){
      
   if(peopleCount==NUMPIXELS){
     pixels.setPixelColor(i, pixels.Color(150, 150, 150)); 
     peopleCount=0;
   }

  
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
   else if (sensorValue1 < .14 * 1024)
    {
      pixels.setPixelColor(i, pixels.Color(150, 0, 0)); // Moderately bright green color.
    }
    else if(sensorValue1 < .28 * 1024)
    {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));  
    }else if(sensorValue1 < .34 * 1024)
    {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));  
    }
     else if(sensorValue1 < .42 * 1024)
    {
    pixels.setPixelColor(i, pixels.Color(0, 150, 150));  
    }
     else if(sensorValue1 < .56 * 1024)
    {
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));  
    }
     else if(sensorValue1 < .70 * 1024)
    {
    pixels.setPixelColor(i, pixels.Color(150, 0, 150));  
    }
     else if(sensorValue1 < .84 * 1024)
    {
    pixels.setPixelColor(i, pixels.Color(150, 150, 150));  
    }
  }

  pixels.show(); // This sends the updated pixel color to the hardware.

  //delay(delayval); // Delay for a period of time (in milliseconds).

  //blink_toggle = !blink_toggle; // flip true to false, fasle to true

}
