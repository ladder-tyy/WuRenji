#include "main.h"

void setup() {
    Serial.begin(115200);
    pwmInit();
    // ps2Init();
    imuInit();
    taskInit();
    ledInit();
}

void loop() {
}
