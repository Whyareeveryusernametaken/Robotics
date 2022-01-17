String rcvString = "";
int height = 0;
int weight = 0;
int bmi = 0;


void setup() {
   Serial.begin(115200); //set up serial library baud rate to 115200
   delay(1000);
   Serial.println("Enter weight to check BMI to ensure healthiness");
}

void loop() {
   if(Serial.available())
      Serial.print("Your weight is "); 
      rcvString = Serial.readString();
      weight = rcvString.toInt(); 
      
      Serial.print("Your height is "); 
      rcvString = Serial.readString();
      height = rcvString.toInt(); 
      
      bmi = weight/(height * height);
      
      Serial.print("You are");
      
      if (bmi < 16) {
        Serial.println("Severely Undeweight");
      }
      else if (16 < bmi < 18.4 ) {
        Serial.println("Underweight");
      }
      else if (18.5 < bmi < 24.9 ) {
        Serial.println("Normal");
      }
      else if (25 < bmi < 29.9 ) {
        Serial.println("Overweight");
   
      }    
}
}
