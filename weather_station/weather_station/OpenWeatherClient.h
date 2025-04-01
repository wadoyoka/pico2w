#ifndef OPEN_WEATHER_CLIENT_H
#define OPEN_WEATHER_CLIENT_H

#include <HTTPClient.h>
#include <ArduinoJson.h>

struct WeatherData {
  float temperature;
  String description;
  float humidity;
  float pressure;
  float windSpeed;
  bool isValid;
};

class OpenWeatherClient {
  private:
    String _latitude;
    String _longitude;
    const char* _apiKey;
    String _serverUrl;
    
  public:
    OpenWeatherClient(const String& latitude, const String& longitude, const char* apiKey);
    WeatherData getWeatherData();
    
  private:
    String buildApiUrl();
    String getWeatherInKatakana(String weather);
    WeatherData parseWeatherJson(String jsonString);
};

#endif

