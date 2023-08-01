#include <PS2X_lib.h>

#ifndef __PS2_H__
#define __PS2_H__

#define PS2_CMD 23
#define PS2_DAT 19
#define PS2_CLK 18
#define PS2_SEL  5

void ps2Init(void);
void ps2Deal(void *pvParameters);

#endif
