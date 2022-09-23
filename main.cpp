#include <Arduino.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Adafruit_NeoPixel.h>

#define PIN        6 // la pin 
#define NUMPIXELS 24 // nbre de led (ou pixel) qui s'allument

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 50 // valeur du délai en ms

// état du capteur
int lastState = 0;
int SensorState = 0;

SoftwareSerial softwareSerial(10, 11);
DFRobotDFPlayerMini player;
//===========================================================
void setup()
{
  //---------------------------------------------------
    Serial.begin(9600);
    softwareSerial.begin(9600);
    player.begin(softwareSerial);
    
    // player.play(1);
    player.stop();
    // delay(3000);
    player.volume(25);

    pinMode(2, INPUT);

    // ruban led
    pixels.begin();
    pixels.setBrightness(25);
    pixels.clear();
    pixels.show();
}
//===========================================================

void loop()
{
    // play pause avec le capteur
  int state = digitalRead(2);
   Serial.println(state);
  if (lastState == 0 && state == 1) {
    if (SensorState == 0) {
      player.start();
      SensorState = 1;
    //   player.next();

      
      for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        pixels.show();   // Send the updated pixel colors to the hardware.
      }
      
    }
    else {
      player.stop();
      SensorState = 0;

      pixels.clear();
      pixels.show();
    }
  }
  lastState = state;

}