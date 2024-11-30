#include "SetUpWiFi.h"
#include <index.h>

SetUpWiFi::SetUpWiFi(const char *ssid, const char *password, const char *ap_ssid, const char *ap_password)
    : default_ssid(ssid), default_password(password), ap_ssid(ap_ssid), ap_password(ap_password), server(80) {}

void SetUpWiFi::begin() {
  String saved_ssid, saved_password;
  if (loadWiFiConfig(saved_ssid, saved_password)) {
    WiFi.begin(saved_ssid.c_str(), saved_password.c_str());
  } else {
    WiFi.begin(default_ssid, default_password);
  }
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect, starting captive portal...");
    startCaptivePortal();
  }
}

void SetUpWiFi::startCaptivePortal() {
  WiFi.softAP(ap_ssid, ap_password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send_P(200, "text/html", INDEX_HTML); });
  server.on("/getwifi", HTTP_POST, [this](AsyncWebServerRequest *request) {
    String ssid = request->arg("ssid");
    String password = request->arg("password");
    this->saveWiFiConfig(ssid, password);
    if (ssid != "") {
      request->send(200, "text/plain", "Cấu hình WiFi thành công. ESP32 đang kết nối...");
      delay(2000);
      ESP.restart();
    }
  });
  server.begin();
}

void SetUpWiFi::saveWiFiConfig(const String &ssid, const String &password) {
  EEPROM.begin(512);
  for (int i = 0; i < ssid.length(); i++) {
    EEPROM.write(i, ssid[i]);
  }
  EEPROM.write(ssid.length(), 0);
  for (int i = 0; i < password.length(); i++) {
    EEPROM.write(100 + i, password[i]);
  }
  EEPROM.write(100 + password.length(), 0);
  EEPROM.commit();
  Serial.println("WiFi configuration saved to EEPROM.");
}

bool SetUpWiFi::loadWiFiConfig(String &ssid, String &password) { EEPROM.begin(512);
  char ssid_buffer[100];
  for (int i = 0; i < 100; i++) {
    ssid_buffer[i] = EEPROM.read(i);
    if (ssid_buffer[i] == 0)
      break; // Ký tự kết thúc chuỗi
  }
  ssid = String(ssid_buffer);

  char password_buffer[100];
  for (int i = 0; i < 100; i++) {
    password_buffer[i] = EEPROM.read(100 + i);
    if (password_buffer[i] == 0)
      break; // Ký tự kết thúc chuỗi
  }
  password = String(password_buffer);

  if (ssid.length() > 0 && password.length() > 0) {
    Serial.println("WiFi configuration loaded from EEPROM.");
    return true;
  }
  Serial.println("No WiFi configuration found in EEPROM.");
  return false;
}