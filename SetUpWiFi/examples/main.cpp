#include <Arduino.h>
#include <SetUpWiFi.h>

const char *ssid = "";
const char *password = "";

const char *ap_ssid = "ESP_AP";
const char *ap_pass = ""; // Mật khẩu nếu có (optional)

const int btn_reset = 4;
const int time_check = 10000; // thời gian kiểm tra kết nối wifi
const int time_reset = 10000; // thời gian reset wifi
String id;
SetUpWiFi wifisetup;

void setup() {
  Serial.begin(9600);
  wifisetup.begin(ssid, password, btn_reset, time_check);
}

void loop() {
  wifisetup.checkButton(time_reset);      // Kiểm tra nút nhấn, giữ trong 1 khoảng thời gian để reset wifi
  wifisetup.handleWiFi(ap_ssid, ap_pass); // kiểm tra wifi nếu có thì bỏ qua, ko thì phát Access Point
}
