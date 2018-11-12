#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
    public:
        virtual ~Scene() {};
        virtual bool Update(sf::Texture& texture) = 0;
};