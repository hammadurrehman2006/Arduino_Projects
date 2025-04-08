#include <IRremote.h>
#include <LiquidCrystal.h>

#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9

#define LED_PIN_1 10
#define LED_PIN_2 11
#define LED_PIN_3 12

#define IR_RECV_PIN 5
#define IR_BUTTON_0 13
#define IR_BUTTON_1 12
#define IR_BUTTON_2 24
#define IR_BUTTON_3 94
#define IR_BUTTON_STOP 71

#define LED_ARRAY_SIZE 3

byte LED_ARRAY[LED_ARRAY_SIZE] = {LED_PIN_1, LED_PIN_2, LED_PIN_3};
byte LED_STATE[LED_ARRAY_SIZE] = {LOW, LOW, LOW};

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN,
                  LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

void initLEDModes()
{
  for (int i = 0; i < LED_ARRAY_SIZE; i++) {
    pinMode(LED_ARRAY[i], OUTPUT);
  }
}

void powerOffAllLEDs()
{
  for (int i = 0; i < LED_ARRAY_SIZE; i++) {
    LED_STATE[i] = LOW;
    digitalWrite(LED_ARRAY[i], LOW);
  }
}


void toggleLEDFromIndex(int index)
{
  if (index >= LED_ARRAY_SIZE) {
    return;
  }
  if (LED_STATE[index] == HIGH) {
    LED_STATE[index] = LOW;
  }
  else {
    LED_STATE[index] = HIGH;
  }
  digitalWrite(LED_ARRAY[index], LED_STATE[index]);
}

void printCommandOnLCD(long command)
{
  lcd.setCursor(0, 0);
  lcd.print("        ");
  lcd.setCursor(0, 0);
  lcd.print(command);
}


void printActionOnLCD(String action)
{
  lcd.setCursor(0, 1);
  lcd.print(action);
}

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECV_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.command != 0 && IrReceiver.decodedIRData.protocol != UNKNOWN) { 
      int command = IrReceiver.decodedIRData.command;
      IrReceiver.resume();

      switch (command) {
        case IR_BUTTON_0:
          powerOffAllLEDs();
          printCommandOnLCD(command);
          printActionOnLCD("Power off LEDs.");
          break;

        case IR_BUTTON_1:
          toggleLEDFromIndex(0);
          printCommandOnLCD(command);
          printActionOnLCD("Toggle LED 1.");
          break;

        case IR_BUTTON_2:
          toggleLEDFromIndex(1);
          printCommandOnLCD(command);
          printActionOnLCD("Toggle LED 2.");
          break;

        case IR_BUTTON_3:
          toggleLEDFromIndex(2);
          printCommandOnLCD(command);
          printActionOnLCD("Toggle LED 3.");
          break;

        case IR_BUTTON_STOP:
          lcd.clear();
          break;

        default:
          printCommandOnLCD(command);
          printActionOnLCD("Not recognized.");
          Serial.println(command);
          break;
      }
    }
    IrReceiver.resume();
  }
}
