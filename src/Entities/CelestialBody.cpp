#include "Entities/CelestialBody.hpp"

#include "Core/Camera.hpp"
#include "Core/Constants.hpp"

CelestialBody::CelestialBody(std::string name, float radius, float minRadius, double mass,
                             double a, double b, sf::Vector2<double> realV, sf::Color color,
                             CoordinateType type, CelestialBody* parent) :
        name(name),
        radius(radius),
        minRadius(minRadius),
        mass(mass),
        x(type == CoordinateType::Rectangular ? a * Config::Coefs::AU_TO_M : (b * Config::Coefs::AU_TO_M) * cos(degToRad(a))),
        y(type == CoordinateType::Rectangular ? b * Config::Coefs::AU_TO_M : (b * Config::Coefs::AU_TO_M) * sin(degToRad(a))),
        realV(realV),
        color(color),
        parent(parent)
    {
        setShape();
    }

void CelestialBody::update(double acceleratedDt) {
    double offsetX = realV.x * acceleratedDt;
    double offsetY = realV.y * acceleratedDt;
    this->x += offsetX;
    this->y += offsetY;
}
void CelestialBody::draw(sf::RenderWindow& window, const Camera& camera) {
    sf::Vector2f pixelPos = camera.worldToScreen(sf::Vector2<double>(this->x, this->y), window);

    float relativeScale = camera.getRelScale();

    float pixelRadius = this->getRadius() * relativeScale;
    pixelRadius = std::max(pixelRadius, this->minRadius);

    shape.setRadius(pixelRadius);
    shape.setOrigin({ pixelRadius, pixelRadius });
    shape.setPosition(pixelPos);
    window.draw(shape);
}
bool CelestialBody::isClicked(sf::Vector2f mouseCoords) {
    sf::Vector2f center = shape.getPosition();
    sf::Vector2f delta = mouseCoords - center;

    float distanceSquare = delta.x * delta.x + delta.y * delta.y;
    float radiusSquare = shape.getRadius() * shape.getRadius();

    return distanceSquare <= radiusSquare;
}

const std::string CelestialBody::getName() const { return name; }
const float CelestialBody::getRadius() const { return radius; }
const float CelestialBody::getMinRadius() const { return minRadius; }
const double CelestialBody::getMass() const { return mass; }
const double CelestialBody::getX() const { return x; }
const double CelestialBody::getY() const { return y; }
const sf::Vector2<double> CelestialBody::getRealV() const { return realV; };
const sf::Color CelestialBody::getColor() const { return color; }

const bool CelestialBody::getIsGravitySource() const { return isGravitySource; }
const CelestialBody* CelestialBody::getParent() const { return parent; }



void CelestialBody::setName(std::string name) { this->name = name; }
void CelestialBody::setRadius(float raidus) { this->radius = radius; }
void CelestialBody::setMinRadius(float minRadius) { this->minRadius = minRadius; }
void CelestialBody::setMass(double mass) { this->mass = mass; }
void CelestialBody::setX(double x) { this->x = x; }
void CelestialBody::setY(double y) { this->y = y; }
void CelestialBody::setRealV(sf::Vector2<double> realV) { this->realV = realV; };
void CelestialBody::setColor(sf::Color color) { this->color = color; }

void CelestialBody::setShape() {
    shape = sf::CircleShape(radius);
    shape.setFillColor(color);
    shape.setOrigin(sf::Vector2f(radius, radius));
    shape.setPosition(sf::Vector2f(x, y));
}

void CelestialBody::setParent(CelestialBody* parent) { this->parent = parent; }
void CelestialBody::setIsGravitySource(bool isGravitySource) { this->isGravitySource = isGravitySource; }