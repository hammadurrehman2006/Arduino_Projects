#define ECHO_PIN 3
#define TRIGGER_PIN 4

#define WARNING_LED_PIN 11

// ultrasonic
unsigned long lastUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;

unsigned long pulseInTimeBegin;
unsigned long pulseInTimeEnd;
bool newDistAvailable = false;

double prevDistance = 400.0;

// warning led 
unsigned long int lastTimeWLedBlink = millis();
unsigned long warningLedDelay = 500;
byte warningLedState = LOW;

void triggerSensor() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}
void echoPinInterrupt(){
  if(digitalRead(ECHO_PIN) == HIGH){
    pulseInTimeBegin = micros();
  }
  else{
    pulseInTimeEnd = micros();
    newDistAvailable = true;
  }
}

double getUltrasonicDist(){
  double distance = (pulseInTimeEnd - pulseInTimeBegin) / 58.0;
  if(distance > 400.0){
    return prevDistance;
  }
  distance = prevDistance * 0.6 + distance * 0.4;
  prevDistance = distance;
  return distance;
}


void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(WARNING_LED_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoPinInterrupt, CHANGE);
}

void loop() {
  unsigned long timeNow = millis();
  if (timeNow - lastUltrasonicTrigger > ultrasonicTriggerDelay) {
    lastUltrasonicTrigger += ultrasonicTriggerDelay;
  }
  if (newDistAvailable) {
    newDistAvailable = false;
    double distance = getUltrasonicDist();
    Serial.print("Distance: ");
    Serial.println(distance);
  }
    
}
