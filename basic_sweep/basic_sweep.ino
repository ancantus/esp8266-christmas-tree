#include <NeoPixelBus.h>
#include <array>

constexpr std::uint32_t PIN = 6u;
constexpr std::uint32_t NUMROWS = 5u;
constexpr std::uint32_t NUMPIXELS = NUMROWS * NUMROWS;

const std::array<RgbColor, 7u> RAINBOW = {
  RgbColor(255, 0, 0),   // red
  RgbColor(255, 127, 0), // orange
  RgbColor(255, 255, 0), // yellow
  RgbColor(0, 255, 0),   // green
  RgbColor(0, 0, 255),   // blue
  RgbColor(75, 0, 130),  // purple
  RgbColor(148, 0, 211), // violet
};

NeoPixelBus<NeoGrbFeature, NeoEsp8266DmaWs2812xMethod> pixels(NUMPIXELS);

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  // while (!Serial); // wait for serial attach

  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

  // this resets all the neopixels to an off state
  pixels.Begin();
  pixels.Show();

  Serial.println();
  Serial.println("Running...");
}

void sweepColor(RgbColor color, std::uint32_t duration)
{
  const std::uint32_t stepDuration = duration / NUMROWS;
  for (std::uint32_t i = 0u; i < NUMROWS; i++)
  {
    for (std::uint32_t j = 0u; j < NUMROWS; j++)
    {
      pixels.SetPixelColor((i * NUMROWS) + j, color);
    }
    pixels.Show();
    delay(stepDuration);
  }
}

void loop() 
{
  for (const auto color : RAINBOW)
  {
    sweepColor(color, 300);
    delay(1000);
  }
}
