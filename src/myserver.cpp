#include "myserver.h"
#include "ep.h"
#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>


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
  <form action="/get">
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

void startServer() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", index_html);
    });

    server.on("/info", HTTP_GET, [](AsyncWebServerRequest *request) {
        String wif = WiFi.localIP().toString();

        request->send(200, "text/html", 
          "Unit connected to: " + WiFi.SSID() +
          "<br>Unit IP: " + WiFi.localIP().toString()
        );
    });
    
    server.on("/unitid", HTTP_GET, [](AsyncWebServerRequest *request) {
        String data = getDeviceID();
        // txt.toCharArray(data, txt.length() +1);
        request->send(200, "text/html", "{ \"data\" :\"" + data +"\"}" );
    });

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request) {
        // todo reset ESP from here...
    });

    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String inputMessage;
        String inputParam;
        // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
        if (request->hasParam(PARAM_SSID)) {
            inputMessage = request->getParam(PARAM_SSID)->value();
            inputParam = PARAM_SSID;
            inputMessage.toCharArray(cfg.ssid, 20);
            // saveSSID(inputMessage);
        }

        if (request->hasParam(PARAM_PWD)) {
            inputMessage = request->getParam(PARAM_PWD)->value();
            inputParam = PARAM_PWD;
            inputMessage.toCharArray(cfg.pwd, 20);
            // savePWD(inputMessage);
        }
        
        if (request->hasParam(PARAM_ON)) {
            inputMessage = request->getParam(PARAM_ON)->value();
            inputParam = PARAM_ON;
            cfg.on = inputMessage.toInt();
            // saveONTime(inputMessage);
        }

        if (request->hasParam(PARAM_OFF)) {
            inputMessage = request->getParam(PARAM_OFF)->value();
            inputParam = PARAM_OFF;
            cfg.off = inputMessage.toInt();
            // saveOFFTime(inputMessage);
        }
        saveConfig(cfg);
        request->send(200, "text/html", "{\"message\" : \"SUCCESS\" }");
    });
    server.onNotFound(notFound);
    server.begin();
}