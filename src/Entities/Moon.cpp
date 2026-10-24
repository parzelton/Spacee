#include "Entities/Moon.hpp"

Moon::Moon(std::string name, float radius, float minRadius, double mass,
    double a, double b, sf::Vector2<double> realV, sf::Color color,
    CoordinateType type, CelestialBody* parent) :
    CelestialBody(name, radius, minRadius, mass, a, b, realV, color, type) {
    setParent(parent);
}