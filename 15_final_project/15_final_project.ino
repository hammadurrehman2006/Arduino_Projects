#include <LiquidCrystal.h>
#include <IRremote.h>
#include <EEPROM.h>

#define IR_RECEIVE_PIN 5

#define IR_REMOTE_OFF 69
#define IR_REMOTE_EQ 67
#define IR_REMOTE_UP 7
#define IR_REMOTE_DOWN 21
#define IR_REMOTE_PLAY 9

#define ECHO_PIN 3
#define TRIGGER_PIN 4

#define LIGHT_LED_PIN 10
#define WARNING_LED_PIN 11
#define ERROR_LED_PIN 12

#define PHOTORESISTOR_PIN A0 

#define BUTTON_PIN 2

#define LOCK_DIST 10.0
#define WARNING_DISTANCE 50.0

#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9

#define DISTANCE_UNIT_CM 0
#define DISTANCE_UNIT_IN 1

#define EEPROM_ADDRESS_DISTANCE_UNIT 50

#define LCD_MODE_DISTANCE 0
#define LCD_MODE_SETTING 1

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// ultrasonic
unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;

volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile bool newDistanceAvailable = false;

double previousDistance = 400.0;

// warning LED
unsigned long lastTimeWarningLEDBlinked = millis();
unsigned long warningLEDDelay = 500;
byte warningLEDState = LOW;

// error LED
unsigned long lastTimeErrorLEDBlinked = millis();
unsigned long errorLEDDelay = 500;
byte errorLEDState = LOW;

unsigned long lastTimeReadLuminosity = millis();
unsigned long readLuminosityDelay = 100;

unsigned long lastTimeButtonPressed = millis();
unsigned long buttonDebounceDelay = 1000;
byte buttonState;

bool isLocked = false;

int distanceUnit = DISTANCE_UNIT_CM;

int lcdMode = LCD_MODE_DISTANCE;


void triggerUltrasonicSensor()
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance()
{
  double durationMicros = pulseInTimeEnd - pulseInTimeBegin;
  double distance = durationMicros / 58.0;
  if (distance > 400.0) {
    return previousDistance;
  }
  distance = previousDistance * 0.6 + distance * 0.4;
  previousDistance = distance;
  return distance;
}

void echoPinInterrupt()
{
  if (digitalRead(ECHO_PIN) == HIGH) { // pulse started
    pulseInTimeBegin = micros();
  }
  else { // pulse stoped
    pulseInTimeEnd = micros();
    newDistanceAvailable = true;
  }
}

void toggleWarningLED()
{
  warningLEDState = (warningLEDState == HIGH) ? LOW : HIGH;
  digitalWrite(WARNING_LED_PIN, warningLEDState);
}

void toggleErrorLED()
{
  errorLEDState = (errorLEDState == HIGH) ? LOW : HIGH;
  digitalWrite(ERROR_LED_PIN, errorLEDState);
}

void setWarningLEDBlinkRateFromDistance(double distance)
{
  // 0 .. 400 cm -> 0 .. 1600 ms
  warningLEDDelay = distance * 4;
  Serial.println(warningLEDDelay);
}

void lock(){
if(!isLocked){
  isLocked = true;
  errorLEDState = LOW;
  digitalWrite(ERROR_LED_PIN, errorLEDState);
}
}
void unlock(){
if(isLocked){
  isLocked = false;
  warningLEDState = LOW;
  errorLEDState = LOW;
}
}

void printDistanceOnLCD(double distance)
{
  if(isLocked){
    lcd.setCursor(0,0);
    lcd.print("!! Obstacle !! ");
    lcd.setCursor(0, 1);
    lcd.print("Press to unlock.");
    }
  else{
    lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    if (distanceUnit == DISTANCE_UNIT_CM) {
      lcd.print(distance);
      lcd.print(" cm");
    }
    else {
      lcd.print(distance * 0.393701);
      lcd.print(" in");
    }
    lcd.setCursor(0, 1);
    if (distance > LOCK_DIST) {
      lcd.print("No Obstacle.");
    }
    else {
      lcd.print("!! Warning !!  ");
    }


  }
}

void toggleDistanceUnit(){
  if (distanceUnit == DISTANCE_UNIT_CM) {
    distanceUnit = DISTANCE_UNIT_IN;
  }
  else {
    distanceUnit = DISTANCE_UNIT_CM;
  }
  EEPROM.write(EEPROM_ADDRESS_DISTANCE_UNIT, distanceUnit);
}

void toggleLCDScreen(){
  switch (lcdMode){
    case LCD_MODE_DISTANCE: {
      lcdMode = LCD_MODE_DISTANCE;
      break;
    }
    case LCD_MODE_SETTING: {
      lcdMode = LCD_MODE_SETTING;
      break;
    }
    default: {
      lcdMode = LCD_MODE_DISTANCE;
    }
  }
  lcd.clear();
  if (lcdMode == LCD_MODE_SETTING) {
    lcd.setCursor(0, 0);
    lcd.print("Press on OFF to  ");
    lcd.setCursor(0, 1);
    lcd.print("reset settings.  ");
  }
}

void resetSettingsToDefault() {
  if(lcdMode == LCD_MODE_SETTING){
    distanceUnit = DISTANCE_UNIT_CM;
    EEPROM.write(EEPROM_ADDRESS_DISTANCE_UNIT, distanceUnit);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Setting have");
    lcd.setCursor(0, 1);
    lcd.print("been reset. ");
  }
}

void handleIRCommand(long command){
  switch (command) {
    case IR_REMOTE_OFF:
      {
        resetSettingsToDefault();
        break;
      }
    case IR_REMOTE_EQ:
      {
        toggleDistanceUnit();
        break;
      }
    case IR_REMOTE_UP:
      {
        toggleLCDScreen();
        break;
      }
    case IR_REMOTE_DOWN:
      {
        toggleLCDScreen();
        break;
      }
    case IR_REMOTE_PLAY:
      {
        unlock();
        break;
      }
    default:
      {

      }
  }
}

void setLightLEDFromLuminosity(int luminosity) {
  byte bri
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(WARNING_LED_PIN, OUTPUT);
  pinMode(ERROR_LED_PIN, OUTPUT);
  pinMode(LIGHT_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

buttonState = digitalRead(BUTTON_PIN);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                  echoPinInterrupt,
                  CHANGE);
  distance = EEPROM.read(EEPROM_ADDRESS_DISTANCE_UNIT);
  if (distanceUnit == 255){
    distanceUnit = DISTANCE_UNIT_CM;
  }
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long timeNow = millis();

  if (timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay) {
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
  }

  if(isLocked){
    if (timeNow - lastTimeErrorLEDBlinked > errorLEDDelay) {
      lastTimeErrorLEDBlinked += errorLEDDelay;
      toggleErrorLED();
      toggleWarningLED();
    }
   if (timeNow - lastTimeButtonPressed > buttonDebounceDelay) {
      byte newButtonState = digitalRead(BUTTON_PIN);
      if (newButtonState != buttonState) {
        buttonState = newButtonState;
        lastTimeButtonPressed = timeNow;
        if (buttonState == LOW) {
          unlock();
        }
      }
    }
  }
  else{   
    if (timeNow - lastTimeWarningLEDBlinked > warningLEDDelay) {
      lastTimeWarningLEDBlinked += warningLEDDelay;
      toggleWarningLED();
    }
    if (IrReceiver.decode()) {
      IrReceiver.resume();
      long command = IrReceiver.decodedIRData.command;
      Serial.println(command);
      handleIRCommand(command);
    }
  }


  if (newDistanceAvailable) {
    newDistanceAvailable = false;
    double distance = getUltrasonicDistance();
    setWarningLEDBlinkRateFromDistance(distance);
    if(distance > LOCK_DIST) {
      lock();
    }
    
    // Serial.println(distance);
  }
  if (timeNow - lastTimeReadLuminosity > readLuminosityDelay){
    lastTimeReadLuminosity =+ readLuminosityDelay;
    int luminosity = analogRead(PHOTORESISTOR_PIN);
  }
}
