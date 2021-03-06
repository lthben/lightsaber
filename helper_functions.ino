uint32_t Wheel(byte WheelPos) {
        /*
        Helper function for colour conversion. 
        Input a value 0 to 255 to get a color value.
         The colours are a transition r - g - b - back to r.
         Source: Adafruit NeoPixel library Strandtest example
         */

        WheelPos = 255 - WheelPos;
        if(WheelPos < 85) {
                return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
        } 
        else if(WheelPos < 170) {
                WheelPos -= 85;
                return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
        } 
        else {
                WheelPos -= 170;
                return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        }
}
