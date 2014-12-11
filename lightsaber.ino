const int switchPin = 11;
const int powerButtonPin = 12;
const int healthButtonPin = 13;

boolean isPowerButtonState, isPowerButtonPressed, isPowerOn;

void setup() {
        pinMode(switchPin, INPUT);
        pinMode(powerButtonPin, INPUT);
        pinMode(healthButtonPin, INPUT);
        Serial.begin(9600);
}

void loop() {
        if (digitalRead(switchPin) == HIGH) { //passive power switch 

                if (digitalRead(powerButtonPin) == HIGH){
                        if (isPowerButtonPressed == false){
                                isPowerButtonPressed = true;
                                if  (isPowerOn == false) {
                                        isPowerOn = true;
                                        Serial.println("power on");
                                } 
                                else(isPowerOn == true) {
                                        isPowerOn = false;
                                        Serial.println("power off");
                                }
                        }
                }   

        }
}




