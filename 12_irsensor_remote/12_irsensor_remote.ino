#include <IRremote.h>

#define IR_RECV_PIN 5
#define IR_REMOTE_IO 69
#define IR_REMOTE_Stop 70
#define IR_REMOTE_Mute 71
#define IR_REMOTE_Mode 68
#define IR_REMOTE_UTurn 64
#define IR_REMOTE_EQ 67
#define IR_REMOTE_Skip_L 7
#define IR_REMOTE_Skip_R 21
#define IR_REMOTE_Play_Pause 9
#define IR_REMOTE_T_L 22
#define IR_REMOTE_T_R 25
#define IR_REMOTE_0 13
#define IR_REMOTE_1 12
#define IR_REMOTE_2 24
#define IR_REMOTE_3 94
#define IR_REMOTE_4 8
#define IR_REMOTE_5 28
#define IR_REMOTE_6 90
#define IR_REMOTE_7 66
#define IR_REMOTE_8 82
#define IR_REMOTE_9 74

void setup() {
  Serial.begin(115200);  // Start serial communication
  IrReceiver.begin(IR_RECV_PIN);
}

void loop() {
  int command = IrReceiver.decodedIRData.command;
  if (IrReceiver.decode()) {
    //   IrReceiver.resume();
    //   Serial.println(IrReceiver.decodedIRData.command);

    switch (command) {
      case IR_REMOTE_0:
        {
          Serial.println("0 pressed.");
          break;
        }
      case IR_REMOTE_1:
        {
          Serial.println("1 pressed.");
          break;
        }
      case IR_REMOTE_2:
        {
          Serial.println("2 pressed.");
          break;
        }
      case IR_REMOTE_3:
        {
          Serial.println("3 pressed.");
          break;
        }
      case IR_REMOTE_4:
        {
          Serial.println("4 pressed.");
          break;
        }
      case IR_REMOTE_5:
        {
          Serial.println("5 pressed.");
          break;
        }
      case IR_REMOTE_6:
        {
          Serial.println("6 pressed.");
          break;
        }
      case IR_REMOTE_7:
        {
          Serial.println("7 pressed.");
          break;
        }
      case IR_REMOTE_8:
        {
          Serial.println("8 pressed.");
          break;
        }
      case IR_REMOTE_9:
        {
          Serial.println("9 pressed.");
          break;
        }
      case IR_REMOTE_IO:
        {
          Serial.println("IO pressed.");
          break;
        }
      case IR_REMOTE_Stop:
        {
          Serial.println("Stop pressed.");
          break;
        }
      case IR_REMOTE_Mute:
        {
          Serial.println("Mute pressed.");
          break;
        }
      case IR_REMOTE_Mode:
        {
          Serial.println("Mode pressed.");
          break;
        }
      case IR_REMOTE_UTurn:
        {
          Serial.println("U-Turn pressed.");
          break;
        }
      case IR_REMOTE_EQ:
        {
          Serial.println("EQ pressed.");
          break;
        }
      case IR_REMOTE_Skip_L:
        {
          Serial.println("Skip Left pressed.");
          break;
        }
      case IR_REMOTE_Skip_R:
        {
          Serial.println("Skip Right pressed.");
          break;
        }
      case IR_REMOTE_Play_Pause:
        {
          Serial.println("Play/Pause pressed.");
          break;
        }
      case IR_REMOTE_T_L:
        {
          Serial.println("T-Left pressed.");
          break;
        }
      case IR_REMOTE_T_R:
        {
          Serial.println("T-Right pressed.");
          break;
        }
      default:
        {
          Serial.println("Unknown button pressed. ");
          Serial.println(command);
          break;
        }
    }

    IrReceiver.resume();
  }
}
