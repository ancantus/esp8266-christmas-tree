#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "MyESP8266AP";
const char *password = "mysecretpassword";

ESP8266WebServer server(80);

void handleRoot() {
  String html = "<h1>ESP8266 Web Server</h1>";
  html += "<form method='POST' action='/submitForm'>";
  html += "<label for='red'>Red (0-255):</label>";
  html += "<input type='number' id='red' name='red'>";
  html += "<label for='green'>Green (0-255):</label>";
  html += "<input type='number' id='green' name='green'>";
  html += "<label for='blue'>Blue (0-255):</label>";
  html += "<input type='number' id='blue' name='blue'>";
  html += "<input type='submit' value='Submit'>";
  html += "</form>";
  server.send(200, "text/html", html);
}

void handleSubmitForm() {
  if (server.hasArg("red")) {
    red = std::stoul(server.arg("red"));
  }
  server.sendHeader("Location", "/", true); // Redirect back to root
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
