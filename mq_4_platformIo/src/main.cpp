/**
 * AWS IoT Core MQTT クライアント サンプルスケッチ
 *
 * このスケッチは、AWS IoT Core と MQTT 通信を行うためのサンプルです。
 * 証明書ファイル (certificates.h) と設定ファイル (config.h) を使用して
 * コードを整理し、メンテナンス性を向上させています。
 *
 * 機能:
 * - AWS IoT Core への接続
 * - メッセージの送信 (publish)
 * - メッセージの受信 (subscribe)
 * - 定期的なセンサーデータの送信
 */
#include <Arduino.h>
#include <WiFi.h>
#include "AwsIotMqttClient.h"
#include "certificates.h" // 証明書ファイル
#include "config.h"       // 設定ファイル

// AWS IoT MQTT クライアントのインスタンス作成
AwsIotMqttClient mqttClient(
    AWS_IOT_ENDPOINT, // AWS IoT エンドポイント
    AWS_ROOT_CA,      // ルート CA 証明書
    CLIENT_CERT,      // クライアント証明書
    PRIVATE_KEY,      // 秘密鍵
    CLIENT_ID         // クライアント ID
);

// センサーデータ
int gas_data = 0;

// 接続状態
bool connected = false;

/**
 * メッセージ受信コールバック関数
 * AWS IoT Core からメッセージを受信したときに呼び出されます
 */
void messageCallback(char *topic, byte *payload, unsigned int length)
{
  // 受信したメッセージをシリアルモニタに表示
  Serial.print("メッセージ受信 [");
  Serial.print(topic);
  Serial.print("]: ");

  // ペイロードを文字列に変換
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';
  Serial.println(message);

  // メッセージの処理
  // ここでは簡単な例として、"led:on" というメッセージを受け取ったら LED を点灯
  if (strcmp(message, "led:on") == 0)
  {
    Serial.println("LED をオンにします");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  // "led:off" というメッセージを受け取ったら LED を消灯
  else if (strcmp(message, "led:off") == 0)
  {
    Serial.println("LED をオフにします");
    digitalWrite(LED_BUILTIN, LOW);
  }
}

/**
 * AWS IoT Core に接続する関数
 */
void connectToAwsIot()
{
  Serial.println("AWS IoT Core に接続を試みます...");

  // コールバック関数を設定
  mqttClient.setCallback(messageCallback);

  // 接続を試行
  if (mqttClient.connect())
  {
    Serial.println("AWS IoT Core に接続しました");

    // トピックを購読

    // TODO SubScribeもするならここのコメントを外す↓
    // Serial.print("トピックを購読します: ");
    // Serial.println(SUBSCRIBE_TOPIC);
    // mqttClient.subscribe(SUBSCRIBE_TOPIC);
    // TODO

    connected = true;
  }
  else
  {
    Serial.println("AWS IoT Core への接続に失敗しました");
    connected = false;
  }
}

/**
 * WiFi に接続する関数
 */
void connectToWiFi()
{
  Serial.print("WiFi に接続中: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // WiFi 接続を待機
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi に接続しました");
  Serial.print("IP アドレス: ");
  Serial.println(WiFi.localIP());
}

/**
 * センサーデータを読み取る関数（サンプル）
 * 実際のプロジェクトでは、実際のセンサーからデータを読み取ります
 */
void readSensorData()
{
  gas_data = analogRead(MQ4_PIN);
  // TODO アラートをちゃんと実装する
  if (gas_data >= MQ4_DANGER_LINE)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RED_LED_PIN, HIGH);
    delay(5000);
  }
  // TODO　アラートをちゃんと実装する
}

/**
 * センサーデータを JSON 形式で送信する関数
 */
void publishSensorData()
{
  // センサーデータを読み取る
  readSensorData();

  // JSON 形式のペイロードを作成
  String payload = "{";
  payload += "\"device_id\":\"" + String(CLIENT_ID) + "\",";
  payload += "\"gas\":" + String(gas_data, 1);
  payload += "}";

  // データを送信
  Serial.print("センサーデータを送信します: ");
  Serial.println(payload);

  if (mqttClient.publish(PUBLISH_TOPIC, payload.c_str()))
  {
    Serial.println("データ送信成功");
  }
  else
  {
    Serial.println("データ送信失敗");
  }
}

/**
 * MQ4センサーが適正な値になっているか確認しつつ準備する関数
 */
void MQ4_Setup()
{
  Serial.println("MQ4ガスセンサーセットアップ開始");
  digitalWrite(GREEN_LED_PIN, HIGH);
  int isWarmedCount = 0;
  int mq4_data = 0;
  while (isWarmedCount < MQ4_PERMISSION_WARM_COUNT)
  {
    mq4_data = analogRead(MQ4_PIN);
    Serial.println("MQ4 Setup: " + String(mq4_data));
    if (isWarmedCount % 2 == 0)
    {
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, HIGH);
    }
    else
    {
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
    }

    if (mq4_data < MQ4_SAFE_LINE)
    {
      isWarmedCount++;
    }
    else
    {
      isWarmedCount = 0;
    }
    delay(MQ4_CHECK_WARM_COUNT_INTERVAL);
  }
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  Serial.println("MQ4ガスセンサーセットアップ完了");
}

/**
 * セットアップ関数
 * スケッチの起動時に一度だけ実行されます
 */
void setup()
{
  // シリアル通信を初期化
  Serial.begin(115200);
  delay(1000); // シリアルポートが安定するまで待機

  Serial.println();
  Serial.println("AWS IoT Core MQTT クライアント サンプル");
  Serial.println("=====================================");

  // LED ピンを出力として設定
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  // MQ4ガスセンサーのセットアップ
  MQ4_Setup();

  // WiFi に接続
  connectToWiFi();

  // AWS IoT Core に接続
  connectToAwsIot();

  // 乱数ジェネレータを初期化（センサーデータのシミュレーション用）
  randomSeed(analogRead(0));
}

/**
 * ループ関数
 * setup() の後に繰り返し実行されます
 */
void loop()
{
  // MQTT クライアントのループ処理
  mqttClient.loop();

  // WiFi 接続が切れた場合は再接続
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi 接続が切断されました。再接続します...");
    connectToWiFi();
  }

  // AWS IoT Core 接続が切れた場合は再接続
  if (!mqttClient.isConnected() && connected)
  {
    Serial.println("AWS IoT Core 接続が切断されました。再接続します...");
    connectToAwsIot();
  }

  // 定期的にセンサーデータを送信
  static unsigned long lastPublishTime = 0;
  if (millis() - lastPublishTime > PUBLISH_INTERVAL)
  {
    lastPublishTime = millis();

    if (mqttClient.isConnected())
    {
      publishSensorData();
    }
    else
    {
      Serial.println("MQTT クライアントが接続されていないため、データを送信できません");
    }
  }

  delay(100); // CPU 負荷を軽減
}