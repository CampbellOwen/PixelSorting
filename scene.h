#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
    public:
        virtual ~Scene() {};
        virtual sf::Image Update() = 0;
};