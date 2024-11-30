#ifndef SET_UP_WIFI_H
#define SET_UP_WIFI_H

#include <Arduino.h>

// Kiểm tra loại vi điều khiển

#include <AsyncTCP.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

class SetUpWiFi {
private:
  const char *default_ssid;
  const char *default_password;
  const char *ap_ssid;
  const char *ap_password;
  AsyncWebServer server;
  void startCaptivePortal();
  void saveWiFiConfig(const String &ssid, const String &password);
  bool loadWiFiConfig(String &ssid, String &password);

public:
	SetUpWiFi(const char *ssid, const char *password, const char *ap_ssid, const char *ap_password);
  void begin();
};

#endif // MY_LIBRARY_H
