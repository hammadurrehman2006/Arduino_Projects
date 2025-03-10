#define LED_PIN 11
#define PTM_PIN A2

void setup() {
  pinMode(PTM_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ptmVal = analogRead(PTM_PIN);
  int LedVal = ptmVal / 4;
  analogWrite(LED_PIN, LedVal);
  Serial.print("LED Value: ");
  Serial.println(LedVal);
  Serial.print("Potentiometer Value: ");
  Serial.println(ptmVal);
  delay(100); // Add a small delay to avoid flooding the serial monitor
}