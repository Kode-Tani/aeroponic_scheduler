#ifndef _MYCFG
#define _MYCFG
#include <Arduino.h>

void initWifi();
bool connectToWifi(String, String);
void printWifiInfo();

void printRunConfigs();

#endif 