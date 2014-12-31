void power_animation() {
        /*
        Power on animation for all modes
         */
        if (digitalRead(powerButtonPin) == HIGH){ 

                if (isPowerButtonPressed == false){

                        isPowerButtonPressed = true;

                        if  (healthBar == 0) {

                                power_on_animation();
                        } 
                        else if (healthBar > 0) {

                                power_off_animation();
                        }
                }
        }   
        else if (digitalRead(powerButtonPin) == LOW) {
                isPowerButtonPressed = false;       
        }
}

void power_on_animation() {
        /*
        Helper function for power_animation()
         */
        healthBar = 18;

        strip.setBrightness(127);

        for (int ledPos=2; ledPos<37; ledPos+=2) {

                switch(mode) {
                        case(REDMODE):
                        strip.setPixelColor(ledPos, strip.Color(127, 0, 0) );
                        break;
                        case(ORANGEMODE):
                        strip.setPixelColor(ledPos, strip.Color(127, 63, 0) );
                        break;
                        case(YELLOWMODE):
                        strip.setPixelColor(ledPos, strip.Color(127, 127, 0) );
                        break;
                        case(GREENMODE):
                        strip.setPixelColor(ledPos, strip.Color(0, 127, 0) );
                        break;
                        case(BLUEMODE):
                        strip.setPixelColor(ledPos, strip.Color(0, 0, 127) );
                        break;
                        case(VIOLETMODE):
                        strip.setPixelColor(ledPos, strip.Color(127, 0, 127) );
                        break;
                }

                strip.show();
                delay(animationSpeed); 
        }
}

void power_off_animation() {
        /*
        Helper function for power_animation
         */
        int currUpToLitLED = healthBar * 2 + 2;

        for (int ledPos=currUpToLitLED; ledPos>1; ledPos-=2) {

                strip.setPixelColor(ledPos, 0);

                healthBar--; 

                strip.show();
                delay(animationSpeed);
        }

        healthBar = 0;//actually it became -1, so rectify to 0

                // cycle to the next mode after each power down animation 
        if (mode == VIOLETMODE){
                mode = REDMODE;
        } 
        else {
                mode++;   
        }
}

