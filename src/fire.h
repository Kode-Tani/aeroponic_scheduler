#ifndef FIRE_H
#define FIRE_H

#include <Arduino.h>

struct FireLog {
    String event;
    double temp;
    double humid;
};
void initializeFB();
void logEvent(FireLog);
void logEvent(String);
void logEvent(String, double, double);
void send();

#endif