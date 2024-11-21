#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "S24 U";
const char* password = "12345678";

// DHT sensor configuration
#define DHTPIN 2       // Pin data DHT11 (GPIO4 pada NodeMCU)
#define DHTTYPE DHT11   // Tipe sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Web server instance
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  // WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // OTA setup
  ArduinoOTA.onStart([]() {
    Serial.println("Start OTA Update");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd OTA Update");
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

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize DHT sensor
  dht.begin();
  Serial.println("DHT11 initialized");

  // Web server routes
  server.on("/", []() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    String html = "<html><body>";
    html += "<h1>DHT11 Sensor Data</h1>";
    if (isnan(temperature) || isnan(humidity)) {
      html += "<p>Failed to read from DHT sensor!</p>";
    } else {
      html += "<p>Temperature: " + String(temperature) + " &deg;C</p>";
      html += "<p>Humidity: " + String(humidity) + " %</p>";
    }
    html += "<a href=\"/\"><button>Refresh</button></a>";
    html += "</body></html>";

    server.send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
}