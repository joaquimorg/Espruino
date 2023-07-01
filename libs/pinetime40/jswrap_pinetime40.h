#include "jspin.h"

void jswrap_pinetime40_hwinit();
void jswrap_pinetime40_init();
void jswrap_pinetime40_kill();
bool jswrap_pinetime40_idle();


void jswrap_pinetime40_setLCDOffset(int y);

void jswrap_pinetime40_setLCDBrightness(JsVarFloat v);
void jswrap_pinetime40_setLCDPower(bool isOn);
void jswrap_pinetime40_setLCDTimeout(JsVarFloat timeout);

JsVarInt jswrap_pinetime40_getBattery();
JsVar *jswrap_pinetime40_appRect();

int jswrap_pinetime40_isCharging();
int jswrap_pinetime40_isLCDOn();
void jswrap_pinetime40_setLocked(bool isLocked);

int jswrap_pinetime40_isLocked();
JsVar *jswrap_pinetime40_buzz(int time, JsVarFloat amt);
JsVar *jswrap_pinetime40_beep(int time, int freq);

void jswrap_pinetime40_setOptions(JsVar *options);
JsVar *jswrap_pinetime40_getOptions();

bool jswrap_pinetime40_setHRMPower(bool isOn, JsVar *appId);