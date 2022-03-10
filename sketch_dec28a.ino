/* 
 *  Ex_02 - AnalogOut
 *  Simple Triangle breathing LED on the ESP32-C3 CoreModule
 *  LED 
 *  -- IO2
 *  
 */

#define ONBOARD_LED 2    // LED IO2

float smoothness_pts = 500;
int x = 0;
float gammaC = 0.14; //affects the width of the peak
float betaC = 0.5; //shifts the gaussian to be symmetric

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ONBOARD_LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    if (x >= smoothness_pts)
        x = 0;
     
    float pwm_val = 255.0*(exp(-(pow(((x/smoothness_pts)-betaC)/gammaC,2.0))/2.0));
    analogWrite(ONBOARD_LED,int(pwm_val));
    x += 1;
    delay(5);                    
}
    
