# MQ_4_PlatformIO

本リポジトリは、MQ4 ガスセンサーで、主にメタンガスが漏れてないかを検知して、検知したら、AWSIOT 　 CORE に送信するものになります。

## AWS IoT MQTT Arduino クライアント

Arduino デバイスを AWS IoT Core に接続し、MQTT 通信を行うためのライブラリです。

## セットアップ方法

### 1. 設定ファイルの準備

1. `config_example.h` を `config.h` としてコピーします
2. `certificates_example.h` を `certificates.h` としてコピーします
3. 各ファイル内の設定値を実際の値に置き換えます

```bash
cp config_example.h config.h
cp certificates_example.h certificates.h
```
