#include "AwsIotMqttClient.h"

// 静的メンバ変数の初期化
AwsIotMqttClient *AwsIotMqttClient::_instance = NULL;

// コンストラクタ
AwsIotMqttClient::AwsIotMqttClient(const char *endpoint, const char *rootCA, const char *clientCert,
                                   const char *privateKey, const char *clientId) : _endpoint(endpoint),
                                                                                   _rootCA(rootCA),
                                                                                   _clientCert(clientCert),
                                                                                   _privateKey(privateKey),
                                                                                   _clientId(clientId),
                                                                                   _mqttClient(_wifiClient)
{
    _instance = this;
}

// デストラクタ
AwsIotMqttClient::~AwsIotMqttClient()
{
    disconnect();
    _instance = NULL;
}

// 内部コールバック関数
void AwsIotMqttClient::_internalCallback(char *topic, byte *payload, unsigned int length)
{
    if (_instance && _instance->_callback)
    {
        _instance->_callback(topic, payload, length);
    }
}

// AWS IoT Core に接続
bool AwsIotMqttClient::connect()
{
    // SSL証明書の設定
    _wifiClient.setCACert(_rootCA);
    _wifiClient.setCertificate(_clientCert);
    _wifiClient.setPrivateKey(_privateKey);

    // MQTT クライアントの設定
    _mqttClient.setServer(_endpoint, 8883);
    _mqttClient.setCallback(_internalCallback);

    // 接続試行
    Serial.print("AWS IoT Core に接続中...");
    bool connected = _mqttClient.connect(_clientId);
    if (connected)
    {
        Serial.println("接続成功");
    }
    else
    {
        Serial.print("接続失敗, rc=");
        Serial.println(_mqttClient.state());
    }

    return connected;
}

// 接続状態確認
bool AwsIotMqttClient::isConnected()
{
    return _mqttClient.connected();
}

// 切断
void AwsIotMqttClient::disconnect()
{
    if (isConnected())
    {
        _mqttClient.disconnect();
        Serial.println("AWS IoT Core から切断しました");
    }
}

// メインループ処理
void AwsIotMqttClient::loop()
{
    if (isConnected())
    {
        _mqttClient.loop();
    }
}

// メッセージ送信
bool AwsIotMqttClient::publish(const char *topic, const char *payload)
{
    return publish(topic, payload, false);
}

// メッセージ送信（retained フラグ付き）
bool AwsIotMqttClient::publish(const char *topic, const char *payload, bool retained)
{
    if (!isConnected())
    {
        Serial.println("メッセージ送信失敗: MQTT クライアントが接続されていません");
        return false;
    }

    Serial.print("トピックに送信中: ");
    Serial.println(topic);

    bool result = _mqttClient.publish(topic, payload, retained);
    if (result)
    {
        Serial.println("メッセージ送信成功");
    }
    else
    {
        Serial.println("メッセージ送信失敗");
    }

    return result;
}

// トピック購読
bool AwsIotMqttClient::subscribe(const char *topic)
{
    if (!isConnected())
    {
        Serial.println("トピック購読失敗: MQTT クライアントが接続されていません");
        return false;
    }

    Serial.print("トピックを購読中: ");
    Serial.println(topic);

    bool result = _mqttClient.subscribe(topic);
    if (result)
    {
        Serial.println("トピック購読成功");
    }
    else
    {
        Serial.println("トピック購読失敗");
    }

    return result;
}

// トピック購読解除
bool AwsIotMqttClient::unsubscribe(const char *topic)
{
    if (!isConnected())
    {
        Serial.println("トピック購読解除失敗: MQTT クライアントが接続されていません");
        return false;
    }

    return _mqttClient.unsubscribe(topic);
}

// コールバック設定
void AwsIotMqttClient::setCallback(MessageCallback callback)
{
    _callback = callback;
}