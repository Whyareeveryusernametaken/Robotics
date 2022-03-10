

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define SR04_I2CADDR 0x57
#define OLED_I2CAADR 0x3C

// i2c PCF8574(A) Port expander
// PCF8574  -> 0 0 1 0  0 A2 A1 A0    0 0 1 1
// PCF8574A -> 0 0 1 1  1 A2 A1 A0    1 0 1 1
#define PEXP_I2CADDR 0x23

// i2c Slave Co-processor - On the Core-Module
#define I2CADDR 0x13
// i2c Slave Co-processor - On the Robot MainBoard
#define I2CADDR_B 0x12

#define I2C_SDA 19
#define I2C_SCL 18
#define LED 2
#define IR_RECV 4
#define NEO_PIXEL 5
#define LED_COUNT 3

SSD1306AsciiWire oled;

byte attinySlaveRcvArray[3];
byte attinySlaveArrayBoard[3];


// Control the LED state of the LED on the
// Robotic MainBoard.
// Input:
//        outputState - HIGH/LOW
// Return:
//        0 - Sucess
//        1 - i2C write failure

int setBoardLED(uint8_t outputState) {
    attinySlaveArrayBoard[0] = 0x02;  // Command 0x02
    attinySlaveArrayBoard[1] = outputState? 0x01:0x00;  // Param1 - LED State
    attinySlaveArrayBoard[2] = 0x00;  // Param2 - Dummy in this case
    delay(10);
    Wire.beginTransmission(I2CADDR);
    Wire.write(attinySlaveArrayBoard, 3); // Sends 3 bytes i2c to Co-processor.
    if (Wire.endTransmission () == 0) { // Receive 0 = success (ACK response) 
        Serial.println("i2c Write to 0x12 Sucessfull");
        return 0;
    }
    else {
        Serial.println("i2c Write Failed");
        return 1;
    }
}

// the setup function runs once when you press reset or power the board
void setup() {

    Wire.begin(I2C_SDA, I2C_SCL);    
    oled.begin(&Adafruit128x64, OLED_I2CAADR); 
    
    pinMode(LED, OUTPUT);
    delay(2000);
    
    Serial.begin(115200);
    
    attinySlaveArrayBoard[0] = 2;
    attinySlaveArrayBoard[1] = 1;
    attinySlaveArrayBoard[2] = 1;
    
    oled.setFont(Adafruit5x7);
    oled.clear();
    oled.println("MainBoard Co-Processor");
    oled.println("IPC (Interprocess Comm)");

}

// the loop function runs over and over again forever
void loop() {
  
    oled.clear();
    oled.println("-LED On (1s)-");
    setBoardLED(HIGH);
    delay(1000);

    oled.clear();
    oled.println("-LED Off (1s)-");
    setBoardLED(LOW);
    delay(1000);

}
                    
                
