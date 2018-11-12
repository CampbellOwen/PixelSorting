#pragma once
#include "scene.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <random>

class PixelSorter : Scene
{
    public:
        PixelSorter(const std::string& path, int sampleSize = 20, unsigned int seed = std::time(nullptr));
        bool Update(sf::Texture& texture);
    private:
        sf::Image img;
        uint64_t index;
        int sampleSize;
        std::mt19937 randEng;
};