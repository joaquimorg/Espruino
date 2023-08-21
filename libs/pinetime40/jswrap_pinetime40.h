#include "jspin.h"
#include "bma400.h"

void jswrap_pinetime40_hwinit();
void jswrap_pinetime40_init();
void jswrap_pinetime40_kill();
bool jswrap_pinetime40_idle();


void jswrap_pinetime40_setLCDOffset(int y);

void jswrap_pinetime40_setLCDBrightness(JsVarFloat v);
void jswrap_pinetime40_setLCDPower(bool isOn);
void jswrap_pinetime40_setLCDTimeout(JsVarFloat timeout);

JsVarInt jswrap_pinetime40_getBattery();
JsVarFloat jswrap_pinetime40_battVoltage();

int jswrap_pinetime40_isCharging();
int jswrap_pinetime40_isLCDOn();
void jswrap_pinetime40_setLocked(bool isLocked);

void jswrap_pinetime40_setLCDPowerBacklight(bool isOn);

int jswrap_pinetime40_isLocked();
JsVar *jswrap_pinetime40_buzz(int time, JsVarFloat amt);
JsVar *jswrap_pinetime40_beep(int time, int freq);

void jswrap_pinetime40_setOptions(JsVar *options);
JsVar *jswrap_pinetime40_getOptions();

bool jswrap_pinetime40_setHRMPower(bool isOn, JsVar *appId);

void jswrap_pinetime40_accelWr(JsVarInt reg, JsVarInt data);
JsVar *jswrap_pinetime40_accelRd(JsVarInt reg, JsVarInt cnt);

int8_t bma400_interface_init(struct bma400_dev *bme, uint8_t intf);
int8_t bma400_read_i2c(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t bma400_write_i2c(uint8_t i2c_addr, uint8_t reg_addr, const uint8_t *reg_data, uint16_t length);
void bma400_delay_ms(uint32_t period_ms);
void bma400_check_rslt(const char api_name[], int8_t rslt);

int jswrap_pinetime40_getStepCount();