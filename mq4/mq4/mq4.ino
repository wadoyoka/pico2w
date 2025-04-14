#include <LiquidCrystal.h>
const int sensorPin = A0;

// LCDピン設定（ご自身の接続に合わせて変更してください）
const int rs = 0;
const int en = 1;
const int d4 = 2;
const int d5 = 3;
const int d6 = 4;
const int d7 = 5;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // LCD初期化
  lcd.begin(16, 2);
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
}

void loop() {
  Serial.print("Analog output: ");
  Serial.println(analogRead(sensorPin));  // Read the analog value of the gas sensor and print it to the serial monitor
  lcd.setCursor(0, 0);
  lcd.print("Analog Output");
  lcd.setCursor(0, 1);
  lcd.print(analogRead(sensorPin));
  delay(1000);                             // Wait for 50 milliseconds
}
