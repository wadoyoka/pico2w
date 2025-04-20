#ifndef AWS_IOT_MQTT_CLIENT_H
#define AWS_IOT_MQTT_CLIENT_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

class AwsIotMqttClient
{
private:
    // AWS IoT Core 設定
    const char *_endpoint;
    const char *_rootCA;
    const char *_clientCert;
    const char *_privateKey;
    const char *_clientId;

    // ネットワーク接続
    WiFiClientSecure _wifiClient;
    PubSubClient _mqttClient;

    // コールバック関数ポインタ
    typedef void (*MessageCallback)(char *topic, byte *payload, unsigned int length);
    MessageCallback _callback = NULL;

    // 内部コールバック関数
    static void _internalCallback(char *topic, byte *payload, unsigned int length);
    static AwsIotMqttClient *_instance;

public:
    AwsIotMqttClient(const char *endpoint, const char *rootCA, const char *clientCert,
                     const char *privateKey, const char *clientId);
    ~AwsIotMqttClient();

    // 接続管理
    bool connect();
    bool isConnected();
    void disconnect();
    void loop();

    // メッセージ送信
    bool publish(const char *topic, const char *payload);
    bool publish(const char *topic, const char *payload, bool retained);

    // メッセージ受信
    bool subscribe(const char *topic);
    bool unsubscribe(const char *topic);
    void setCallback(MessageCallback callback);
};

#endif // AWS_IOT_MQTT_CLIENT_H