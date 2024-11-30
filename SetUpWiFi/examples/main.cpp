#include <Arduino.h>
#include <SetUpWiFi.h>

// WiFi mặc định để trống hoặc để bất kỳ
const char *wifi_ssid = "";
const char *wifi_password = "";

// WiFi AP khi không kết nối được
const char *ap_ssid = "SetupWiFi";
const char *ap_password = "";

SetUpWiFi wifiManager(wifi_ssid, wifi_password, ap_ssid, ap_password);

void setup() {
  Serial.begin(9600);
  wifiManager.begin();
}

void loop() {
  // Code chính
}
