/**
 * AWS IoT MQTT クライアント 証明書ファイル サンプル
 *
 * 使用方法:
 * 1. このファイルを "certificates.h" としてコピーします
 * 2. 各証明書と鍵を実際の値に置き換えます
 * 3. 実際の certificates.h ファイルは .gitignore に追加して、公開リポジトリにアップロードしないようにします
 *
 * 証明書の取得方法:
 * 1. AWS IoT コンソールで「モノ」を作成
 * 2. 証明書を作成またはインポート
 * 3. 証明書、秘密鍵、ルート CA 証明書をダウンロード
 */

#ifndef CERTIFICATES_H
#define CERTIFICATES_H

//=============================================================================
// AWS IoT ルート CA 証明書
//=============================================================================
// Amazon Root CA 1 証明書
// https://www.amazontrust.com/repository/AmazonRootCA1.pem からダウンロード可能
const char *AWS_ROOT_CA = R"EOF(
-----BEGIN CERTIFICATE-----
... (ここに実際のルート CA 証明書を入力) ...
-----END CERTIFICATE-----
)EOF";

//=============================================================================
// デバイス証明書
//=============================================================================
// AWS IoT コンソールからダウンロードした証明書
// ファイル名: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx-certificate.pem.crt
const char *CLIENT_CERT = R"EOF(
-----BEGIN CERTIFICATE-----
... (ここに実際のデバイス証明書を入力) ...
-----END CERTIFICATE-----
)EOF";

//=============================================================================
// デバイスの秘密鍵
//=============================================================================
// AWS IoT コンソールからダウンロードした秘密鍵
// ファイル名: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx-private.pem.key
const char *PRIVATE_KEY = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
... (ここに実際の秘密鍵を入力) ...
-----END RSA PRIVATE KEY-----
)EOF";

#endif // CERTIFICATES_H