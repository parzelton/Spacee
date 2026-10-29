#include "Simulation/BackgroundStars.hpp"

void BackgroundStars::generateStarsCoords() {
    srand(starsSeed);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int resolutionWidth = desktop.size.x;
    unsigned int resolutioHeight = desktop.size.y;

    uint64_t count = 0;
    while (count != starsCount) {
        float x = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * static_cast<float>(resolutionWidth + 1);
        float y = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * static_cast<float>(resolutioHeight + 1);
        if (std::count(starsCoords.cbegin(), starsCoords.cend(), sf::Vector2f(x, y)) == 0) {
            starsCoords.push_back(sf::Vector2f(x, y));
            ++count;
        }
    }
}

void BackgroundStars::generateStarsRadiuses() {
    srand(starsSeed);

    uint64_t count = 0;
    while (count != starsCount) {
        float r = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * static_cast<double>(maxStarsRadius + 1);
        if (std::count(starsRadiuses.cbegin(), starsRadiuses.cend(), r) == 0) {
            starsRadiuses.push_back(r);
            ++count;
        }
    }
}

void BackgroundStars::generateStars() {  // DEPRECATED, NOT RECOMMENDED TO USE
    generateStarsCoords();
    generateStarsRadiuses();
    this->stars = {};
    uint64_t count = 0;
    while (count != starsCount) {
        sf::CircleShape star(starsRadiuses[count]);
        star.setPosition(starsCoords[count]);
        star.setFillColor(sf::Color(254, 254, 254));
        stars.push_back(star);
        ++count;
    }
}
    
void BackgroundStars::generateStarsVertex() {
    generateStarsCoords();
    generateStarsRadiuses();
    starsVertex = sf::VertexArray(sf::PrimitiveType::Points, starsCount);
    uint64_t count = 0;
    while (count != starsCount) {;
        starsVertex[count].position = starsCoords[count];
        starsVertex[count].color = sf::Color(254, 254, 254);
        //stars.push_back(star);
        ++count;
    }
}

/*void BackgroundStars::takeRandomColor() {

}*/

BackgroundStars::BackgroundStars(uint64_t seed,
                                 uint64_t count,
                                 uint64_t r) {
    starsSeed = seed;
    starsCount = count;
    maxStarsRadius = r;
    //generateStars();  // DEPRECATED, NOT RECOMMENDED TO USE
    generateStarsVertex();
}

const std::vector<sf::CircleShape>& BackgroundStars::getStarsAsShapesVector() {
    return stars;
}

const sf::VertexArray& BackgroundStars::getStarsAsShapesVertex() {
    return starsVertex;
}