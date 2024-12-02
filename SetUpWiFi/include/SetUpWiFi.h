#ifndef SET_UP_WIFI_H
#define SET_UP_WIFI_H

#include <Arduino.h>

// Kiểm tra loại vi điều khiển
#ifdef ESP32
#include <AsyncTCP.h>
#include <WiFi.h>

#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>

#endif
#include <EEPROM.h>
#include <ESPAsyncWebServer.h>

class SetUpWiFi {
private:
  const char *default_ssid;
  const char *default_password;
  String ap_ssid;
  String ap_password;
  AsyncWebServer server;
  int resetPin;
  bool wifiConnected = false;
  bool apStarted = false;

  void saveWiFiConfig(const String &ssid, const String &password);
  bool loadWiFiConfig(String &ssid, String &password);
  bool isButtonPressed(int timeCheckReset);
  void clearWiFiConfig();
  void autoHandleWiFi();

public:
  SetUpWiFi();
  void begin(const char *ssid, const char *password, int resetPin, int timeCheck = 30000);
  void checkButton(int timeCheckReset = 2000);
  void startCaptivePortal(const char *ap_ssid = nullptr, const char *ap_password = nullptr);
  void handleWiFi(const char *ap_ssid = nullptr, const char *ap_password = nullptr);
};

#endif // SET_UP_WIFI_H
