// #ifndef FILEHELPER
// #define FILEHELPER

// #include <Arduino.h>

// String getDeviceID();

// void initializeSPIFS();
// void endSPIFS();

// bool isWifiConfigExist();
// bool isRunConfigExist();
// bool isFirebaseConfigExist();

// // wifi config
// String loadSSID();
// void saveSSID(String);

// String loadPWD();
// void savePWD(String);

// // runtime config
// long loadOnTime();
// void saveONTime(String);

// long loadOffTime();
// void saveOFFTime(String);

// // get firebase config
// String getFirebaseConfigURL();
// long getFirebaseUpdateInterval();
// String getFirebaseLogsURL();

// struct DataLogger {
//     long timestamp;
//     String state; // "ON" or "OFF"
//     double temperature; 
//     double humidity;
//     String message; // additional message
// };

// #endif