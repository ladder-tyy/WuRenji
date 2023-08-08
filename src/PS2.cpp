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


int targetRoll, targetPitch, targetYaw;
int targetPower;

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
    int joyLX, joyLY, joyRX, joyRY;
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

        targetRoll = map(joyLX, -127, 128, -ANGLE, ANGLE) + 1;
        targetPitch = map(joyLY, -127, 128, -ANGLE, ANGLE) + 1;
        targetYaw = map(joyRX, -127, 128, -ANGLE, ANGLE) + 1;
        targetPower = map(joyRY, -127, 128, -SPEED, SPEED) + 1;

        // Print the joystick values
        // Serial.print("target(Roll, Pitch): ");Serial.print(targetRoll);Serial.print(", ");Serial.print(targetPitch);
        // Serial.print(" | target (Yaw, Power): ");Serial.print(targetYaw);Serial.print(", ");Serial.println(targetPower);
    }
    delay(10);
}

