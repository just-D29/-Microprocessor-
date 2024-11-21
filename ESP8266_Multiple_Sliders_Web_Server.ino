#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Assign output variable to GPIO pin
const int ledPin = 2; // GPIO5 (D1)

int ledBrightness = 0; // Variable to store LED brightness (0-1023)

void setup() {
  Serial.begin(115200);

  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, ledBrightness); // Set initial brightness to 0 (off)

  // WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266_Slider"); // Start WiFi manager with AP name

  Serial.println("Connected to WiFi");
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    String currentLine = ""; // Make a String to hold incoming data from the client
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // HTTP response headers
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>");
            client.println("html { font-family: Helvetica; text-align: center;}");
            client.println("input[type=range] { -webkit-appearance: none; width: 80%; height: 15px; background: #ddd; outline: none;}");
            client.println("input[type=range]::-webkit-slider-thumb { -webkit-appearance: none; appearance: none; width: 25px; height: 25px; background: #4CAF50; cursor: pointer;}");
            client.println("</style></head>");
            client.println("<body><h1>ESP8266 LED Brightness Control</h1>");

            // Display slider to control LED brightness
            client.println("<p>LED Brightness: " + String(ledBrightness) + "</p>");
            client.println("<input type=\"range\" min=\"0\" max=\"1023\" value=\"" + String(ledBrightness) + "\" id=\"brightnessSlider\" onchange=\"updateBrightness(this.value)\">");
            client.println("<script>");
            client.println("function updateBrightness(value) {");
            client.println("  var xhr = new XMLHttpRequest();");
            client.println("  xhr.open('GET', '/setBrightness?value=' + value, true);");
            client.println("  xhr.send();");
            client.println("}");
            client.println("</script></body></html>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    // Handle GET requests
    if (header.indexOf("GET /setBrightness?value=") >= 0) {
      int valueStart = header.indexOf('=') + 1;
      int valueEnd = header.indexOf(' ', valueStart);
      String valueStr = header.substring(valueStart, valueEnd);
      ledBrightness = valueStr.toInt();
      analogWrite(ledPin, ledBrightness); // Update LED brightness
      Serial.println("LED Brightness set to: " + String(ledBrightness));
    }

    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
  }
}