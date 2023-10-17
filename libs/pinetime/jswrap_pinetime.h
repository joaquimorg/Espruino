#include "jspin.h"

void jswrap_pinetime_hwinit();
void jswrap_pinetime_init();
void jswrap_pinetime_kill();
bool jswrap_pinetime_idle();

void jswrap_pinetime_kickPollWatchdog();

JsVarInt jswrap_pinetime_getBattery();

