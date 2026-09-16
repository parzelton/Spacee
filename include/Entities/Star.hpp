#pragma once
#include "Entities/CelestialBody.hpp"
#include "Core/Camera.hpp"

class Star : public CelestialBody {
private:
    sf::Color brightColor;
    sf::Color baseColor;
    sf::Color darkColor;

    void setDarkAndBrightColors();

public:
    Star(std::string name, float radius, float minRadius, double mass,
         double a, double b, sf::Vector2<double> realV, sf::Color color,
         CoordinateType type = CoordinateType::Ecliptic);

	// TODO: trail

    virtual sf::Color getColor() const { return shape.getFillColor(); }
    virtual void setColor(sf::Color color) { shape.setFillColor(color); }

    void updatePulse(double elapsedTime);
};