#pragma once
#include "scene.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <random>

class Wipe : Scene
{
    public:
        Wipe(const std::string& path);
        bool Update(sf::Texture& texture);
    private:
        sf::Image img;
        size_t row;
        sf::Color refColour;

};