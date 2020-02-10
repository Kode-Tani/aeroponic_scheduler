#include <Arduino.h>
#include "ep.h"
#include <EEPROM.h>

int addr = 0;
char* deviceid = "aeroponic_id_";
int devID = ESP.getChipId();

void initEprom() {
    EEPROM.begin(512);
}

String getDeviceID() {
    String _v = String(devID);
    return deviceid + _v;
}

bool isConfigExist() {
    Config cfg = loadConfig();

    Serial.print("eSSID ");
    Serial.println(cfg.ssid);
    Serial.print("ePWD ");
    Serial.println(cfg.pwd);
    Serial.print("eON ");
    Serial.println(cfg.on);
    Serial.print("eOFF ");
    Serial.println(cfg.off);

    return cfg.ssid[0] != NULL && cfg.pwd[0] != NULL;
}

void saveConfig(Config data) {
    EEPROM.put(addr, data);
    EEPROM.commit();
}

Config loadConfig() {
    Config cfg;
    EEPROM.get(addr, cfg);
    return cfg;
}
