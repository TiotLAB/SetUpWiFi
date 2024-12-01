#ifndef SET_UP_WIFI_H
#define SET_UP_WIFI_H

#include <Arduino.h>

// Kiểm tra loại vi điều khiển

#include <AsyncTCP.h>
#include <EEPROM.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

class SetUpWiFi {
private:
  const char *default_ssid;
  const char *default_password;
  const char *ap_ssid;
  const char *ap_password;
  AsyncWebServer server;
  int buttonPin;

  void saveWiFiConfig(const String &ssid, const String &password);
  bool loadWiFiConfig(String &ssid, String &password);
  bool isButtonPressed();
  void clearWiFiConfig();

public:
  SetUpWiFi(const char *ssid, const char *password, int buttonPin);
  void begin();
  void checkButton();
  void startCaptivePortal(const char *ap_ssid, const char *ap_password);
};

#endif // SET_UP_WIFI_H
