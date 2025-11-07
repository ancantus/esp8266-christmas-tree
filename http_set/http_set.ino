#include <NeoPixelBus.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "RTC_Christmas_Tree";
const char *password = "merrychristmas";
ESP8266WebServer server(80);

constexpr std::uint32_t PIN = 6u;
constexpr std::uint32_t NUMROWS = 5u;
constexpr std::uint32_t NUMPIXELS = NUMROWS * NUMROWS;
NeoPixelBus<NeoGrbFeature, NeoEsp8266DmaWs2812xMethod> pixels(NUMPIXELS);

void handleRoot() {
  String html = "<h1>RTC Christmas Tree</h1>";
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

std::uint32_t readArg(const String& tag, std::uint32_t other)
{
  if (server.hasArg(tag)) 
  {
    return server.arg(tag).toInt();
  }
  return other;
}

void handleSubmitForm() 
{
  const RgbColor color{
    readArg("red", 0), 
    readArg("green", 0),
    readArg("blue", 0)
  };
  for (std::uint32_t i = 0u; i < NUMPIXELS; i++)
  {
    pixels.SetPixelColor(i, color);
  }
  pixels.Show();

  server.sendHeader("Location", "/", true); // Redirect back to root
  server.send(302, "text/plain", "");
}

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer

  server.on("/", handleRoot);
  server.on("/submitForm", handleSubmitForm);
  server.begin();

  // this resets all the neopixels to an off state
  pixels.Begin();
  pixels.Show();
}

void loop() 
{
  server.handleClient();
}
