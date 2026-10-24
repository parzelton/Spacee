#pragma once
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

class Camera;

enum class CoordinateType {
    Rectangular,
    Polar
};


class CelestialBody {
protected:
    std::string name;
    float radius;               // pixel
    float minRadius;            // pixel
    double mass;                // Earth masses
    double x;                   // real (m)
    double y;                   // real (m)
    sf::Vector2<double> realV;  // velocity
    sf::Color color;

    sf::CircleShape shape;

    bool isGravitySource = true;
    CelestialBody* parent = nullptr;


public:
    // heliocentric rectangular & ecliptic coordinate system
    CelestialBody(std::string name, float radius, float minRadius, double mass,
                  double a, double b, sf::Vector2<double> realV, sf::Color color,
                  CoordinateType type = CoordinateType::Rectangular);
    virtual ~CelestialBody() = default;

    // these ones have default implementations
    virtual void update(double acceleratedDt);
    virtual void draw(sf::RenderWindow& window, const Camera& camera);
    virtual bool isClicked(sf::Vector2f mouseCoords);

    const std::string getName() const;
    const float getRadius() const;
    const float getMinRadius() const;
    const double getMass() const;
    const double getX() const;
    const double getY() const;
    const sf::Vector2<double> getRealV() const;
    const sf::Color getColor() const;

    const bool getIsGravitySource() const;
    const CelestialBody* getParent() const;


    void setName(std::string name);
    void setRadius(float radius);
    void setMinRadius(float minRadius);
    void setMass(double mass);
    void setX(double x);
    void setY(double y);
    void setRealV(sf::Vector2<double> realV);
    void setColor(sf::Color color);

    void setShape();

    void setIsGravitySource(bool isGravitySource);
    void setParent(CelestialBody* parent);
};