#include "mycfg.h"
#include <ESP8266WiFi.h>
#include "ep.h"
// #include "display.h"


void initWifi() {
  WiFi.mode(WIFI_AP_STA);
  // enable soft AP
  WiFi.softAP(getDeviceID(), "aeroponic.id");
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AccessPoint mode: ");
  Serial.print("SSID: ");
  Serial.println(getDeviceID());
  Serial.print("IP Server: ");
  Serial.println(myIP.toString());
  Serial.println();
}

// print wifi info
void printWifiInfo() {
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

bool connectToWifi(String ssid, String pwd) {
  WiFi.begin(ssid, pwd);

  Serial.print("Connecting to: ");
  Serial.print(ssid);
  Serial.print("|");
  Serial.print(pwd);
  Serial.print(" \t ");
  int retval = 0;
  while (WiFi.status() != WL_CONNECTED) {
    retval += 1;
    delay(1000);
    Serial.print(".");
    if(retval >= 10) {
        Serial.print("END");
        Serial.println();
      return WiFi.status() == WL_CONNECTED;
    }
  }
  return true;
}

void printRunConfigs() {
  // Serial.print("ON time: ");
  // Serial.print(loadOnTime());
  // Serial.println(" Milliseconds");

  // Serial.print("OFF time: ");
  // Serial.print(loadOffTime());
  // Serial.println(" Milliseconds");
}