#include <Arduino.h>
#include "fire.h"
#include "ep.h"
#include <ESP8266HTTPClient.h>
#include <FirebaseESP8266.h>

// HTTPClient http;
// char* baseURL = "https://aeroponic-id.firebaseio.com/unit/";

#define FIREBASE_HOST "aeroponic-id.firebaseio.com"
#define FIREBASE_AUTH "lqgGwyJSM0WXkLQdWMvggPjg5qVLryfG6mOwcyit" // secret (40 chars)

String message;
boolean sended = false;
FirebaseData firebaseData;
String path = "/unit";

void initializeFB() {
    String deviceID = getDeviceID();
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    
    if (!Firebase.beginStream(firebaseData, path + "/" + deviceID)) {
        Serial.println("Could not begin stream");
        Serial.println("REASON: " + firebaseData.errorReason());
        Serial.println();
    }
}

void send(FireLog logs) {
    // if(sended) return;
    sended = true;
    Serial.println("Sending data to firebase....");
    Serial.println(message);
    String deviceID = getDeviceID();

    FirebaseJson json;
    json.add("event", logs.event);
    long d = millis() / 1000;
    json.add("timestamp", ((int) d));
    json.add("humid", logs.humid);
    json.add("temp", logs.temp);

    Serial.println();
    if (!Firebase.pushJSON(firebaseData, path + "/" + deviceID + "/logs/", json)) {
        Serial.println("Could not Send stream");
        Serial.println("REASON: " + firebaseData.errorReason());
        Serial.println();
    } else {
        Serial.println("log tersimpan...");
    }

    // Firebase.pushString(firebaseData, url, message);

    // int httpCode = http.POST(message);
    // Serial.println(httpCode);
    // Serial.println(http.getString());
    // http.end();
}

void logEvent(FireLog logs) {
    sended = false;
    message = "{\"event\": \"" + logs.event + 
        "\", \"timestamp\": " + millis() + 
        ", \"humid\": " + logs.humid + 
        ", \"temp\": " + logs.temp +"}";
    send(logs);
}

void logEvent(String event) {
    FireLog logs;
    logs.event = event;
    logs.humid = -1;
    logs.temp = -1;
    logEvent(logs);
}

void logEvent(String event, double temp, double humid) {
    FireLog logs;
    logs.event = event;
    logs.humid = humid;
    logs.temp = temp;
    logEvent(logs);
}