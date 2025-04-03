# Pico2w weather_station
本リポジトリは、pico2wを用いて天気情報をLCDに表示するプログラムです。<br>
pico2wじゃなくても、Arduinoが書き込めれば使えます。

文字が右から左に流れていきます。

# 完成品動画
以下動画URLです。

[Pico2WでSHARPキャラクターディスプレイモジュール(16×2行バックライト有)LM162AT1使う](https://www.youtube.com/watch?v=Av_Wy9Dt-k4&t=1s)

# 各ディレクトリの説明
- weather_station<br>
  Arduinoのソースコードが入っています。<br>
  weather_station.inoがメインファイルです。<br>
  使い方はweather_stationディレクトリのREADME.mdに書いてあります。
- circuit_diagram<br>
  回路図のpdfとkicad_schファイルが入っています。<br>
  描いてある内容はどっちも一緒なので、pdf推奨です。

# 環境
- [Raspberry Pi Pico 2 W](https://akizukidenshi.com/catalog/g/g130330/)
- [LCD](https://akizukidenshi.com/catalog/g/g101623/)
- [OpenWeatherAPI](https://openweathermap.org/api)

# 参考リンク
- [ラズパイPico/Pico2/PicoWのArduinoIDE2のインストール方法や使い方紹介](https://logikara.blog/raspi-pico-arduinoide/)
  <br>
  pico2wでは無いですが、参考になります。
- [OpenWeather APIの使い方](https://dev.classmethod.jp/articles/openweather_-pyowm/)
- [Lcdモジュールの使い方](https://mecha-norimaki.com/arduino_start_17/)
- [Lcdでカタカナや特殊文字を表示する](https://mecha-norimaki.com/arduino_start_17/#:~:text=%E3%81%AB%E3%81%AA%E3%82%8A%E3%81%BE%E3%81%99%E3%80%82-,%E3%82%AB%E3%82%BF%E3%82%AB%E3%83%8A%E3%82%84%E7%89%B9%E6%AE%8A%E6%96%87%E5%AD%97%E3%82%92%E8%A1%A8%E7%A4%BA%E3%81%99%E3%82%8B,-%E6%AC%A1%E3%81%AF%E3%80%81%E4%BB%A5%E4%B8%8B)