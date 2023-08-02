#include "PS2.h"

#define pressures   true
#define rumble      true

PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

boolean startPress = false;
boolean startOpen = false;

boolean selectPress = false;
boolean selectOpen = false;

void ps2Init(void){
    // Attach the PS2 controller to the pins
    int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
      if (error == 0) {
        Serial.println("PS2 Controller Connected!");
        Serial.println("Ready to read input.");
      } else {
      Serial.println("No controller found, check wiring.");
      while (true) {
        delay(1000);
      }
  }
}

void ps2Deal(void *pvParameters){
    while(1){
        // Read the PS2 controller input
        ps2x.read_gamepad(false, 0);

        // Check if any button is pressed

        if(ps2x.Button(PSB_START) && startPress == false){
            startPress = true;
            startOpen = !startOpen;
            Serial.printf("Start Key is ");
            Serial.println(startOpen);
            }
        else if(startPress == true && !ps2x.Button(PSB_START)){startPress = false;}

        if(ps2x.Button(PSB_SELECT) && selectPress == false){
            selectPress = true;
            selectOpen = !selectOpen;
            Serial.printf("Select Key is ");
            Serial.println(selectOpen);
            }
        else if(selectPress == true && !ps2x.Button(PSB_SELECT)){selectPress = false;}





        // Read the analog joystick values
        int joyX = ps2x.Analog(PSS_LX);
        int joyY = ps2x.Analog(PSS_LY);
        int joyRX = ps2x.Analog(PSS_RX);
        int joyRY = ps2x.Analog(PSS_RY);

        // Print the joystick values
        Serial.print("Left Joystick (X, Y): ");
        Serial.print(joyX);
        Serial.print(", ");
        Serial.print(joyY);
        Serial.print(" | Right Joystick (X, Y): ");
        Serial.print(joyRX);
        Serial.print(", ");
        Serial.println(joyRY);
    }
    delay(10);
}