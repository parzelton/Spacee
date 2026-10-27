#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Core/Constants.hpp"

class Camera {
private:
	sf::Vector2<double> position;  // meters
	double initScale;
	double currScale;
	bool isFollowing;
	int targetInd;

public:
	Camera();

	sf::Vector2f worldToScreen(sf::Vector2<double> realCoord, const sf::RenderWindow& windows) const;

	sf::Vector2<double> screenToWorld(sf::Vector2f pixelCoords, const sf::RenderWindow& window) const;

	void zoom(float delta);
	void zoom(float delta, sf::Vector2i mousePizelCoords, const sf::RenderWindow& window);

	void follow(double targetX, double targetY);

	void move(double deltaX, double deltaY);

	const sf::Vector2<double> getPosition() const;
	const double getInitScale() const;
	const double getCurrScale() const;
	const float getRelScale() const;  // relative scale is the scale relative to the initial scale (Config::Camera::scale)
	const bool getIsFollowing() const;
	const int getTargetInd() const;

	void setInitScale(double initScale);
	void setCurrScale(double currScale);
	void setIsFollowing(bool isFollowing);
	void setTargetInd(int targetInd);
};