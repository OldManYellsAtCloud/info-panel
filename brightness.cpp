#include "brightness.h"
#include <string>

std::string Brightness::BRIGHTNESS_PATH = "/sys/class/backlight/backlight/brightness";
double Brightness::MAX_BRIGHTNESS = 3124.0;

Brightness::Brightness()
{
    brightnessFile.open(BRIGHTNESS_PATH);
}

int Brightness::getBrightness()
{
    int realBrightness;
    std::string line;
    std::getline(brightnessFile, line);
    realBrightness = std::stoi(line);
    brightnessFile.seekg(0);
    return static_cast<int>(realBrightness / MAX_BRIGHTNESS * 100);
}

void Brightness::setBrightness(int brightness)
{
    int convBrightness = (brightness / 100.0) * MAX_BRIGHTNESS;
    brightnessFile << std::to_string(convBrightness) << std::endl;
}

