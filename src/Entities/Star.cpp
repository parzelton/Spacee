#include "Entities/Star.hpp"

#include "Core/BaseFunctions.hpp"

Star::Star(std::string name, float radius, float minRadius, double mass,
           double a, double b, sf::Vector2<double> realV, sf::Color color,
           CoordinateType type) :
    CelestialBody(name, radius, minRadius, mass, a, b, realV, color, type)
{
    baseColor = color;
    setDarkAndBrightColors();
}

void Star::setDarkAndBrightColors() {
    // mix base color with white at approximately 40%
    float shiftToWhite = 0.4f;
    brightColor.r = static_cast<uint8_t>(baseColor.r + (255 - baseColor.r) * shiftToWhite);
    brightColor.g = static_cast<uint8_t>(baseColor.g + (255 - baseColor.g) * shiftToWhite);
    brightColor.b = static_cast<uint8_t>(baseColor.b + (255 - baseColor.b) * shiftToWhite);
    brightColor.a = baseColor.a;

    // reduce red at 10%, green at 35% and blue at 60%
    darkColor.r = static_cast<uint8_t>(std::max(0.f, baseColor.r * 0.90f));
    darkColor.g = static_cast<uint8_t>(std::max(0.f, baseColor.g * 0.65f));
    darkColor.b = static_cast<uint8_t>(std::max(0.f, baseColor.b * 0.40f));
    darkColor.a = baseColor.a;
}

void Star::updatePulse(double elapsedTime) {
    float sinValue = sin(elapsedTime);

    if (sinValue >= 0.f) {
        this->color = lerpColors(baseColor, brightColor, sinValue);
    }
    else {
        this->color = lerpColors(baseColor, darkColor, sinValue);
    }

    shape.setFillColor(this->color);
}