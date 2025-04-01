#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <WiFi.h>

class WiFiConnection {
  private:
    const char* _ssid;
    const char* _password;
    bool _isConnected;
    
  public:
    WiFiConnection(const char* ssid, const char* password);
    bool connect();
    bool isConnected();
    void disconnect();
};

#endif

