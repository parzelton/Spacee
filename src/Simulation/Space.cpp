#include "Simulation/Space.hpp"

#include "Simulation/BackgroundStars.hpp"
#include "Entities/CelestialBody.hpp"
#include "Entities/Star.hpp"
#include "Entities/Planet.hpp"

#include "Core/Constants.hpp"
#include <iostream>

Space::Space(double startTimeAcceleration) {
    stars = BackgroundStars();
    this->timeAcceleration = startTimeAcceleration;
    elapsedSimulationTime = 0.;
    elapsedRealTime = 0.;
}

void Space::changeVelocities(double acceleratedDt) {
    std::vector<sf::Vector2<double>> accelerations(bodies.size(), {0.f, 0.f});

    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = 0; j < bodies.size(); ++j) {
            if (i == j)
                continue;
            
            double dx = bodies[j]->getX() - bodies[i]->getX();
            double dy = bodies[j]->getY() - bodies[i]->getY();
            
            double distanceSqr = dx * dx + dy * dy;
            double distance = std::sqrt(distanceSqr);

            if (distance < 1000.)
                continue;  // TODO: burst

            //double m1 = bodies[i]->getMass() * Config::Coefs::EM_TO_KG;  // kg
            double m2 = bodies[j]->getMass() * Config::Coefs::EM_TO_KG;  // kg

            double accelerationMagnitude = (Config::Coefs::G * m2) / distanceSqr;

            sf::Vector2<double> normalizedVector{dx/distance, dy/distance};
            sf::Vector2<double> accelerationVector = normalizedVector * accelerationMagnitude;

            accelerations[i] += accelerationVector;
        }
    }

    for (size_t i = 0; i < bodies.size(); ++i) {
        sf::Vector2<double> newVelocity = bodies[i]->getRealV() + accelerations[i] * acceleratedDt;
        bodies[i]->setRealV(newVelocity);
    }
}


void Space::drawBackground(sf::RenderWindow& window) {
    window.clear(Config::Window::backgroundColor);

    // stars
    const auto& starsVertex = this->stars.getStarsAsShapesVertex();
    window.draw(starsVertex);
}


void Space::drawSpace(sf::RenderWindow& window, Camera& camera, float deltaTime) {
    float safeDeltaTime = std::min(deltaTime, Config::Window::maxDt);  // clamping

    double acceleratedDt = static_cast<double>(safeDeltaTime * this->timeAcceleration);

    elapsedSimulationTime += acceleratedDt;
    elapsedRealTime += deltaTime;

    // sub-stepping
    int steps = static_cast<int>(std::ceil(acceleratedDt / Config::Window::maxSubDt));
    steps = std::min(steps, Config::Window::maxSteps);

    float subDt = static_cast<float>(acceleratedDt) / static_cast<float>(steps);

    // star pulsation
    for (std::unique_ptr<CelestialBody>& body : bodies) {
        if (typeid(*body) == typeid(Star)) {
            Star* star = static_cast<Star*>(body.get());
            star->updatePulse(elapsedRealTime);
            break;
        }
    }

    for (size_t i = 0; i < steps; ++i) {
        changeVelocities(subDt);
        drawBackground(window);

        // CBs
        for (std::unique_ptr<CelestialBody>& body : bodies)
            body->update(subDt);

        for (std::unique_ptr<CelestialBody>& body : bodies)
            body->draw(window, camera);

        if (camera.getIsFollowing()) {
            int targetInd = camera.getTargetInd();
            const CelestialBody& targetBody = *(bodies.at(targetInd));
            camera.follow(targetBody.getX(), targetBody.getY());
        }
    }
}

void Space::initializeSolarSystem() {
    // Sun
    std::unique_ptr<CelestialBody> sun = std::make_unique<Star>(Config::CB::Sun::name,
                                                                Config::CB::Sun::pixelRadius,
                                                                Config::CB::Sun::minPixelRadius,
                                                                Config::CB::Sun::mass,
                                                                Config::CB::Sun::longitude,
                                                                Config::CB::Sun::distance,
                                                                Config::CB::Sun::realV,
                                                                Config::CB::Sun::color,
                                                                CoordinateType::Ecliptic);
    bodies.push_back(std::move(sun));

    // Mercury
    std::unique_ptr<CelestialBody> mercury = std::make_unique<Planet>(Config::CB::Mercury::name,
                                                                      Config::CB::Mercury::pixelRadius,
                                                                      Config::CB::Mercury::minPixelRadius,
                                                                      Config::CB::Mercury::mass,
                                                                      Config::CB::Mercury::longitudeAphelion,
                                                                      Config::CB::Mercury::aphelion,
                                                                      Config::CB::Mercury::aphelionVelocity,
                                                                      Config::CB::Mercury::color,
                                                                      CoordinateType::Ecliptic);
    bodies.push_back(std::move(mercury));

    // Venus
    std::unique_ptr<CelestialBody> venus = std::make_unique<Planet>(Config::CB::Venus::name,
                                                                    Config::CB::Venus::pixelRadius,
                                                                    Config::CB::Venus::minPixelRadius,
                                                                    Config::CB::Venus::mass,
                                                                    Config::CB::Venus::longitudeAphelion,
                                                                    Config::CB::Venus::aphelion,
                                                                    Config::CB::Venus::aphelionVelocity,
                                                                    Config::CB::Venus::color,
                                                                    CoordinateType::Ecliptic);
    bodies.push_back(std::move(venus));

    // Earth
    std::unique_ptr<CelestialBody> earth = std::make_unique<Planet>(Config::CB::Earth::name,
                                                                    Config::CB::Earth::pixelRadius,
                                                                    Config::CB::Earth::minPixelRadius,
                                                                    Config::CB::Earth::mass,
                                                                    Config::CB::Earth::longitudeAphelion,
                                                                    Config::CB::Earth::aphelion,
                                                                    Config::CB::Earth::aphelionVelocity,
                                                                    Config::CB::Earth::color,
                                                                    CoordinateType::Ecliptic);
    bodies.push_back(std::move(earth));

    // Mars
    std::unique_ptr<CelestialBody> mars = std::make_unique<Planet>(Config::CB::Mars::name,
                                                                   Config::CB::Mars::pixelRadius,
                                                                   Config::CB::Mars::minPixelRadius,
                                                                   Config::CB::Mars::mass,
                                                                   Config::CB::Mars::longitudeAphelion,
                                                                   Config::CB::Mars::aphelion,
                                                                   Config::CB::Mars::aphelionVelocity,
                                                                   Config::CB::Mars::color,
                                                                   CoordinateType::Ecliptic);
    bodies.push_back(std::move(mars));

    // Jupiter
    std::unique_ptr<CelestialBody> jupiter = std::make_unique<Planet>(Config::CB::Jupiter::name,
                                                                      Config::CB::Jupiter::pixelRadius,
                                                                      Config::CB::Jupiter::minPixelRadius,
                                                                      Config::CB::Jupiter::mass,
                                                                      Config::CB::Jupiter::longitudeAphelion,
                                                                      Config::CB::Jupiter::aphelion,
                                                                      Config::CB::Jupiter::aphelionVelocity,
                                                                      Config::CB::Jupiter::color,
                                                                      CoordinateType::Ecliptic);
    bodies.push_back(std::move(jupiter));

    // Saturn
    std::unique_ptr<CelestialBody> saturn = std::make_unique<Planet>(Config::CB::Saturn::name,
                                                                     Config::CB::Saturn::pixelRadius,
                                                                     Config::CB::Saturn::minPixelRadius,
                                                                     Config::CB::Saturn::mass,
                                                                     Config::CB::Saturn::longitudeAphelion,
                                                                     Config::CB::Saturn::aphelion,
                                                                     Config::CB::Saturn::aphelionVelocity,
                                                                     Config::CB::Saturn::color,
                                                                     CoordinateType::Ecliptic);
    bodies.push_back(std::move(saturn));

    // Uranus
    std::unique_ptr<CelestialBody> uranus = std::make_unique<Planet>(Config::CB::Uranus::name,
                                                                     Config::CB::Uranus::pixelRadius,
                                                                     Config::CB::Uranus::minPixelRadius,
                                                                     Config::CB::Uranus::mass,
                                                                     Config::CB::Uranus::longitudeAphelion,
                                                                     Config::CB::Uranus::aphelion,
                                                                     Config::CB::Uranus::aphelionVelocity,
                                                                     Config::CB::Uranus::color,
                                                                     CoordinateType::Ecliptic);
    bodies.push_back(std::move(uranus));

    // Neptune
    std::unique_ptr<CelestialBody> neptune = std::make_unique<Planet>(Config::CB::Neptune::name,
                                                                     Config::CB::Neptune::pixelRadius,
                                                                     Config::CB::Neptune::minPixelRadius,
                                                                     Config::CB::Neptune::mass,
                                                                     Config::CB::Neptune::longitudeAphelion,
                                                                     Config::CB::Neptune::aphelion,
                                                                     Config::CB::Neptune::aphelionVelocity,
                                                                     Config::CB::Neptune::color,
                                                                     CoordinateType::Ecliptic);
    bodies.push_back(std::move(neptune));

    // Pluto
    std::unique_ptr<CelestialBody> pluto = std::make_unique<Planet>(Config::CB::Pluto::name,
                                                                    Config::CB::Pluto::pixelRadius,
                                                                    Config::CB::Pluto::minPixelRadius,
                                                                    Config::CB::Pluto::mass,
                                                                    Config::CB::Pluto::longitudeAphelion,
                                                                    Config::CB::Pluto::aphelion,
                                                                    Config::CB::Pluto::aphelionVelocity,
                                                                    Config::CB::Pluto::color,
                                                                    CoordinateType::Ecliptic);
    bodies.push_back(std::move(pluto));
}



const float Space::getTimeAcceleration() const { return timeAcceleration; }
const std::vector<std::unique_ptr<CelestialBody>>& Space::getBodies() const { return bodies; }
const int Space::getSunInd() const {
    int i = 0;
    for (auto iter = bodies.cbegin(); iter != bodies.cend() || i < bodies.size(); ++iter, ++i) {
        if ((*iter)->getName() == "Sun") {
            return i;
        }
    }
}
const double Space::getElapsedSimulationTime() const { return this->elapsedSimulationTime; }

void Space::setTimeAcceleration(float startTimeAcceleration) { this->timeAcceleration = startTimeAcceleration; }