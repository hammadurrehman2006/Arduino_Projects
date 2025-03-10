void setup() {
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int i;
  for (i = 0; i <= 255; i++) {
    analogWrite(11, i);
    Serial.println(i);
  }
  for (i = 255; i >= 0; i--) {  // Change from i<=0 to i>=0
    analogWrite(11, i);
  }
}