#include <SPI.h>
#include <MFRC522.h>
#include <HX711.h>
#include <LiquidCrystal.h>

// RFID Okuyucu ayarları
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Load Cell ayarları
#define DOUT_PIN A1
#define SCK_PIN A0
HX711 scale;

// LCD ekran ayarları
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// LED ve Buzzer ayarları
#define LED_PIN 8
#define BUZZER_PIN 9

// Kullanıcı bilgileri (UID ve bakiye)
struct User {
  String uid;
  int bakiye;
};

User users[] = {
  {"kart1_uid", 0},
  {"kart2_uid", 0}
};
const int numUsers = sizeof(users) / sizeof(users[0]);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale();
  scale.tare(); // Load cell sıfırlama

  lcd.begin(16, 2);
  lcd.print("Pil Geri Donusum");
  delay(2000);
  lcd.clear();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Load cell ile pil atılmasını kontrol et
  if (scale.get_units() > 10) { // Pilin ağırlığına göre ayarlayın
    Serial.println("Pil atildi.");
    lcd.setCursor(0, 0);
    lcd.print("Pil Atildi");
    delay(2000);
    lcd.clear();

    // RFID kart kontrolü
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      String cardUID = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        cardUID += String(mfrc522.uid.uidByte[i], HEX);
      }
      cardUID.toUpperCase();
      
      bool validUser = false;
      for (int i = 0; i < numUsers; i++) {
        if (users[i].uid == cardUID) {
          validUser = true;
          users[i].bakiye += 10; // Pil başına verilen puan
          lcd.setCursor(0, 0);
          lcd.print("Bakiye: ");
          lcd.setCursor(8, 0);
          lcd.print(users[i].bakiye);
          digitalWrite(LED_PIN, HIGH);
          tone(BUZZER_PIN, 1000); // Buzzer çaldır
          delay(1000);
          digitalWrite(LED_PIN, LOW);
          noTone(BUZZER_PIN); // Buzzer sustur
          delay(2000);
          lcd.clear();
          break;
        }
      }
      if (!validUser) {
        Serial.println("Gecersiz Kart.");
        lcd.setCursor(0, 0);
        lcd.print("Gecersiz Kart");
        digitalWrite(LED_PIN, LOW);
        tone(BUZZER_PIN, 500); // Hatalı Buzzer çaldır
        delay(1000);
        noTone(BUZZER_PIN); // Buzzer sustur
        delay(2000);
        lcd.clear();
      }
      mfrc522.PICC_HaltA();
    }
  }
  delay(500);
}
