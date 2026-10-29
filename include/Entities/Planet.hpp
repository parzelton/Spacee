#pragma once
#include "Entities/CelestialBody.hpp"
#include "Core/Camera.hpp"

class Planet : public CelestialBody {

public:
    Planet(std::string name, float radius, float minRadius, double mass,
           double a, double b, sf::Vector2<double> realV, sf::Color color,
           CoordinateType type = CoordinateType::Rectangular, CelestialBody* parent = nullptr);


    virtual sf::Color getColor() const { return shape.getFillColor(); }
    virtual void setColor(sf::Color color) { shape.setFillColor(color); }

    void burst();  // TODO
};