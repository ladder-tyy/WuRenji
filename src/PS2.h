#include <PS2X_lib.h>

#ifndef __PS2_H__
#define __PS2_H__

#define PS2_CMD 23
#define PS2_DAT 19
#define PS2_CLK 18
#define PS2_SEL  5

#define RED     17
#define GREEN   16
#define BLUE     4

extern int targetRoll, targetPitch, targetYaw;
extern int targetPower;
extern boolean startOpen, selectOpen;

void ledInit(void);
void ps2Init(void);
void ps2Deal(void *pvParameters);

#endif
