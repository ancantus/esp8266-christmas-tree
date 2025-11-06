#include <Adafruit_NeoPixel.h>
#include <array>

constexpr std::uint32_t PIN = 6u;
constexpr std::uint32_t NUMROWS = 5u;
constexpr std::uint32_t NUMPIXELS = NUMROWS * NUMROWS;

const std::array<std::uint32_t, 7u> RAINBOW = {
  Adafruit_NeoPixel::Color(255, 0, 0),   // red
  Adafruit_NeoPixel::Color(255, 127, 0), // orange
  Adafruit_NeoPixel::Color(255, 255, 0), // yellow
  Adafruit_NeoPixel::Color(0, 255, 0),   // green
  Adafruit_NeoPixel::Color(0, 0, 255),   // blue
  Adafruit_NeoPixel::Color(75, 0, 130),  // purple
  Adafruit_NeoPixel::Color(148, 0, 211), // violet
};

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pixels.begin();
}

void sweepColor(std::uint32_t color, std::uint32_t duration)
{
  const std::uint32_t stepDuration = duration / NUMROWS;
  for (std::uint32_t i = 0u; i < NUMROWS; i++)
  {
    for (std::uint32_t j = 0u; j < NUMROWS; j++)
    {
      pixels.setPixelColor((i * NUMROWS) + j, color);
    }
    delay(stepDuration);
  }
}

void loop() 
{
  for (const auto color : RAINBOW)
  {
    sweepColor(color, 200);
    delay(1000);
  }
}
