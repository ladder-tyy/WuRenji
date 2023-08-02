#include "PS2.h"

#define pressures   true
#define rumble      true

#define MID         128
#define ANGLE       60
#define SPEED       2000

PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

boolean startPress = false;
boolean startOpen = false;

boolean selectPress = false;
boolean selectOpen = false;

int joyLX, joyLY, joyRX, joyRY;
int angLX, angLY, spdRY;

void ledInit(void){
    pinMode(RED,    OUTPUT);
    pinMode(GREEN,  OUTPUT);
    pinMode(BLUE,   OUTPUT);

    digitalWrite(RED,HIGH);
    delay(500);
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,HIGH);
    delay(500);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,HIGH);
    delay(500);
    digitalWrite(BLUE,LOW);
}

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
            if(startOpen == true){
                digitalWrite(GREEN,HIGH);
            }else{digitalWrite(GREEN,LOW);}

            // Serial.printf("Start Key is ");
            // Serial.println(startOpen);

            }
        else if(startPress == true && !ps2x.Button(PSB_START)){startPress = false;}

        if(ps2x.Button(PSB_SELECT) && selectPress == false){
            selectPress = true;
            selectOpen = !selectOpen;
            // Serial.printf("Select Key is ");
            // Serial.println(selectOpen);
            }
        else if(selectPress == true && !ps2x.Button(PSB_SELECT)){selectPress = false;}

        // Read the analog joystick values
        joyLX = ps2x.Analog(PSS_LX) - MID;
        joyLY = -(ps2x.Analog(PSS_LY) - MID);
        joyRX = ps2x.Analog(PSS_RX) - MID;
        joyRY = -(ps2x.Analog(PSS_RY) - MID);

        angLX = map(joyLX, 0, 255, 0, ANGLE);
        angLY = map(joyLY, 0, 255, 0, ANGLE);
        spdRY = map(joyRY, 0, 255, 0, SPEED) - 3;

        // Print the joystick values
        // Serial.print("Left Joystick (X, Y): ");Serial.print(joyLX);Serial.print(", ");Serial.print(joyLY);
        Serial.print("Left JoyAngle (X, Y): ");Serial.print(angLX);Serial.print(", ");Serial.print(angLY);
        Serial.print(" | Right Joystick (X, Y): ");Serial.print(joyRX);Serial.print(", ");Serial.println(spdRY);
    }
    delay(10);
}

