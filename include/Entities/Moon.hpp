#pragma once
#include "Entities/CelestialBody.hpp"

class Moon : public CelestialBody {
public:
    Moon(std::string name, float radius, float minRadius, double mass,
        double a, double b, sf::Vector2<double> realV, sf::Color color,
        CoordinateType type = CoordinateType::Rectangular, CelestialBody* parent = nullptr);

    virtual sf::Color getColor() const { return shape.getFillColor(); }
    virtual void setColor(sf::Color color) { shape.setFillColor(color); }
};