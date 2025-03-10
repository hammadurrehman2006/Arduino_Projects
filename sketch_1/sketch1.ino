void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(5000);
  Serial.println("Hello Uno");
  digitalWrite(13, LOW);
  delay(2000);
}