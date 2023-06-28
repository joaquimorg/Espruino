#include "jspin.h"

void jswrap_pinetime40_hwinit();
void jswrap_pinetime40_init();
void jswrap_pinetime40_kill();
bool jswrap_pinetime40_idle();


void jswrap_pinetime40_setLCDOffset(int y);

void jswrap_pinetime40_setLCDBrightness(JsVarFloat v);
void jswrap_pinetime40_setLCDPower(bool isOn);
JsVarInt jswrap_pinetime40_getBattery();
JsVar *jswrap_pinetime40_appRect();

int jswrap_pinetime40_isCharging();
