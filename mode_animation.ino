void mode_animation() {
        /*
        Perform the animation effects all modes 
         */

        if (digitalRead(ANIMATIONBUTTONPIN) == HIGH) {

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
                                timeInterval = random(LOWERTIMEBOUND, UPPERTIMEBOUND);
                                startTime = millis();
                                break;
                                case(BLUEMODE):
                                isDoBlue = !isDoBlue;
                                if (isDoBlue == true) {
                                        isBlueOnInitialised = false; 
                                }
                                break;
                                case(VIOLETMODE):
                                isDoViolet = !isDoViolet;
                                break;
                        default:
                                break;
                        }
                }  
        }
        else if (digitalRead(ANIMATIONBUTTONPIN) == LOW) {
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
                        timeInterval = random(LOWERTIMEBOUND, UPPERTIMEBOUND);     
                        whichDirection = random(0, 2); //returns either 0 or 1
                }
                case(BLUEMODE):
                if (isDoBlue == true) {
                        do_bluemode_animation();
                }
                break;
                case(VIOLETMODE):
                if (isDoViolet == true) {
                        do_violetmode_animation();
                }
                break;
        }
}  

void do_violetmode_animation() {
        /*
        Does a twinkle star shimmering light animation
         */
        for (int ledPos=2; ledPos<strip.numPixels(); ledPos+=2) {
                brightLevel = random(25, 128);
                strip.setPixelColor(ledPos, brightLevel, 0, brightLevel);       
        }
        strip.show();
        delay(ANIMATIONSPEED*2);
}

void do_bluemode_animation() {
        /*
        Does a running theatre light animation.
         Code adapted from NeoPixel library example.
         */
        //turn all off before starting the blue animation
        if (isBlueOnInitialised == false) {
                for (int i=2; i<strip.numPixels(); i+=2) {
                        strip.setPixelColor(i, 0);
                }
                strip.show();

                isBlueOnInitialised = true;
        }

        //running lights effect
        for (int q=0; q < 3; q++) {
                for (int i=0; i < strip.numPixels(); i=i+3) {
                        strip.setPixelColor(i+q, strip.Color(0, 0, 127));    //turn every third pixel on
                }
                strip.show();

                delay(ANIMATIONSPEED*5);

                for (int i=0; i < strip.numPixels(); i=i+3) {
                        strip.setPixelColor(i+q, 0);        //turn every third pixel off
                }
        }
}

void do_greenmode_animation() {
        /*
        Does a glitching effect, a ring running up and down the blade
         */
        if (whichDirection == 0) {
                for (int darkLedPos=2; darkLedPos<strip.numPixels()+2; darkLedPos+=2) {

                        for (int ledPos=2; ledPos<strip.numPixels(); ledPos+=2) {

                                strip.setPixelColor(ledPos, 0,127,0);

                        }
                        strip.setPixelColor(darkLedPos, 0); 

                        strip.show();
                        delay(ANIMATIONSPEED);         
                }

                strip.setPixelColor(strip.numPixels()-1, 0,127,0);
        } 
        else if (whichDirection == 1) {
                for (int darkLedPos=36; darkLedPos>1; darkLedPos-=2) {

                        for (int ledPos=2; ledPos<strip.numPixels(); ledPos+=2) {

                                strip.setPixelColor(ledPos, 0,127,0);

                        }
                        strip.setPixelColor(darkLedPos, 0); 

                        strip.show();
                        delay(ANIMATIONSPEED);         
                }
        }
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
                delay(2);
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

        delay(ANIMATIONSPEED);
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









