#include "myserver.h"
#include "ep.h"
#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>


const char* PARAM_SSID = "ssid";
const char* PARAM_PWD = "pwd";
const char* PARAM_ON = "ontime";
const char* PARAM_OFF = "offtime";

AsyncWebServer server(80);

Config cfg;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <p><img src="https://sc02.alicdn.com/kf/HTB1tbPDXnHuK1RkSndVq6xVwpXai/lyine-new-vertical-aeroponic-tower-garden.jpg" alt="" width="139" height="139" /><span style="color: #3366ff;"><strong><span style="font-size: 400%;">Aeroponic.id</span></strong></span></p>
  <hr>

  <H2>WIFI Config</H2><br>
  <form action="/config">
    WIFI AP SSID:&nbsp <input type="text" name="ssid"><br>
    WIFI PWD:&nbsp <input type="text" name="pwd"><br><br>
    <H2>ON/OFF Config</H2><br>
    ON Time (in milliseconds):&nbsp <input type="text" name="ontime" value="10000"><br>
    OFF time (in milliseconds):&nbsp <input type="text" name="offtime" value="300000"><br>
    <input type="submit" value="Submit">
  </form><br>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String getConfigJson() {
  String data = getDeviceID();
  Config cfg = loadConfig();

  DynamicJsonDocument doc(256);
  JsonObject obj = doc.to<JsonObject>();

  obj["deviceId"] = data;
  obj["ssid"] = cfg.ssid;
  obj["pwd"] = cfg.pwd;
  obj["version"] = getOSVersion();
  obj["on_time"] = cfg.on;
  obj["off_time"] = cfg.off;

  char output[256];
  serializeJson(obj, output);
  Serial.println(output);
        
  return output;
}

void startServer() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", index_html);
    });

    server.on("/info", HTTP_GET, [](AsyncWebServerRequest *request) {

        request->send(200, "text/html", 
          "Unit connected to: " + WiFi.SSID() +
          "<br>Unit IP: " + WiFi.localIP().toString()
        );
    });

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request) {
        // todo reset ESP from here...
        request->send_P(200, "text/html", "Restarting...");
        delay(1000);
        ESP.restart();
    });

    server.on("/unit", HTTP_GET, [](AsyncWebServerRequest *request) {
        String data = getDeviceID();
        DynamicJsonDocument doc(256);
        JsonObject obj = doc.to<JsonObject>();

        obj["deviceId"] = data;
        obj["ssid"] = WiFi.SSID();
        obj["ip"] = WiFi.localIP().toString();
        obj["version"] = getOSVersion();
        
        char output[256];
        serializeJson(obj, output);
        Serial.println(output);
        
        request->send_P(200, "text/json",  output);
    });

    server.on("/getc", HTTP_GET, [] (AsyncWebServerRequest *request) {
      request->send(200, "text/json", getConfigJson());
    });

    server.on("/config", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String inputMessage;
        String inputParam;
        // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
        bool newconfig = false;
        if (request->hasParam(PARAM_SSID)) {
            inputMessage = request->getParam(PARAM_SSID)->value();
            inputParam = PARAM_SSID;
            inputMessage.toCharArray(cfg.ssid, 20);
            newconfig = true;
        }

        if (request->hasParam(PARAM_PWD)) {
            inputMessage = request->getParam(PARAM_PWD)->value();
            inputParam = PARAM_PWD;
            inputMessage.toCharArray(cfg.pwd, 20);
            newconfig = true;
        }
        
        if (request->hasParam(PARAM_ON)) {
            inputMessage = request->getParam(PARAM_ON)->value();
            inputParam = PARAM_ON;
            cfg.on = inputMessage.toInt();
            // saveONTime(inputMessage);
            newconfig = true;
        }

        if (request->hasParam(PARAM_OFF)) {
            inputMessage = request->getParam(PARAM_OFF)->value();
            inputParam = PARAM_OFF;
            cfg.off = inputMessage.toInt();
            newconfig = true;
        }
        if (newconfig) {
          saveConfig(cfg);
        }

        request->send(200, "text/json", "sukses");
    });
    server.onNotFound(notFound);
    server.begin();
}