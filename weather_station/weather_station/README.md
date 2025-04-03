# weather_station使い方
1. 本ディレクトリをお手持ちのパソコンにダウンロードしてください。
2. weather_station.inoの5~24行目を適宜書き換えてください。
```arduino
// TODO Start------------------------------------------------------------------
// WiFi設定（ご自身のSSIDとパスワードに置き換えてください）
const char* ssid = "********";
const char* password = "************";

// OpenWeatherMap API設定
const String latitude = "************";              // ご自身の緯度に置き換えてください
const String longitude = "************";            // ご自身の経度に置き換えてください
const char* apiKey = "***********";  // ご自身のOpenWeather APIキーに置き換えてください


// LCDピン設定（ご自身の接続に合わせて変更してください）
const int rs = 0;
const int en = 1;
const int d4 = 2;
const int d5 = 3;
const int d6 = 4;
const int d7 = 5;

// TODO End------------------------------------------------------------------

```
3. ArduinoJsonをArduinoにインストールしてください。

   ![ArduinoJsonインストール画像](https://raw.githubusercontent.com/wadoyoka/pico2w/refs/heads/main/weather_station/imamges/ArduinoJson.png)
4. マイコンに書き込みましょう！
