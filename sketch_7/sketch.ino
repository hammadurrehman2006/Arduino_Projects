# define LED_PIN 12

unsigned long prev_time = millis();
unsigned long blinkDelay = 500;
int LED_STATE = LOW;
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  pinMode(LED_PIN,OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    int data = Serial.parseInt();
    if((data >= 100) && (data <= 4000)){
      blinkDelay = data;
    }
  }
  unsigned long timeNow = millis();
  if (timeNow - prev_time > blinkDelay){
    if(LED_STATE == LOW){
      LED_STATE = HIGH;
  }
    else{
      LED_STATE = LOW;
  }
    digitalWrite(LED_PIN,LED_STATE);
    prev_time += blinkDelay;
  }
  
}
