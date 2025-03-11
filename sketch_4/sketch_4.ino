# define Led1 3
# define Led2 5
# define Led3 9
void setup() {
  pinMode(Led1,OUTPUT);
  pinMode(Led2,OUTPUT);
  pinMode(Led3,OUTPUT);

  digitalWrite(Led1,LOW);
  digitalWrite(Led2,LOW);
  digitalWrite(Led3,LOW);

}

void loop() {
    digitalWrite(Led1,HIGH);
    digitalWrite(Led2,LOW);
    digitalWrite(Led3,LOW);
    delay(4000);
    digitalWrite(Led1,LOW);
    digitalWrite(Led2,HIGH);
    digitalWrite(Led3,LOW);
    delay(2000);
    digitalWrite(Led1,LOW);
    digitalWrite(Led2,LOW);
    digitalWrite(Led3,HIGH);
    delay(4000);

}
