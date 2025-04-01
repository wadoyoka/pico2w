#include "WiFiConnection.h"
#include "OpenWeatherClient.h"
#include <LiquidCrystal.h>

// WiFi設定（ご自身のSSIDとパスワードに置き換えてください）
const char* ssid = "********";
const char* password = "************";

// OpenWeatherMap API設定
const String latitude = "************";              // ご自身の経度に置き換えてください
const String longitude = "************";            // ご自身の経度に置き換えてください
const char* apiKey = "***********";  // ご自身のOpenWeather APIキーに置き換えてください


// LCDピン設定（ご自身の接続に合わせて変更してください）
const int rs = 0;
const int en = 1;
const int d4 = 2;
const int d5 = 3;
const int d6 = 4;
const int d7 = 5;




// クラスのインスタンスを作成
WiFiConnection wifiConnection(ssid, password);
OpenWeatherClient weatherClient(latitude, longitude, apiKey);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
WeatherData weather;

//天気情報表示文字
const String tenki = "\xc3\xdd\xb7";
const String situdo = "\xbc\xc2\xc4\xde";
const String kion = "\xb7\xb5\xdd";
const String kiatsu = "\xb7\xb1\xc2";
const String huusoku = "\xcc\xb3\xbf\xb8";


unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval =10 * 60 * 1000;       // interval at which to blink (milliseconds)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();

  // LCD初期化
  lcd.begin(16, 2);

  // 起動メッセージ表示
  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(1000);
  // WiFi接続
  lcd.setCursor(0, 1);
  lcd.print("WiFi connecting");

  wifiConnection.connect();
  lcd.setCursor(0, 1);
  if (wifiConnection.isConnected()) {
    lcd.print("Setup complete");
  } else {
    lcd.print("Wifi DisConnect");
  }
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval || !(wifiConnection.isConnected()) || !(weather.isValid)) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    if (wifiConnection.isConnected()) {
      // 天気データの取得
      weather = weatherClient.getWeatherData();
      lcd.clear();
    } else {
      Serial.println("WiFi未接続");

      // 再接続を試みる
      wifiConnection.connect();
    }
  } else {
    if (weather.isValid) {
      // Serial.println("現在の天気情報:");
      // Serial.println("温度: " + String(weather.temperature) + "°C");
      // Serial.println("天気: " + weather.description);
      // Serial.println("湿度: " + String(weather.humidity) + "%");
      // Serial.println("気圧: " + String(weather.pressure) + "hPa");
      // Serial.println("風速: " + String(weather.windSpeed) + "m/s");

      lcd.setCursor(0, 0);
      lcd.print(tenki + ":" + weather.description+"  "+kion+":"+String(weather.temperature) + "\xdf\x43 "+situdo+":"+String(weather.humidity) + "%");
      lcd.setCursor(0, 1);
      lcd.print(kiatsu+":"+String(weather.pressure) + "hPa "+huusoku+":"+String(weather.windSpeed) +"m/s");
      delay(400);
      for (int positionCounter = 0; positionCounter < 36; positionCounter++) {
        // scroll one position left:
        lcd.scrollDisplayLeft();
        // wait a bit:
        delay(600);
      }
    }
  }
}
