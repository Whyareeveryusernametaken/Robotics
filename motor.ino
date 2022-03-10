int setBoardLED(uint8_t outputState) {
    attinySlaveArrayBoard[0] = 0x02;  // Command 0x02
    attinySlaveArrayBoard[1] = outputState? 0x01:0x00;  // Param1 - LED State
    attinySlaveArrayBoard[2] = 0x00;  // Param2 - Dummy in this case
    delay(10);
    Wire.beginTransmission(I2CADDR_B);
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

// Control the Stepper on the
// Robotic MainBoard.
// Input:
//        motorState - HIGH/LOW
// Return:
//        0 - Sucess
//        1 - i2C write failure

int setMotorRunning(uint8_t motorState) {
    attinySlaveArrayBoard[0] = 0x01;  // Command 0x01
    attinySlaveArrayBoard[1] = motorState? 0x01:0x00;  // Param1 - Stop/Run
    attinySlaveArrayBoard[2] = 0x00;  // Param2 - Dummy in this case
    delay(10);
    Wire.beginTransmission(I2CADDR_B);
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

// Control the Stepper on the
// Robotic MainBoard.
// Input:
//        motor - 0 (Motor A)
//                1 (Motor B)
//        direction - 0 -> Stop 
//                    1 -> Clockwise
//                    2 -> Counter-Clockwise
// Return:
//        0 - Sucess
//        1 - i2C write failure

#define STOP 0
#define CW 1
#define CCW 2

int setDirection(int motor, byte direction) {
    attinySlaveArrayBoard[0] = motor == 0 ? 0x13 : 0x23;  // Command 0x13 or 0x23
    attinySlaveArrayBoard[1] = (direction >= 0) && (direction <= 2) ? direction: 0;  
                                                          // Param1 - Stop/CW/CCW
    attinySlaveArrayBoard[2] = 0x00;  // Param2 - Dummy in this case
    delay(10);
    Wire.beginTransmission(I2CADDR_B);
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
// Control the Stepper on the
// Robotic MainBoard.
// Input:
//        motor - 0 (motor A)
//        motor - 1 (motor B)
//        RPM - HIGH/LOW
// Return:
//        0 - Sucess
//      1 - i2C write failure


#define L 0
#define H 1

int setRPM(int motor, float RPM) {
    attinySlaveArrayBoard[0] = motor ==0? 0x14: 0x24;  // Command 0x14 or 0x24
    attinySlaveArrayBoard[1] = RPM == 0? 6000 : 24000  ;  // Param1 - rpm(L) 
    attinySlaveArrayBoard[2] = 0x00  ;  // param2 - dummy
    delay(10);
    Wire.beginTransmission(I2CADDR_B);
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

    oled.clear();
    oled.println("-Motor Start FW (5s)-");
    setDirection(0, CCW);
    setDirection(1, CW);
    setRPM(0,L);
    setRPM(1,L);
    setMotorRunning(HIGH);
    delay(5000);

    oled.clear();
    oled.println("-Motor Stop (3s)-");
    setMotorRunning(LOW);
    delay(3000);

    oled.clear();
    oled.println("-Motor Start CCW- (5s)");
    setDirection(0, CCW);
    setDirection(1, CCW);
    setMotorRunning(HIGH);
    delay(5000);

    oled.clear();
    oled.println("-Motor Stop (1s)-");
    setMotorRunning(LOW);
    delay(1000);
    oled.clear();

    oled.println("-Motor Start CW- (5s)");
    setDirection(0, CW);
    setDirection(1, CW);
    setMotorRunning(HIGH);
    delay(5000);

    oled.clear();
    oled.println("-Motor Stop (1s)-");
    setMotorRunning(LOW);
    delay(1000);

    oled.println("-Motor Start REW- (5s)");
    oled.println("-RPM High- (5s)");
    setDirection(0, CW);
    setDirection(1, CCW);
    setMotorRunning(HIGH);
    setRPM(0,H);
    setRPM(1,H);
    delay(10000);
    
    oled.clear();
    oled.println("-Motor Stop (1s)-");
    setMotorRunning(LOW);
    delay(1000);
    
    oled.println("-RPM Low- (5s)");
    setDirection(0, CW);
    setDirection(1, CCW);
    setMotorRunning(HIGH);
    setRPM(0,L);
    setRPM(1,L);
    delay(10000);

    oled.clear();
    oled.println("-Motor Stop (1s)-");
    setMotorRunning(LOW);
    delay(1000);
}
