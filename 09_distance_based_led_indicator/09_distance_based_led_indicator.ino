#define ECHO_PIN 3
#define TRIGGER_PIN 4
#define LED_1 10
#define LED_2 11
#define LED_3 12

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 100;

volatile unsigned long pulseTimeIn;
volatile unsigned long pulseTimeOut;

volatile bool newDistAvailable = false;

void triggerUltrasonicSensor() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance() {
  double durationMicros = pulseTimeOut - pulseTimeIn;
  double distance = durationMicros / 58.0;  // cm (148.0: inches)
  return distance;
}

void echoPinInterrupt() {
  if (digitalRead(ECHO_PIN) == HIGH) {  // start measuring
    pulseTimeIn = micros();
  } else {  // stop measuring
    pulseTimeOut = micros();
    newDistAvailable = true;
  }
}

void powerLedFromDist(double distance) {
  if (distance >= 80) {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, HIGH);
  } else if (distance >= 20) {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, LOW);
  } else {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                  echoPinInterrupt,
                  CHANGE);
}

void loop() {
  unsigned long timeNow = millis();

  if (timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay) {
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
  }
  if (newDistAvailable) {
    newDistAvailable = false;
    double distance = getUltrasonicDistance();
    Serial.println(distance);
    powerLedFromDist(distance);
  }
}
