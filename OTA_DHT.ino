#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <DHT.h>

// Konfigurasi Wi-Fi
const char* ssid = "S24 U";
const char* password = "12345678";

// Konfigurasi DHT
#define DHTPIN 4          // Pin sensor DHT (gunakan pin GPIO sesuai koneksi Anda)
#define DHTTYPE DHT11      // Tipe DHT: DHT11 atau DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  Serial.println("Booting...");

  // Inisialisasi sensor DHT
  dht.begin();

  // Koneksi ke Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Konfigurasi OTA
  ArduinoOTA.onStart([]() {
    String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem";
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();
  Serial.println("OTA Ready");
}

void loop() {
  // Jalankan OTA handler
  ArduinoOTA.handle();

  // Baca data dari sensor DHT
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Periksa apakah pembacaan berhasil
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.printf("Temperature: %.1f °C\n", temperature);
    Serial.printf("Humidity: %.2f %%\n", humidity);
  }

  delay(1000); // Delay 2 detik sebelum membaca ulang
}
