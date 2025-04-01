#include "OpenWeatherClient.h"

OpenWeatherClient::OpenWeatherClient(const String& latitude, const String& longitude, const char* apiKey) {
  _latitude = latitude;
  _longitude = longitude;
  _apiKey = apiKey;
  _serverUrl = buildApiUrl();
}

String OpenWeatherClient::buildApiUrl() {
  return "http://api.openweathermap.org/data/2.5/weather?lat=" + _latitude + 
         "&lon=" + _longitude + 
         "&appid=" + String(_apiKey) + 
         "&lang=en&units=metric";
}

WeatherData OpenWeatherClient::getWeatherData() {
  WeatherData data = {0, "", 0, 0, 0, false}; // 初期値を設定
  
  HTTPClient http;
  http.begin(_serverUrl);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println("HTTPレスポンスコード: " + String(httpResponseCode));
    
    data = parseWeatherJson(payload);
  } else {
    Serial.println("HTTPリクエストエラー: " + String(httpResponseCode));
  }
  
  http.end();
  return data;
}

String OpenWeatherClient::getWeatherInKatakana(String weather) {
    if (weather == "Thunderstorm") return "	\xd7\xb2\xb3";//ライウ
    if (weather == "Drizzle") return "\xb7\xd8\xbb\xd2";//キリサメ
    if (weather == "Rain") return "\xb1\xd2";//アメ
    if (weather == "Snow") return "\xd5\xb7";//ユキ
    if (weather == "Clear") return "\xca\xda";//ハレ
    if (weather == "Clouds") return "\xb8\xd3\xd8";//クモリ
    if (weather == "Mist") return "\xd3\xd4";//モヤ
    if (weather == "Smoke") return "\xb9\xd1\xd8";//ケムリ
    if (weather == "Haze") return "\xb6\xbd\xd0";//カスミ
    if (weather == "Dust") return "\xce\xba\xd8";//ホコリ
    if (weather == "Fog") return "\xb7\xd8";//キリ
    if (weather == "Sand") return "\xbd\xc5";//スナ
    if (weather == "Ash") return "\xca\xb2";//ハイ
    if (weather == "Squall") return "\xbd\xba\xb0\xd9";//スコール
    if (weather == "Tornado") return "\xc4\xd9\xc8\xb0\xc4\xde";//トルネード

    return "\xcc\xd2\xb2"; // 該当なしの場合
}

WeatherData OpenWeatherClient::parseWeatherJson(String jsonString) {
  WeatherData data = {0, "", 0, 0, 0, false};
  
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, jsonString);
  
  if (!error) {
    data.temperature = doc["main"]["temp"];
    data.description = getWeatherInKatakana(doc["weather"][0]["main"].as<String>());
    data.humidity = doc["main"]["humidity"];
    data.pressure = doc["main"]["pressure"];
    data.windSpeed = doc["wind"]["speed"];
    data.isValid = true;
    
    Serial.println("JSON解析成功");
  } else {
    Serial.println("JSON解析エラー");
  }
  
  return data;
}

