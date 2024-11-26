#include <Wire.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD

#define ONE_WIRE_BUS A0     // Pin data untuk sensor DS18B20
#define BUZZER_PIN 12       // Pin untuk buzzer

// Inisialisasi pin untuk relay
const int relayPin = 5; // Pin digital untuk relay

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

bool buzzerTriggered = false; // Penanda untuk status buzzer

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  sensors.begin();
  pinMode(BUZZER_PIN, OUTPUT); // Mengatur pin buzzer sebagai output

    // Inisialisasi pin relay sebagai output
  pinMode(relayPin, OUTPUT);
    // Matikan relay di awal
  digitalWrite(relayPin, LOW);
}

void loop() {
  sensors.requestTemperatures();             // Meminta pembaruan suhu
  float suhu = sensors.getTempCByIndex(0);   // Membaca suhu dalam Celsius
  
   // Tampilkan suhu pada LCD
  lcd.setCursor(0, 0); // Set kursor ke baris kedua
  lcd.print("Suhu  : ");
  lcd.print(suhu);
  lcd.setCursor(14, 0); // Set kursor ke baris kedua
  lcd.write(223); // Menampilkan simbol derajat
  lcd.print("C"); // Spasi tambahan untuk menghapus angka sebelumnya
  
    //Mengontrol Lampu berdasarkan suhu
  lcd.setCursor(0, 1); // Set kursor ke baris kedua
  lcd.print("Kipas : ");
  lcd.setCursor(8, 1);

  // Jika suhu lebih dari 25°C, nyalakan relay
  if (suhu >= 25.0) {
    digitalWrite(relayPin, HIGH);  // Nyalakan relay (aktifkan lampu)
    lcd.print("ON ");
  } else {
    digitalWrite(relayPin, LOW);   // Matikan relay (matikan lampu)
    lcd.print("OFF");
  }

  if (suhu >= 25.0 && !buzzerTriggered) {   // Jika suhu >= 25°C dan buzzer belum menyala
    digitalWrite(BUZZER_PIN, HIGH);         // Menyalakan buzzer
    delay(500);                              // Buzzer menyala selama 50 ms
    digitalWrite(BUZZER_PIN, LOW);          // Mematikan buzzer setelah 50 ms
    delay(500);   
    digitalWrite(BUZZER_PIN, HIGH);         // Menyalakan buzzer
    delay(500);                              // Buzzer menyala selama 50 ms
    digitalWrite(BUZZER_PIN, LOW);          // Mematikan buzzer setelah 50 ms
    delay(500);   
    digitalWrite(BUZZER_PIN, HIGH);         // Menyalakan buzzer
    delay(500);                              // Buzzer menyala selama 50 ms
    digitalWrite(BUZZER_PIN, LOW);          // Mematikan buzzer setelah 50 ms
    buzzerTriggered = true;                 // Menandai bahwa buzzer sudah menyala sekali
    Serial.println("Buzzer menyala selama 50ms, suhu >= 25°C");
  }
  if (suhu < 25.0) {                        // Reset flag jika suhu turun di bawah 25°C
    buzzerTriggered = false;
  }

  delay(2000); // Menunggu 2 detik sebelum membaca lagi
}
