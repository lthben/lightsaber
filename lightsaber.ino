/*
Author:      Benjamin Low (Lthben@gmail.com)
 Date:        11 Dec 2014
 Description: 
 Arduino code for controlling the ws2812 leds for 
 a hacked Hasbro lightsaber. 
 This version of the lightsaber tracks a health bar determined by 
 the number of lit leds.
 There is a passive on-off switch and two buttons. 
 The first button is an active on-off switch that will reset the 
 health bar to 18. 
 The second button will decrement the health bar by 1 each time it is pressed.
 */

#include <Adafruit_NeoPixel.h>

#define PIN 6 //data pin for the leds

Adafruit_NeoPixel strip = Adafruit_NeoPixel(39, PIN, NEO_GRB + NEO_KHZ800);

const int switchPin = 11;
const int powerButtonPin = 12;
const int healthButtonPin = 13;

boolean isPowerButtonPressed, isPowerOn;
boolean isHealthButtonPressed;

int healthBar = 0; //full health has 18 bars 

void setup() {
        pinMode(switchPin, INPUT);
        pinMode(powerButtonPin, INPUT);
        pinMode(healthButtonPin, INPUT);
        Serial.begin(9600);
        strip.begin();
        strip.show();
}

void loop() {

        if (digitalRead(switchPin) == HIGH) { //passive power switch 

                //active power button
                if (digitalRead(powerButtonPin) == HIGH){ 

                        if (isPowerButtonPressed == false){

                                isPowerButtonPressed = true;

                                if  (isPowerOn == false) {

                                        isPowerOn = true;

                                        power_on_animation();

                                        Serial.println("power on\n");
                                } 
                                else if (isPowerOn == true) {

                                        isPowerOn = false;

                                        power_off_animation();

                                        Serial.println("power off\n\n");
                                }
                        }
                }   
                else if (digitalRead(powerButtonPin) == LOW) {
                        isPowerButtonPressed = false;       
                }

                // health button
                if (digitalRead(healthButtonPin) == HIGH) {

                        if (isHealthButtonPressed == false) {

                                isHealthButtonPressed = true;

                                decrement_health();
                                
                                Serial.print("health: ");
                                Serial.println(healthBar); 
                        }
                } 
                else if (digitalRead(healthButtonPin) == LOW) {
                        isHealthButtonPressed = false;
                }
        }
}

/*
Pixel density for the strip is 66 per metre.
 Ignore first few leds because they are not used.
 39 leds total on the ~60cm strip. Therefore, they 
 are numbered from 0 to 38.
 We want 18 leds to light up, so light up
 alternate leds starting from pos 4. 
 */
void power_on_animation() {
        
        healthBar = 18;
        
        for (int ledPos=4; ledPos<39; ledPos+=2) {
                int shownHealth = (ledPos - 4)/2;      
                if (healthBar > shownHealth) {
                        strip.setPixelColor(ledPos, strip.Color(127, 0, 0) );

                        strip.show();
                        delay(50);
                }
        }
}

void power_off_animation() {

        int currUpToLitLED = healthBar * 2 + 4;

        for (int ledPos=currUpToLitLED; ledPos>3; ledPos-=2) {

                strip.setPixelColor(ledPos, 0);

                healthBar--; 

                strip.show();
                delay(50);
        }
       
       healthBar = 0;//actually it became -1, so rectify to 0
}

void decrement_health() {
  
        if (healthBar > 0) {
                int currUpToLitLED = (healthBar-1) * 2 + 4;
                
                strip.setPixelColor(currUpToLitLED, 0);
                
                healthBar--;
                
                strip.show();
                delay(100);
        }
}





