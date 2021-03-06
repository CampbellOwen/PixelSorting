#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
class Utility
{
    public:

        static uint64_t positionToIndex(const sf::Vector2u& pos, const sf::Vector2u& size)
        {
            uint64_t index = (pos.y * size.x) + pos.x;
            return index;
        }

        static sf::Vector2u indexToPosition(const uint64_t& index, const sf::Vector2u& size)
        {
            // std::cout << size.x << " " << size.y << std::endl;
            unsigned int x = (unsigned int) (index % (uint64_t)size.x);
            unsigned int y = (index / size.x);

            return {x, y};
        }
        static void resizeSprite(const sf::RenderWindow& window, const sf::Texture& texture, sf::Sprite& sprite)
        {
            sf::Vector2u windowSize = window.getSize();

            sf::Vector2u textureSize = texture.getSize();
            sprite.setScale(sf::Vector2f(1, 1));
            
            float scale;
            if (textureSize.x > textureSize.y) {
                scale = (float) windowSize.x / textureSize.x;
            }
            else {
                scale = (float) windowSize.y / textureSize.y;
            }
            sprite.setScale(scale, scale);
            
            sf::Vector2u spriteSize;
            spriteSize.x = textureSize.x * scale;
            spriteSize.y = textureSize.y * scale;

            sf::Vector2f position;
            position.x = (float) (windowSize.x / 2) - (spriteSize.x / 2);
            position.y = (float) (windowSize.y / 2) - (spriteSize.y / 2);

            sprite.setPosition(position);
        }

        static double colourDist(sf::Color c1, sf::Color c2)
        {
            double r = c1.r - c2.r;
            double g = c1.g - c2.g;
            double b = c1.b - c2.b;

            return ((r*r) + (g*g) + (b*b)) / 3.0;
        }
};
