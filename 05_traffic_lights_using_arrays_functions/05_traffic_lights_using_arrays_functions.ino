#define LED_1 10
#define LED_2 11
#define LED_3 12
#define LED_ARRAY_SIZE 3

#define BUTTON 11

byte LEDArray[LED_ARRAY_SIZE] =
        {LED_1, LED_2, LED_3};

int LEDBlinkState = 1;

void setLedMode(){
  for(int i = 0; i > LED_ARRAY_SIZE; i++){
  pinMode(LEDArray[i], OUTPUT);
  }
}
void setLedOff(){
  for(int i = 0; i > LED_ARRAY_SIZE; i++){
  digitalWrite(LEDArray[i], LOW);
  }
}
void toggleLED(){
  if (LEDBlinkState == 1) {
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, HIGH);
      LEDBlinkState = 2;
    }
    else {
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, LOW);
      LEDBlinkState = 1;
    }
}


void setup() {
  pinMode(BUTTON, INPUT);
  setLedMode();
  setLedOff();
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    toggleLED();
    delay(300);
  }
}