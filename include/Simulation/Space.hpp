#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
class BackgroundStars;
class CelestialBody;
class Star;
class Planet;
#include "Simulation/BackgroundStars.hpp"
#include "Core/Camera.hpp"
//#include "Entities/CelestialBody.hpp"
//#include "Entities/Star.hpp"
//#include "Entities/Planet.hpp"

class Space {
private:
	BackgroundStars stars;
	float timeAcceleration;
	double elapsedSimulationTime;
	double elapsedRealTime;

	// 0 - Sun, 1 - Mercury, 2 - Venus, etc.
	std::vector<std::unique_ptr<CelestialBody>> bodies;

	void changeVelocities(double acceleratedDt);
	void drawBackground(sf::RenderWindow& window);

public:
	Space(double timeAcceleration);

	void initializeSolarSystem();
	void drawSpace(sf::RenderWindow& window, Camera& camera, float deltaTime);

	const float getTimeAcceleration() const;
	const double getElapsedSimulationTime() const;
	const std::vector<std::unique_ptr<CelestialBody>>& getBodies() const;
	const int getSunInd() const;  // DEPRECATED, NOT RECOMMENDED TO USE

	void setTimeAcceleration(float timeAcceleration);
	//void setBodies();  // is this really necessary?
	//void setSun();     // is this really necessary?
};