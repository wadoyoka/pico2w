#include "WiFiConnection.h"

WiFiConnection::WiFiConnection(const char* ssid, const char* password) {
  _ssid = ssid;
  _password = password;
  _isConnected = false;
}

bool WiFiConnection::connect() {
  Serial.print("WiFi接続中...");
  
  WiFi.begin(_ssid, _password);
  
  // 接続を試みる（最大20回 = 10秒）
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  Serial.println();
  
  if (WiFi.status() == WL_CONNECTED) {
    _isConnected = true;
    Serial.println("WiFi接続完了");
    return true;
  } else {
    Serial.println("WiFi接続失敗");
    return false;
  }
}

bool WiFiConnection::isConnected() {
  _isConnected = (WiFi.status() == WL_CONNECTED);
  return _isConnected;
}

void WiFiConnection::disconnect() {
  WiFi.disconnect();
  _isConnected = false;
  Serial.println("WiFi切断");
}

