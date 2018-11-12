#include "wipe.h"
#include "utility.h"
#include <iostream>

Wipe::Wipe(const std::string& path)
{
    img.loadFromFile(path);
    std::cout << "Size: {" << img.getSize().x << ", " << img.getSize().y << "}" << std::endl;
    size_t numPixels = img.getSize().x * img.getSize().y;
    std::cout << "Number of Pixels: " << numPixels << std::endl;
    sf::Vector2u pos = {0, 0};
    std::cout << "Position: {" << pos.x << ", " << pos.y << "} " << "Index: " << Utility::positionToIndex(pos, img.getSize()) << std::endl;
    pos = {img.getSize().x -1, img.getSize().y - 1};
    std::cout << "Position: {" << pos.x << ", " << pos.y << "} " << "Index: " << Utility::positionToIndex(pos, img.getSize()) << std::endl;


    pos = Utility::indexToPosition(0, img.getSize());
    std::cout << "Index: " << 0 <<  " " << "Position: {" << pos.x << ", " << pos.y << "} " << std::endl;
    pos = Utility::indexToPosition(numPixels-1, img.getSize());
    std::cout << "Index: " << numPixels-1 <<  " " << "Position: {" << pos.x << ", " << pos.y << "} " << std::endl;
    
    row = 0;
    refColour = img.getPixel(0, 0);
}

bool Wipe::Update(sf::Texture& texture)
{
    sf::Vector2u size = img.getSize();

    if (row >= size.y) {
        return false;
    }

    std::vector< sf::Color > pixels;

    for(size_t x = 0; x < size.x; x++) {
        pixels.push_back(img.getPixel(x, row));
    }

    std::sort(pixels.begin(), pixels.end(), [this](auto &left, auto &right) {
            return Utility::colourDist(refColour, left) < Utility::colourDist(refColour, right);
        });

    for(size_t x = 0; x < size.x; x++) {
        img.setPixel(x, row, pixels[x]);
    }

    row++;

    texture.update(img);
    return true;
}