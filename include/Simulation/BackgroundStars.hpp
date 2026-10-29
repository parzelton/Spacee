#pragma once
#include <SFML/Graphics.hpp>
#include "Core/Constants.hpp"

#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

class BackgroundStars {
private:
    uint64_t starsSeed;
    uint64_t starsCount;
    uint64_t maxStarsRadius;
    std::vector<sf::Vector2f> starsCoords;
    std::vector<float> starsRadiuses;
    std::vector<sf::CircleShape> stars;
    sf::VertexArray starsVertex;

private:
    void generateStarsCoords();

    void generateStarsRadiuses();

    void generateStars();  // DEPRECATED, NOT RECOMMENDED TO USE

    void generateStarsVertex();

    /*void takeRandomColor() {

    }*/

public:
    BackgroundStars(uint64_t seed = Config::Window::starsSeed,
                    uint64_t count = Config::Window::starsCount,
                    uint64_t r = Config::Window::maxStarsRadius);

    const std::vector<sf::CircleShape>& getStarsAsShapesVector();

    const sf::VertexArray& getStarsAsShapesVertex();
};