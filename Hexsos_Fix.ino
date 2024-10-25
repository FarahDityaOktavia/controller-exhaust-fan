#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD

// Inisialisasi pin untuk sensor DS18B20
const int oneWireBusPin = A0; // Pin digital untuk sensor DS18B20
OneWire oneWire(oneWireBusPin);
DallasTemperature sensors(&oneWire);

// Inisialisasi pin untuk relay
const int relayPin = 3; // Pin digital untuk relay

void setup() {
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  
  // Inisialisasi sensor suhu
  sensors.begin();
  
  // Inisialisasi pin relay sebagai output
  pinMode(relayPin, OUTPUT);
  
  // Matikan relay di awal
  digitalWrite(relayPin, LOW);

  // Tampilkan pesan awal di LCD
  // lcd.setCursor(0, 0);
  // lcd.print("Monitoring Suhu");
}

void loop() {
  // Minta pembacaan suhu dari sensor
  sensors.requestTemperatures();
  
  // Baca suhu dalam Celsius
  float celsius = sensors.getTempCByIndex(0);
  
  // Tampilkan suhu pada LCD
  lcd.setCursor(0, 0); // Set kursor ke baris kedua
  lcd.print("Suhu  : ");
  lcd.print(celsius);
  lcd.setCursor(14, 0); // Set kursor ke baris kedua
  lcd.write(223); // Menampilkan simbol derajat
  lcd.print("C"); // Spasi tambahan untuk menghapus angka sebelumnya
  
  //Mengontrol Lampu berdasarkan suhu
  lcd.setCursor(0, 1); // Set kursor ke baris kedua
  lcd.print("Kipas : ");
  lcd.setCursor(8, 1);

  // Jika suhu lebih dari 25°C, nyalakan relay
  if (celsius > 30.0) {
    digitalWrite(relayPin, HIGH);  // Nyalakan relay (aktifkan lampu)
    lcd.print("ON ");
  } else {
    digitalWrite(relayPin, LOW);   // Matikan relay (matikan lampu)
    lcd.print("OFF");
  }
  
  delay(1000); // Tunggu sejenak sebelum pembacaan berikutnya
}
