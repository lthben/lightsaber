void mode_animation() {
        /*
        Perform the animation effects all modes 
         */

        if (digitalRead(animationButtonPin) == HIGH) {

                if (isAnimationButtonPressed == false) {

                        isAnimationButtonPressed = true;

                        switch(mode) {
                                case(REDMODE):
                                do_redmode_animation(); //a one-time trigger operation
                                break;
                                case(ORANGEMODE):
                                isDoOrange = !isDoOrange; //on and off the animation effect
                                break;
                                case(YELLOWMODE):
                                isDoYellow = !isDoYellow; 
                                break;
                                case(GREENMODE):
                                isDoGreen = !isDoGreen;
                                timeInterval = random(2000, 5000);
                                startTime = millis();
                                break;
                        default:
                                break;
                        }
                }  
        }
        else if (digitalRead(animationButtonPin) == LOW) {
                isAnimationButtonPressed = false;
        }

        switch(mode) { //for continuous animation modes instead of one-time triggers
                case(ORANGEMODE):
                if (isDoOrange == true) {
                        do_orangemode_animation();
                }
                break; 
                case(YELLOWMODE):
                if (isDoYellow == true) {
                        do_yellowmode_animation();
                }
                break;
                case(GREENMODE):
                if (isDoGreen == true && millis()-startTime > timeInterval) {
                        do_greenmode_animation();  
                           startTime = millis();
                      timeInterval = random(2000,5000);     
                }
        }
}  

void do_greenmode_animation() {
        /*
        Does a glitching effect, a ring running up and down the blade
         */

        for (int darkLedPos=2; darkLedPos<strip.numPixels()+2; darkLedPos+=2) {

                for (int ledPos=2; ledPos<strip.numPixels(); ledPos+=2) {

                        strip.setPixelColor(ledPos, 0,127,0);

                }
                strip.setPixelColor(darkLedPos, 0); 

                strip.show();
                delay(animationSpeed);         
        }
        
        strip.setPixelColor(strip.numPixels()-1, 0,127,0);
}

void do_yellowmode_animation() {
        /*
        Does a rainbow gradual shimmering effect
         */
        colourIndex++;

        for (int ledPos=2; ledPos<strip.numPixels(); ledPos+=2) {

                strip.setPixelColor(ledPos, Wheel( colourIndex % 255) );
                strip.setBrightness(127);
                strip.show();
        }
}

void do_orangemode_animation() {
        /*
        Does a pulsing light effect
         */
        if (brightLevelDirection == 1) {
                if (brightLevel >= 127) {
                        brightLevelDirection*=-1;
                } 
                else {
                        brightLevel+=5;
                }
        } 
        else if (brightLevelDirection == -1) {
                if (brightLevel <= 50) {
                        brightLevelDirection*=-1;
                } 
                else {
                        brightLevel -= 5;       
                }
        }

        strip.setBrightness(brightLevel);
        strip.show();

        delay(animationSpeed);
}

void do_redmode_animation() {
        /*
        Decrements the health bar by one each time. One bar is 
         equivalent to three LEDs.
         */
        if (healthBar > 0) {

                for (int i=0; i<3; i++) { 

                        //power off three leds in sequence
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
        }
}







