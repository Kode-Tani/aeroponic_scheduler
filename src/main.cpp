#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "mycfg.h"
#include "myserver.h"
#include "ep.h"
#include "fire.h"
#include <Tasker.h>

Config runCFG;

long rOnTime = 10*1000;
long rOffTime = 5 * 60 * 1000;
uint8_t RELAY = D5;
Tasker tasker;

void logger() {
  // send();
}

void relayController() {
  Serial.println("ON");
  logEvent("ON");
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(RELAY, LOW);
  delay(rOnTime);

  Serial.println("OFF");
  logEvent("OFF");
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(RELAY, HIGH);
  delay(rOffTime);
}

void setup() {
  Serial.begin(9600);

  bool ready = false;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RELAY, OUTPUT);
  initEprom();
  initializeFB();

  initWifi();
  startServer();
  delay(500);
  runCFG = loadConfig();
  if (runCFG.ssid[0] != NULL && runCFG.pwd[0] != NULL) {
    Serial.println("config found...");
    Serial.println(runCFG.ssid);
    Serial.println(runCFG.pwd);
    ready = connectToWifi(runCFG.ssid, runCFG.pwd);
  }

  if(!ready) {
    Serial.println("Failed to connect to saved config... fallback default.");
    ready = connectToWifi("azusa", "a2u5a.ucha");
  }

  if (runCFG.on > 1000){
      rOnTime = runCFG.on;
  }
    
  if (runCFG.on > 1000){
    rOffTime = runCFG.off;
  }
  Serial.print("ON time: ");
  Serial.println(rOnTime);
  Serial.print("off time: ");
  Serial.println(rOffTime);
  tasker.setInterval(relayController, 500);

  if(ready) {
    printWifiInfo();
    printRunConfigs();
    tasker.setInterval(logger, 1000);
    logEvent("DEVICE STARTED");
  } else {
    Serial.println("Cannot connect to default wifi");
  }
}

void loop() {
  tasker.loop();
}