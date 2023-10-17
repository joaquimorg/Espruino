#include "jspin.h"

void jswrap_pinetime_hwinit();
void jswrap_pinetime_init();
void jswrap_pinetime_kill();
bool jswrap_pinetime_idle();

void jswrap_pinetime_kickPollWatchdog();


void jswrap_pinetime_setLCDOffset(int y);

void jswrap_pinetime_setLCDBrightness(JsVarFloat v);
void jswrap_pinetime_setLCDPower(bool isOn);
void jswrap_pinetime_setLCDTimeout(JsVarFloat timeout);

JsVarInt jswrap_pinetime_getBattery();
JsVar *jswrap_pinetime_appRect();

int jswrap_pinetime_isCharging();
int jswrap_pinetime_isLCDOn();
void jswrap_pinetime_setLocked(bool isLocked);

void jswrap_pinetime_setLCDPowerBacklight(bool isOn);

int jswrap_pinetime_isLocked();
JsVar *jswrap_pinetime_buzz(int time, JsVarFloat amt);
JsVar *jswrap_pinetime_beep(int time, int freq);

void jswrap_pinetime_setOptions(JsVar *options);
JsVar *jswrap_pinetime_getOptions();

bool jswrap_pinetime_setHRMPower(bool isOn, JsVar *appId);