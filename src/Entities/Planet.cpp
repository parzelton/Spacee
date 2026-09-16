#include "Entities/Planet.hpp"

Planet::Planet(std::string name, float radius, float minRadius, double mass,
               double a, double b, sf::Vector2<double> realV, sf::Color color,
               CoordinateType type) :
    CelestialBody(name, radius, minRadius, mass, a, b, realV, color, type)
{ }