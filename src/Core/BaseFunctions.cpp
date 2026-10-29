#include "Core/BaseFunctions.hpp"

#include "Entities/CelestialBody.hpp"
#include "Entities/Star.hpp"
#include "Entities/Planet.hpp"

inline static bool areEqual(float a, float b, float epsilon) {
    return static_cast<bool>(abs(a - b) < epsilon);
}

float degToRad(float degrees) {
    return static_cast<float>(degrees * std::numbers::pi / 180.);
}

float radToDeg(float radians) {
    return static_cast<float>(radians * (180. / std::numbers::pi));
}

double normalizeDegrees(double degrees) {
    if (degrees > 360.)
        return degrees - 360.;
    if (degrees < 0.)
        return degrees + 360.;
    return degrees;
}


sf::Angle argumentOfVelocityAtTrueLongitude(double L, double e, double varpi) {  // For Earth on;y!!!
    double Lr = degToRad(L);
    double varpir = degToRad(varpi);

    double vx = -(sin(Lr) + e * sin(varpir));
    double vy = cos(Lr) + e * cos(varpir);

    double alpha = atan2(vy, vx);

    return sf::Angle(sf::radians(alpha));
}
sf::Angle argumentOfVelocityAtTrueLongitude(sf::Angle L, double e, sf::Angle Omega, sf::Angle i, sf::Angle omega) {
    double nu = L.asDegrees() - Omega.asDegrees() - omega.asDegrees();

    double nr = degToRad(nu);
    double Or = Omega.asRadians();
    double ir = i.asRadians();
    double wr = omega.asRadians();

    double v1x = -std::sin(nr) * std::cos(wr)
        - (e + std::cos(nr)) * std::sin(wr);
    double v1y = -std::sin(nr) * std::sin(wr)
        + (e + std::cos(nr)) * std::cos(wr);

    double v2x = v1x;
    double v2y = v1y * std::cos(ir);
    //double v2z = v1y * std::sin(ir);

    double vx = v2x * std::cos(Or) - v2y * std::sin(Or);
    double vy = v2x * std::sin(Or) + v2y * std::cos(Or);
    //double vz = v2z;

    return sf::Angle(sf::radians(std::atan2(vy, vx)));
}

std::string formatDouble(double number, Unit unit) {
    std::ostringstream oss;
    oss.imbue(std::locale("en_US.UTF-8"));

    // distance, meter & kilometer
    if (unit == Unit::Meter || unit == Unit::Kilometer) {
        oss << std::fixed << std::setprecision(2) << number;
    }

    // distance, au
    if (unit == Unit::Au) {
        oss << std::fixed << std::setprecision(4) << number;
    }

    // velocity
    if (unit == Unit::Mps) {
        oss << std::fixed << std::setprecision(2) << number;
    }
    if (unit == Unit::Aps) {
        oss << std::fixed << std::setprecision(10) << number;
    }

    // mass
    if (unit == Unit::Kilogram) {
        oss << std::fixed << std::setprecision(2) << number;
    }
    if (unit == Unit::Em) {
        oss << std::fixed << std::setprecision(5) << number;
    }

    // time
    if (unit == Unit::Sec || unit == Unit::Year) {
        oss << std::fixed << std::setprecision(0) << number;
    }

    return oss.str();
}
std::string formatExponential(double number) {
    std::ostringstream oss;
    oss.imbue(std::locale("en_US.UTF-8"));
    oss << std::scientific << number;
    return oss.str();
}

double distanseFromAnotherCb(const CelestialBody& targetCb, const CelestialBody& anotherCb) {
    double dx = abs(targetCb.getX() - anotherCb.getX());
    double dy = abs(targetCb.getY() - anotherCb.getY());
    return std::sqrt(dx * dx + dy * dy);
}

sf::Color lerpColors(sf::Color start, sf::Color end, float t) {
    t = std::max(0.f, std::min(1.f, t));

    uint8_t r = static_cast<uint8_t>(start.r + (end.r - start.r) * t);
    uint8_t g = static_cast<uint8_t>(start.g + (end.g - start.g) * t);
    uint8_t b = static_cast<uint8_t>(start.b + (end.b - start.b) * t);
    uint8_t a = start.a;  // start.a equals end.a

    return sf::Color(r, g, b, a);
}

double calculatePolarRadius(double semiMajorAxis, double eccentricity, sf::Angle trueAnomaly) {
    double r = semiMajorAxis * (1. - eccentricity * eccentricity) / (1. + eccentricity * cos(trueAnomaly.asRadians()));
    return r;
}

sf::Vector2<double> calculateEclipticCoords(double polarRadius, sf::Angle longitudeAscendingNode, sf::Angle argumentOfLatitude, sf::Angle inclination) {
    double r = polarRadius;
    double bigOmega = longitudeAscendingNode.asRadians();
    double u = argumentOfLatitude.asRadians();
    double i = inclination.asRadians();

    double x = r * (cos(bigOmega) * cos(u) - sin(bigOmega) * sin(u) * cos(i));
    double y = r * (sin(bigOmega) * cos(u) + cos(bigOmega) * sin(u) * cos(i));

    return sf::Vector2<double>(x, y);
}