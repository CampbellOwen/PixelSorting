#pragma once
#include "scene.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <random>

class PixelSorter : Scene
{
    public:
        PixelSorter(sf::Image& img, int sampleSize = 500, unsigned int seed = std::time(nullptr));
        sf::Image Update();
    private:
        sf::Image& img;
        size_t index;
        int sampleSize;
        std::mt19937 randEng;
};