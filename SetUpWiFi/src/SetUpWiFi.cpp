#include "SetUpWiFi.h"
#include <index.h>

SetUpWiFi::SetUpWiFi() : server(80) {}

void SetUpWiFi::begin(const char *ssid, const char *password, int buttonPin, int timeCheck) {
  this->buttonPin = buttonPin;
  pinMode(buttonPin, INPUT_PULLUP);
  String saved_ssid, saved_password;
  if (loadWiFiConfig(saved_ssid, saved_password)) {
    WiFi.begin(saved_ssid.c_str(), saved_password.c_str());
  } else {
    WiFi.begin(ssid, password);
  }
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeCheck) {
    delay(500);
  }
}

void SetUpWiFi::startCaptivePortal(const char *ap_ssid, const char *ap_password) {
  WiFi.softAP(ap_ssid, ap_password);
  IPAddress IP = WiFi.softAPIP();
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
  apStarted = true;
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
}

bool SetUpWiFi::loadWiFiConfig(String &ssid, String &password) {
  EEPROM.begin(512);
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
    return true;
  }
  return false;
}

bool SetUpWiFi::isButtonPressed(int timeCheckReset) {
  unsigned long startPressTime = millis();
  while (digitalRead(buttonPin) == LOW) {             // Chờ nút được nhấn (Low là nút được nhấn)
    if (millis() - startPressTime > timeCheckReset) { // Kiểm tra nếu nút được giữ lâu hơn 2 giây
      return true;
    }
  }
  return false;
}

void SetUpWiFi::checkButton(int timeCheckReset) {
  // Kiểm tra trạng thái nút nhấn trong vòng lặp chính
  if (isButtonPressed(timeCheckReset)) {
    clearWiFiConfig();
    ESP.restart(); // Khởi động lại ESP
  }
}

void SetUpWiFi::clearWiFiConfig() {
  EEPROM.begin(512);
  // Xóa cấu hình WiFi bằng cách ghi 0 vào EEPROM
  for (int i = 0; i < 100; i++) {
    EEPROM.write(i, 0);
  }
  for (int i = 100; i < 200; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

void SetUpWiFi::autoHandleWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!wifiConnected) {
      wifiConnected = true;
      apStarted = false; // Dừng trạng thái AP khi đã kết nối WiFi
    }
  } else {
    if (!apStarted) {
      startCaptivePortal(ap_ssid, ap_password); // Dùng AP mặc định
    }
    wifiConnected = false;
  }
}

void SetUpWiFi::handleWiFi(const char *ap_ssid, const char *ap_password) {
  this->ap_ssid = ap_ssid;
  this->ap_password = ap_password;
  autoHandleWiFi();
}
