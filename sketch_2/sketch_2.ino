// Setup function runs once at the beginning
void setup() {
  // Set pin 11 as an output
  pinMode(11, OUTPUT);
  
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
}

// Loop function runs repeatedly after setup
void loop() {
  int i; // Initialize a variable to store the brightness value
  
  // Fade in: increase brightness from 0 to 255
  for (i = 0; i <= 255; i++) {
    // Set the brightness of pin 11 using PWM (analogWrite)
    analogWrite(11, i);
    
    // Print the current brightness value to the serial monitor
    Serial.println(i);
  }
  
  // Fade out: decrease brightness from 255 to 0
  for (i = 255; i >= 0; i--) {
    // Set the brightness of pin 11 using PWM (analogWrite)
    analogWrite(11, i);
  }
}