#include "main.h"

void setup() {
    Serial.begin(115200);
    ps2Init();
    // imuInit();
    taskInit();
}

void loop() {

}
