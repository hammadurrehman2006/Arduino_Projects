#include <LiquidCrystal.h>

#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9
#define ECHO_PIN 3
#define TRIGGER_PIN 4

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 100;

volatile unsigned long pulseTimeIn;
volatile unsigned long pulseTimeOut;
volatile bool newDistAvailable = false;

double prevDistance = 400.0;

void triggerUltrasonicSensor() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance() {
  double durationMicros = pulseTimeOut - pulseTimeIn;
  double distance = durationMicros / 58.0;
  if(distance > 400.0){
    return prevDistance;
  }
  distance = prevDistance * 0.5 + distance * 0.5;
  prevDistance = distance;
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

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN,
                  LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

int cursorLine = 0;

void printUserTextOnDisplay(double distance){
   lcd.setCursor(0, 0);
   lcd.print("Distance:");
   lcd.setCursor(0, 1);
   lcd.print(distance);
   lcd.setCursor(6, 1);
   lcd.print("cm");

}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  lcd.begin(16, 2);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
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
    printUserTextOnDisplay(distance);
  }
}