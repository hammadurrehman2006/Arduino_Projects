// Setup function runs once at the beginning of the program
void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Set digital pin 13 as an output
  pinMode(13, OUTPUT);
}

// Loop function runs repeatedly after setup
void loop() {
  // Turn on the LED connected to digital pin 13
  digitalWrite(13, HIGH);
  
  // Wait for 5 seconds (5000 milliseconds)
  delay(5000);
  
  // Print "Hello Uno" to the serial monitor
  Serial.println("Hello Uno");
  
  // Turn off the LED connected to digital pin 13
  digitalWrite(13, LOW);
  
  // Wait for 2 seconds (2000 milliseconds)
  delay(2000);
}