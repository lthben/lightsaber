/*
 Author:  Benjamin Low (benjamin.low@digimagic.com.sg)
 
 Description: 
 Arduino code for controlling the ws2812 leds for a hacked 
 Hasbro lightsaber. There is a passive on-off battery switch 
 and two buttons. The first button is an active on-off switch 
 that will cycle through the modes as indicated by the colours
 ROYGBV. The second button will perform the animation effects 
 for each mode. 
 
 Revisions:
 11 Dec 2014: First version. Red mode only. 
 30 Dec 2014: Added new modes.
 
 Notes:
 Pixel density for the strip is 66 per metre.
 Ignore first few leds because they are not used.
 37 leds total on the 60cm strip. Therefore, they 
 are numbered from 0 to 36. We want 18 leds to light up, 
 so light up alternate leds starting from pos 2. 
 All brightness levels are maxed at 127 instead of 
 the possible 255 to conserve battery power.
 
 */

#include <Adafruit_NeoPixel.h>

#define PIN 6 //data pin for the leds

Adafruit_NeoPixel strip = Adafruit_NeoPixel(37, PIN, NEO_GRB + NEO_KHZ800);

const int REDMODE = 1, ORANGEMODE = 2, YELLOWMODE = 3, GREENMODE = 4, BLUEMODE = 5, VIOLETMODE = 6; //the different modes for the animation
int mode;

const int POWERBUTTONPIN = 9; 
const int ANIMATIONBUTTONPIN = 10; 

boolean isPowerButtonPressed; //prevent state switching when button is held down
boolean isAnimationButtonPressed; 

const int ANIMATIONSPEED = 25;//delay in ms

//REDMODE
int healthBar = 0; //tracks amount of health for REDMODE

//ORANGEMODE
boolean isDoOrange = false; //triggers on and off the ORANGEMODE animation effect
int brightLevel = 127; //brightness in ORANGEMODE only
int brightLevelDirection = 1;

//YELLOWMODE
boolean isDoYellow = false;
const int STARTCOLOURINDEX = 35;
int colourIndex = STARTCOLOURINDEX; //to keep track of the Wheel colour

//GREENMODE
boolean isDoGreen = false;
int whichDirection; //randomised direction for the glitch animation
long startTime, timeInterval;
const int LOWERTIMEBOUND = 500, UPPERTIMEBOUND = 2000; //for the randomised time interval duration

//BLUEMODE
boolean isDoBlue = false;
boolean isBlueOnInitialised = false; //for initialising the animation ON animation
boolean isBlueOffInitialised = false; //for initialising the animation OFF animation

//VIOLETMODE
boolean isDoViolet = false;

void setup() {
        pinMode(POWERBUTTONPIN, INPUT);
        pinMode(ANIMATIONBUTTONPIN, INPUT);
        Serial.begin(9600);
        strip.begin();
        strip.show();

        mode = GREENMODE;
}

void loop() {

        power_animation(); //power on and off animations for each mode

        mode_animation(); //animation effects for each mode       
}




















