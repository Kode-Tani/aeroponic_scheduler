#ifndef EP_H
#define EP_H
#include <Arduino.h>

struct Config {
    char ssid[20] = {NULL};
    char pwd[20] = {NULL};
    int on = -1;
    int off = -1;
};

void initEprom();
String getDeviceID();
bool isConfigExist();

void saveConfig(Config);
Config loadConfig();

#endif