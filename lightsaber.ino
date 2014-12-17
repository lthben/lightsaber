/*
Author:      Benjamin Low (benjamin.low@digimagic.com.sg)
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

Adafruit_NeoPixel strip = Adafruit_NeoPixel(37, PIN, NEO_GRB + NEO_KHZ800);

const int powerButtonPin = 9; //for power on and off animations
const int healthButtonPin = 10; //to reduce the health

boolean isPowerButtonPressed; //prevent state switching when button is held down
boolean isHealthButtonPressed; //prevent state switching when button is held down

int healthBar = 0; //tracks amount of health

void setup() {
        pinMode(powerButtonPin, INPUT);
        pinMode(healthButtonPin, INPUT);
        Serial.begin(9600);
        strip.begin();
        strip.show();
}

void loop() {

        //active power button
        if (digitalRead(powerButtonPin) == HIGH){ 

                if (isPowerButtonPressed == false){

                        isPowerButtonPressed = true;

                        if  (healthBar == 0) {

                                power_on_animation();

                                Serial.println("power on\n");
                        } 
                        else if (healthBar > 0) {

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

        for (int ledPos=2; ledPos<37; ledPos+=2) {
                int shownHealth = (ledPos - 2)/2;      
                if (healthBar > shownHealth) {
                        strip.setPixelColor(ledPos, strip.Color(127, 0, 0) );

                        strip.show();
                        delay(25);
                }
        }
}

void power_off_animation() {

        int currUpToLitLED = healthBar * 2 + 2;

        for (int ledPos=currUpToLitLED; ledPos>1; ledPos-=2) {

                strip.setPixelColor(ledPos, 0);

                healthBar--; 

                strip.show();
                delay(25);
        }

        healthBar = 0;//actually it became -1, so rectify to 0
}

void decrement_health() {

        /*
        if (healthBar > 0) {
         int currUpToLitLED = (healthBar-1) * 2 + 4;
         
         strip.setPixelColor(currUpToLitLED, 0);
         
         healthBar--;
         
         strip.show();
         delay(500);
         }
         */


        if (healthBar > 0) {

                decrement_by_one();
                decrement_by_one();
                decrement_by_one();

        }

}

void decrement_by_one() {
        int currUpToLitLED = (healthBar-1) * 2 + 2;

        int brightness = 127;

        while (brightness > 0){

                strip.setPixelColor(currUpToLitLED, strip.Color(brightness, 0, 0));              

                brightness--;

                strip.show(); 
        }

        strip.setPixelColor(currUpToLitLED, 0);

        strip.show();  

        healthBar --;
}










