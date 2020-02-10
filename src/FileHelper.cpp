// #include "FileHelper.h"
// // #include "FS.h"
// #include <LittleFS.h>

// String deviceid = "aeroponic_id_ecb8bd24";
// String baseURL = "https://otodidakserver.firebaseio.com/unit/" + deviceid + "/";

// String wifissid = "/ssid";
// String wifipwd = "/pwd";
// String onCfg = "/on";
// String offCfg = "/off";

// String getDeviceID() {
//     return deviceid;
// }

// void initializeSPIFS() {
//     LittleFSConfig cfg;
//     cfg.setAutoFormat(true);
//     LittleFS.setConfig(cfg);
//     LittleFS.begin();
// }

// void endSPIFS() {
//     LittleFS.end();
// }

// // if not exist should return 
// bool isWifiConfigExist() {
//     return LittleFS.exists(wifissid) && LittleFS.exists(wifipwd);
// }

// // if not exist should return default value.
// bool isRunConfigExist() {
//     return LittleFS.exists(onCfg) || LittleFS.exists(offCfg);
// }

// bool isFirebaseConfigExist() {
// // todo next
// return false;
// }

// // wifi config
// String loadSSID() {
//     if (isWifiConfigExist()) {
//         File fssid = LittleFS.open(wifissid, "r");
//         if (!fssid) {
//             Serial.println("File config for SSID is not found. Please setup Unit first...");
//             return "";
//         }
//         String data = fssid.readString();
//         fssid.close();
//         return data;
//     } else {
//         Serial.println("Either SSID or password not being set");
//     }
//     return "";
// }

// String loadPWD() {
//     if (isWifiConfigExist()) {
//         File fpwd = LittleFS.open(wifipwd, "r");
//         if (!fpwd) {
//             Serial.println("File config for SSID is not found. Please setup Unit first...");
//             return "";
//         }
//         String data = fpwd.readString();
//         fpwd.close();
//         return data;
//     } else {
//         Serial.println("Either SSID or password not being set");
//     }
//     return "";
// }

// // runtime config
// long loadOnTime() {
//     if (isRunConfigExist()) {
//         File f = LittleFS.open(onCfg, "r");
//         if (!f) {
//             Serial.println("On time is not found. fallback to 15 seconds");
//             return 15 * 1000;
//         }
    
//         String ct = f.readString();
//         f.close();
//         return ct.toInt();
//     }
//     return 15 * 1000;
// }
// long loadOffTime() {
//     if (isRunConfigExist()) {
//         File f = LittleFS.open(offCfg, "r");
//         if (!f) {
//             Serial.println("Off time is not found. fallback to 5 minute");
//             return 5 * 60 * 1000;
//         }
//         int dt = f.readString().toInt();
//         f.close();
//         return dt;
//     }
//     return 5 * 60 * 1000;
// }

// // get firebase config
// String getFirebaseConfigURL() {
//     return "";
// }
// long getFirebaseUpdateInterval() {
//     return 0;
// }

// String getFirebaseLogsURL() {
//     return "";
// }

// void saveSSID(String ssid) {
//     File f = LittleFS.open(wifissid, "w");
//     if (!f) {
//         Serial.println("File config for SSID is not found. Please setup Unit first...");
//     }
//     f.print(ssid);
//     f.close();
//     delay(500);

//     Serial.print("DATA SSID file: ");
//     Serial.println(loadSSID());
// }

// void savePWD(String pwd) {
//     File f = LittleFS.open(wifipwd, "w");
//     if (!f) {
//         Serial.println("File config for SSID is not found. Please setup Unit first...");
//     }
//     f.print(pwd);
//     f.close();
//     delay(500);

//     Serial.println("DATA PWD file: "+ loadPWD());
// }
// void saveONTime(String on) {
//     File f = LittleFS.open(onCfg, "w");
//     if (!f) {
//         Serial.println("File config for ON is not found. Please setup Unit first...");
//     }
//     f.print(on);
//     f.close();
//     delay(500);
//     Serial.print("DATA On file: ");
//     Serial.println(loadOnTime());
// }
// void saveOFFTime(String off) {
//     File f = LittleFS.open(offCfg, "w");
//     if (!f) {
//         Serial.println("File config for OFF is not found. Please setup Unit first...");
//     }
//     f.print(off);
//     f.close();
//     delay(500);

//     Serial.print("DATA off file: ");
//     Serial.println(loadOffTime());
// }
